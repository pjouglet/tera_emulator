#include "RShowInven.h"
#include "Inventory.h"
RShowInven::RShowInven() : SendPacket(C_SHOW_INVEN)
{
}

void RShowInven::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player * p = nullptr;
	if ((p = caller->GetSelectedPlayer()))
		p->_inventory->SendInventory(caller, 1);
}
