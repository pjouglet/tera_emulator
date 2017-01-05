#include "Inventory.h"
#include "IItem.h"
#include "InventorySlot.h"
#include "InventoryService.h"
#include "ServerTimer.h"
#include "PassivityService.h"
#include "BroadcastService.h"
#include "SendPacket.h"
#include "Stream.h"
#include "Client.hpp"
#include "Passivity.h"

Inventory::Inventory(Player * owner)
{
	_owner = owner;
	_slotCount = 0;
	_gold = 0;
	_maxGold = 0;
	_itemLevel = 0;
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < _slots.size(); i++)
	{
		if (_slots[i])
		{
			delete _slots[i];
			_slots[i] = 0;
		}
	}
	_slots.clear();
}

const bool Inventory::Initialize(short slotCount, int maxPlayerGold)
{
	for (size_t i = 0; i < 20; i++)
	{
		_slots.push_back(new InventorySlot(i + 1)); // profileSlots
	}

	for (size_t i = 0; i < slotCount; i++)
	{
		_slots.push_back(new InventorySlot(i + 40)); // profileSlots slot id starts from 40
	}

	_slotCount = slotCount;

	if (maxPlayerGold < 0)
		maxPlayerGold = 0xffffffffffffffff; //max ulong
	return true;
}

const bool Inventory::ExpandInventory(byte rowCount)
{
	std::lock_guard<std::mutex> lock(_invLock);
	byte inventoryRows = _slotCount / 8;
	if (inventoryRows + rowCount > (byte)INVENTORY_MAX_ROWS)
		return false;

	byte newSlotCount = rowCount * 8;

	for (size_t i = _slotCount; i < (_slotCount + newSlotCount); i++)
	{
		_slots.push_back(new InventorySlot(i + 40));
	}
	_slotCount += newSlotCount;

	return true;
}

const bool Inventory::ClearInventory(Client * caller)
{
	std::lock_guard<std::mutex> lock(_invLock);
	for (size_t i = 0; i < _slots.size(); i++)
	{
		if (_slots[i])
			_slots[i]->ClearSlot();
		
	}

	SendInventory(caller, 0);
	PlayerService::SendExternalChange(caller);
	_itemCount = _itemLevel = _profileItemLevel = 0;
	ClearGold();
	
	return true;
}

Stream* Inventory::GetItemsRAW()
{
	Stream* out = new Stream();
	std::lock_guard<std::mutex> lock(_invLock);
	out->WriteInt32(0); //count;
	int count = 0;
	for (size_t i = 0; i < _slots.size(); i++)
	{
		if (_slots[i] && _slots[i]->_isEmpty == 0)
		{
			count++;
			out->WriteInt32(_slots[i]->_id);
			SLOT_INFO * info = _slots[i]->_info;
			out->WriteInt32(info->_itemId);

			out->WriteByte(info->_hasCrystals);
			for (byte j = 0; j < info->_hasCrystals; j++)
				out->WriteInt32(info->_crystals[j]);

			out->WriteByte(info->_isMasterworked);
			out->WriteByte(info->_isAwakened);
			out->WriteByte(info->_isEnigmatic);
			out->WriteByte(info->_enchantLevel);
			out->WriteByte(info->_isBinded);
			out->WriteInt32(info->_binderEntityId);
			out->WriteByte(info->_isCrafted);
			out->WriteInt32(info->_crafterEntityId);
			out->WriteInt32(info->_stackCount);

			short passCount = out->NextPos();
			short pCount = 0;
			for (size_t j = 0; j < info->_passivities.size(); j++)
			{
				if (info->_passivities[j])
				{
					out->WriteInt32(info->_passivities[j]->_id);
					pCount++;
				}
				else
					out->WriteInt32(0);
			}
			out->_pos = passCount;
			out->WriteInt16(pCount);
			out->SetEnd();


		}
	}

	out->SetFront();
	out->WriteInt32(count);
	out->SetEnd();

	return out;
}

const bool Inventory::AddGold(long long gold)
{
	if (_maxGold > 0)
		if (_gold + gold >= _maxGold)
			return false;

	_gold += gold;
	return true;
}

const bool Inventory::TakeGold(long long gold)
{
	if ((int)_gold - gold < 0)
		return false;
	_gold -= gold;
	return true;
}

const bool Inventory::IsFull()
{
	return _itemCount == _slotCount;
}

void Inventory::ClearGold()
{
	_gold = 0;
}

