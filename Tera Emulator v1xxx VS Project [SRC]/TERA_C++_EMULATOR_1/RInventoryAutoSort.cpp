#include "RInventoryAutoSort.h"
#include "Inventory.h"


RInventoryAutoSort::RInventoryAutoSort() : SendPacket(C_INVENTORY_AUTO_SORT)
{
}

void RInventoryAutoSort::Process(OpCode opCode, Stream * data, Client * caller) const
{
	return;
	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;
	Inventory * inv = p->_inventory;

	int unk1 = data->ReadInt32();
	int unk2 = data->ReadInt32();
	int unk3 = data->ReadInt32();

	inv->Sort();
	inv->SendInventory(caller, 0, false);
}
