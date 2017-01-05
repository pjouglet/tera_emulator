#include "RUnequipItem.h"



RUnequipItem::RUnequipItem() :SendPacket(C_UNEQUIP_ITEM)
{
}

void RUnequipItem::Process(OpCode opCode, Stream * data, Client * caller) const
{
}