void Inventory::Sort()
{
	Lock();
	std::vector<InventorySlot*> profileSlots;
	std::vector<InventorySlot*> toSort;

	for (size_t i = 0; i < 20; i++)
	{
		profileSlots.push_back(_slots[i]);
	}


	_slots.erase(_slots.begin(), _slots.begin() + 20);
	for (int i = 0; i < _slots.size(); i++)
	{
		if (_slots[i]->_isEmpty == 0)
		{
			toSort.push_back(_slots[i]);
		}
		else
		{
			delete _slots[i];
			_slots[i] == nullptr;
		}
	}

	_slots.clear();

	bool eaven = toSort.size() % 2 == 0 ? true : false;
	SLOT_INFO * temp = nullptr;
	int count = 0;
	if (eaven)
	{
		while (1)
		{
			if (count == toSort.size())
				break;
			for (size_t i = 0; i < toSort.size(); i += 2)
				if (toSort[i]->_info->_item->_sortingNumber < toSort[i + 1]->_info->_item->_sortingNumber)
				{
					temp = toSort[i]->_info;
					toSort[i]->_info = toSort[i + 1]->_info;
					toSort[i + 1]->_info = temp;
					count = 0;
					break;
				}
				else
					count++;

		}
	}
	else
	{
		int size = toSort.size() - 1;
		InventorySlot* e = toSort[size];
		toSort.erase(toSort.begin() + size);

		while (1)
		{
			if (count == size)
				break;

			for (size_t i = 0; i < size; i += 2)
				if (toSort[i]->_info->_item->_sortingNumber < toSort[i + 1]->_info->_item->_sortingNumber)
				{
					temp = toSort[i]->_info;
					toSort[i]->_info = toSort[i + 1]->_info;
					toSort[i + 1]->_info = temp;
					count = 0;
					break;
				}
				else
					count++;
		}

		bool found = false;
		for (size_t i = 0; i < size; i += 2)
		{
			if (toSort[i]->_info->_item->_sortingNumber <= e->_info->_item->_sortingNumber &&
				toSort[i + 1]->_info->_item->_sortingNumber >= e->_info->_item->_sortingNumber)
			{
				toSort.insert(toSort.begin() + i, e);
				found = true;
				break;
			}
		}
		if (!found)
		{
			toSort.push_back(e);
		}
	}

	for (int i = 0; i < profileSlots.size(); i++)
	{
		_slots.push_back(profileSlots[i]);
	}

	for (size_t i = 0; i < toSort.size(); i++)
	{
		_slots.insert(_slots.begin() + 20, toSort[i]);
	}

	int toInsert = _slotCount - toSort.size();
	if (toInsert > 0)
	{
		while (toInsert)
		{
			_slots.push_back(new InventorySlot(0));
			toInsert--;
		}

	}

	RedoSlotsIds();

	Unlock();
}

InventorySlot * Inventory::operator[](int j)
{
	std::lock_guard<std::mutex> lock(_invLock);
	for (size_t i = 0; i < _slots.size(); i++)
	{
		if (_slots[i] && _slots[i]->_id == j)
			return _slots[i];
	}
	return nullptr;
}

InventorySlot * Inventory::operator[](long long uid)
{
	std::lock_guard<std::mutex> lock(_invLock);
	for (size_t i = 0; i < _slots.size(); i++)
	{
		if (_slots[i] && _slots[i]->_isEmpty == 0 && _slots[i]->_info->_item->_entityId == (int)uid)
			return _slots[i];
	}
	return  nullptr;
}

void Inventory::operator<<(int itemId)
{
	std::lock_guard<std::mutex> lock(_invLock);
	int hasItem = -1;

	for (size_t i = 0; i < _slots.size(); i++)
	{
		if (_slots[i] && _slots[i]->_id > 20 && _slots[i]->_info->_itemId == itemId && _slots[i]->_info->_stackCount + 1 <= _slots[i]->_info->_item->_maxStack)
		{
			hasItem = i;
			break;
		}
	}

	if (hasItem >= 0)
	{
		_slots[hasItem]->_info->_stackCount++;
	}
	else
	{
		for (size_t i = 0; i < _slots.size(); i++)
		{
			if (_slots[i] && _slots[i]->_id > 20 && _slots[i]->_isEmpty == 1)
			{
				BuildItemInfoEx(_slots[i], itemId);
				_itemCount++;
				break;
			}
		}
	}
	RecalculateLevels();
}

