#include "RDelItem.h"
#include "Inventory.h"
#include "InventorySlot.h"
#include "IItem.h"

RDelItem::RDelItem(): SendPacket(C_DEL_ITEM)
{

}

void RDelItem::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;

	int playerEntityId = data->ReadInt32();
	int playerSubId = data->ReadInt32();

	int slotOffset = data->ReadInt32();

	int unk = data->ReadInt32();

	InventorySlot*  slot = (*p->_inventory)[slotOffset + 40];

	if (slot)
	{
		WorldSystem::DropItem(caller, slot->_info->_itemId);
		slot->ClearSlot();
		p->_inventory->_itemCount--;
		p->_inventory->SendInventory(caller, 0);
	}
}
//data->Clear();
//data->WriteInt16(0);
//data->WriteInt16(S_SPAWN_DROPITEM);
//
//data->WriteInt16(0);
//short ownersPos = data->NextPos();
//
//data->WriteInt64(slot->_info->_item->_entityId);
//data->WriteFloat(p->_position->_X + 10);
//data->WriteFloat(p->_position->_Y + 10);
//data->WriteFloat(p->_position->_Z);
//data->WriteInt32(slot->_info->_itemId);
//data->WriteInt32(slot->_info->_stackCount);
//data->WriteInt32(0);
//data->WriteInt32(0);
//data->WriteInt16(0);
//data->WriteInt32(0);
//data->WriteInt32(0);
//data->WritePos(ownersPos);
//data->WriteInt16(0);
//
//data->WritePos(0);
//caller->Send(data);


