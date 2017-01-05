#include "InventorySlot.h"
#include "IItem.h"


InventorySlot::InventorySlot(int id)
{
	_isEmpty = 1;
	_id = id;
	_info = new SLOT_INFO();
}
InventorySlot::~InventorySlot()
{
	if (_info)
	{
		_info->_item = 0;
		delete _info;
		_info = 0;
	}
}

const bool InventorySlot::ClearSlot()
{
	_info->Clear();
	_isEmpty = 1;
	return true;
}

const bool InventorySlot::operator<<(IItem * item)
{
	if (!_info)
		return false;
	_info->_item = item;

	return true;
}

const bool InventorySlot::operator<<(SLOT_INFO * info)
{
	return false;
}

const bool InventorySlot::operator >> (InventorySlot * slot)
{
	if (!slot || slot->_info) //we put me info to you info[null]
		return false;
	slot->_info = _info;
	ClearSlot();
	return true;
}

const bool InventorySlot::operator^(InventorySlot * slot)
{
	if (!slot || !slot->_info || !_info || slot == this)
		return false;

	byte emptyTemp = _isEmpty;
	_isEmpty = slot->_isEmpty;
	slot->_isEmpty = emptyTemp;
	//switch emptyVar

	SLOT_INFO *  temp = slot->_info;
	slot->_info = _info;
	_info = temp;

	return true;
}

InventorySlot::operator int()
{
	if (_info && _info->_item)
		return _info->_item->_entityId;
	return 0;
}

SLOT_INFO::SLOT_INFO()
{
	memset(this, 0, sizeof SLOT_INFO);
}

SLOT_INFO::SLOT_INFO(int itemid, int stackCount, int * crystals, byte crystalCount, IItem * item, byte enchantLevel, int binderEI, int crafterEI)
{
	_itemId = itemid;
	_stackCount = stackCount;
	_hasCrystals = crystalCount;
	memset(crystals, 0, sizeof(int) * 4);
	for (byte i = 0; i < crystalCount; i++)
		_crystals[i] = crystals[i];

	_item = item;
	_isBinded = binderEI == 0 ? 0 : 1;
	_binderEntityId = binderEI;
	_isCrafted = crafterEI == 0 ? 0 : 1;
	_crafterEntityId = crafterEI;
	_enchantLevel = enchantLevel;
}

void SLOT_INFO::Clear()
{
	_passivities.clear();
	memset(this, 0, sizeof SLOT_INFO);
}
