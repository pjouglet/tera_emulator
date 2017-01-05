#include "RTryLootDropItem.h"



RTryLootDropItem::RTryLootDropItem() : SendPacket(C_TRY_LOOT_DROPITEM)
{
}

void RTryLootDropItem::Process(OpCode opCode, Stream * data, Client * caller) const
{
	WorldSystem::LootItem(caller, data->ReadInt32());
}
