#include "RMoveItemPos.h"
#include "Inventory.h"
#include "InventorySlot.h"
#include "MessagingSystem.h"

RMoveItemPos::RMoveItemPos() : SendPacket(C_MOVE_INVEN_POS)
{
}

void RMoveItemPos::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;

	int playerEntityId = data->ReadInt32();
	int playerSubid = data->ReadInt32();

	int slot1Id = data->ReadInt32();
	int slot2Id = data->ReadInt32();

	if (slot1Id < 40 || slot1Id > p->_inventory->_slotCount + 40 || slot2Id < 40 || slot2Id> p->_inventory->_slotCount + 40)
		return; //be withing bounds of inventory

	p->_inventory->Lock();
	InventorySlot * slot1 = (*p->_inventory)[slot1Id];
	InventorySlot * slot2 = (*p->_inventory)[slot2Id];

	if (slot2->_isEmpty == 0)
	{
		//todo [combine item]
		MessagingSystem::SendSystemMessage(caller, "Can't combine those items!");
	}
	else
		(*slot1) ^ slot2; //just interchange
	p->_inventory->Unlock();

	p->_inventory->SendInventory(caller, 1, false);


	data->Clear();
	data->WriteInt16(0);
	data->WriteInt16(S_INVEN_CHANGEDSLOT);

	data->WriteInt16(2); //count
	short next = data->NextPos();
	for (short i = 0; i < 2; i++)
	{
		data->WritePos(next);
		data->WriteInt16(data->_pos);
		next = data->NextPos();

		data->WriteByte(1); //bool what?
		data->WriteInt32(i == 0 ? slot1Id : slot2Id);
	}
	data->WritePos(0);
	caller->Send(data);


}