void Inventory::SendInventory(Client * caller, byte show, bool broadcast)
{
	int itemCount = 0;
	Stream* data = new Stream();
	data->WriteInt16(0);
	data->WriteInt16(S_INVEN);

	short itemCountPos = data->NextPos();		//iventory itemsCount + equiped item Count

	short next = data->NextPos();

	data->WriteInt32(_owner->_entityId); //pid
	data->WriteInt32(_owner->_subId);

	data->WriteInt64(_gold);

	data->WriteByte(show);//show
	data->WriteByte(1);
	data->WriteByte(0);

	data->WriteInt32(_slotCount); //only inventory slotcount


	data->WriteInt32(_itemLevel);
	data->WriteInt32(_profileItemLevel);

	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);

	data->WriteInt32(330);
	data->WriteInt32(0);

	for (size_t i = 0; i < _slots.size(); i++)
	{
		if (_slots[i]->_isEmpty == 1)
			continue;
		itemCount++;

		InventorySlot * slot = _slots[i];
		data->WritePos(next);
		data->WriteInt16(data->_pos);
		next = data->NextPos();

		data->WriteInt32(slot->_info->_passivities.size());
		short passivities_pos = data->NextPos();

		data->WriteInt32(slot->_info->_itemId);

		data->WriteInt64(slot->_info->_item->_entityId); //item entity id
		data->WriteInt64(_owner->_lobbyId);

		data->WriteInt32(_slots[i]->_id);
		data->WriteInt32(0); //unk
		data->WriteInt64(_slots[i]->_info->_stackCount);
		data->WriteInt32(30); //unk 30

		data->WriteByte(0); //bined?
		data->WriteInt32(_slots[i]->_info->_crystals[0]);
		data->WriteInt32(_slots[i]->_info->_crystals[1]);
		data->WriteInt32(_slots[i]->_info->_crystals[2]);
		data->WriteInt32(_slots[i]->_info->_crystals[3]);

		data->WriteInt32(0); //unk
		data->WriteInt32(0); //apearance changed?
		data->WriteInt32(0); //unk
		data->WriteInt32(0); //unk
		data->WriteInt32(0); //unk	 effect?
		data->WriteInt32(0); //unk	 effect?
		data->WriteInt32(0); //unk	 effect?
		data->WriteInt32(0); //unk	 effect?
		data->WriteInt32(0); //unk
		data->WriteInt32(0); //unk

		data->WriteByte(0); //unk
		//data->WriteInt32(0);

		data->WriteInt32(_slots[i]->_info->_item->_itemLevel); //ilvs
		data->WriteInt32(_slots[i]->_info->_item->_itemLevel); //ilvs
		data->WriteInt32(_slots[i]->_info->_item->_itemLevel); //ilvs

		data->WriteInt32(0);
		data->WriteInt32(0);
		data->WriteInt32(0);

		data->WriteInt32(0);
		data->WriteInt32(0); // feedStock
		data->WriteInt32(0); //unk
		data->WriteInt32(0); //unk

		data->WriteByte(0); //unk

		data->WriteByte(-1);  //0x0FF
		data->WriteByte(-1);  //0x0FF
		data->WriteByte(-1);  //0x0FF
		data->WriteByte(-1);  //0x0FF

		data->WriteInt32(0);
		data->WriteInt16(0);
		data->WritePos(passivities_pos);
		for (size_t j = 0; j < _slots[i]->_info->_passivities.size(); j++)
			data->WriteInt32(_slots[i]->_info->_passivities[j]->_id);

		if (_slots[i]->_info->_passivities.size() == 0)data->WriteInt16(0);
	}

	data->_pos = itemCountPos;
	data->WriteInt16(itemCount);
	data->SetEnd();

	data->WriteInt16(0);

	data->WritePos(0);

	if (broadcast)
		BroadcastSystem::Broadcast(caller, data, ME, 0);
	else
		caller->Send(data);

	data->Clear();
}

void Inventory::BuildItemInfoEx(InventorySlot * slot, int itemId)
{
	if (itemId <= 0 || !slot || !slot->_info)
		return;

	IItem * item = InventoryService::ResolveItem(itemId);
	if (!item)
		return; //empty
	SLOT_INFO* out = slot->_info;
	slot->_isEmpty = 0;

	out->Clear();
	out->_item = item;
	out->_stackCount = 1;
	out->_itemId = itemId;


	if (item->_category == twohand || item->_category == axe || item->_category == circle || item->_category == bow || item->_category == staff || item->_category == rod || item->_category == lance || item->_category == dual || item->_category == blaster || item->_category == gauntlet || item->_category == shuriken ||
		item->_category == bodyMail || item->_category == handMail || item->_category == feetMail ||
		item->_category == bodyLeather || item->_category == handLeather || item->_category == feetLeather ||
		item->_category == bodyRobe || item->_category == handRobe || item->_category == feetRobe)
	{
		switch (item->_type)
		{

		case EQUIP_WEAPON:
		{



		}break;
		case EQUIP_ARMOR_BODY:
		{



		}break;
		case EQUIP_ARMOR_LEG:
			break;
		case EQUIP_ARMOR_ARM:
			break;
		}
	}

	std::string chuck = "";
	for (size_t i = 0; i < item->_linkPassivityId.size(); i++)
	{
		if (item->_linkPassivityId[i] == ';')
		{
			Passivity * newP = PassivityService::ResolvePassivity(atoi(chuck.c_str()));
			if (newP)
				out->_passivities.push_back(newP);

			chuck.clear();
			continue;
		}
		else if (item->_linkPassivityId[i] != ';'  && i == item->_linkPassivityId.size() - 1)
		{
			Passivity * newP = PassivityService::ResolvePassivity(atoi(chuck.c_str()));
			if (newP)
				out->_passivities.push_back(newP);
			break;
		}

		chuck += item->_linkPassivityId[i];
	}

}

void Inventory::GetStarterInventory(Player * p)
{
	if (!p)
		return;
	PlayerClass pClass = p->_playerInfo->pClass;
	if (p->_inventory)
		delete p->_inventory;

	p->_inventory = new Inventory(p);
	p->_inventory->Initialize(INVENTORY_START_SLOT_COUNT);

	Inventory* inv = p->_inventory;

	if (pClass == PlayerClass::WARRIOR || pClass == PlayerClass::ARCHER || pClass == PlayerClass::SLAYER || pClass == PlayerClass::REAPER)
	{
		BuildItemInfoEx((*inv)[PROFILE_ARMOR], 15004);
		BuildItemInfoEx((*inv)[PROFILE_GLOVES], 15005);
		BuildItemInfoEx((*inv)[PROFILE_BOOTS], 15006);
	}
	else if (pClass == PlayerClass::BERSERKER || pClass == PlayerClass::LANCER || pClass == PlayerClass::ENGINEER || pClass == PlayerClass::FIGHTER)
	{
		BuildItemInfoEx((*inv)[PROFILE_ARMOR], 15001);
		BuildItemInfoEx((*inv)[PROFILE_GLOVES], 15002);
		BuildItemInfoEx((*inv)[PROFILE_BOOTS], 15003);
	}
	else if (pClass == PlayerClass::SORCERER || pClass == PlayerClass::PRIEST || pClass == PlayerClass::MYSTIC || pClass == PlayerClass::ASSASSIN)
	{
		BuildItemInfoEx((*inv)[PROFILE_ARMOR], 15007);
		BuildItemInfoEx((*inv)[PROFILE_GLOVES], 15008);
		BuildItemInfoEx((*inv)[PROFILE_BOOTS], 15009);
	}

	switch (pClass)
	{
	case PlayerClass::WARRIOR:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10001);
		break;
	case PlayerClass::BERSERKER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10004);
		break;
	case PlayerClass::FIGHTER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 82005);
		break;
	case PlayerClass::ENGINEER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 55005);
		break;
	case PlayerClass::PRIEST:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10007);
		break;
	case PlayerClass::MYSTIC:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10008);
		break;
	case PlayerClass::ASSASSIN:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 58171);
		break;
	case PlayerClass::LANCER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10002);
		break;
	case PlayerClass::SLAYER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10003);
		break;
	case PlayerClass::SORCERER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10005);
		break;
	case PlayerClass::ARCHER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 10006);
		break;
	case PlayerClass::REAPER:
		BuildItemInfoEx((*inv)[PROFILE_WEAPON], 80396);
		break;
	}

	inv->_itemCount = 4;
}

void Inventory::Lock()
{
	_invLock.lock();
}

void Inventory::Unlock()
{
	_invLock.unlock();
}

void Inventory::RedoSlotsIds()
{
	for (size_t i = 0; i < _slots.size(); i++)
	{
		_slots[i]->_id = i + 1;
	}
}

void Inventory::RecalculateLevels()
{
	_itemLevel = 0;
	_profileItemLevel = 0; int count = 0;
	for (size_t j = 0; j < 20; j++)
		if (_slots[j]->_isEmpty == 0)
		{
			_profileItemLevel += _slots[j]->_info->_item->_itemLevel;
			count++;
		}
	if (_profileItemLevel && count)
		_profileItemLevel /= count;

	count = 0;
	for (size_t j = 0; j < _slots.size(); j++)
		if (_slots[j]->_id > 20 && _slots[j]->_isEmpty == 0)
		{
			_itemLevel += _slots[j]->_info->_item->_itemLevel;
			count++;
		}

	if (_itemLevel && count)
		_itemLevel /= count;
}
