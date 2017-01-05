#include "RDungeonCoolTimeList.h"

RDungeonCoolTimeList::RDungeonCoolTimeList() : SendPacket(C_DUNGEON_COOL_TIME_LIST)
{
}

void RDungeonCoolTimeList::Process(OpCode opCode, Stream * data, Client * caller) const
{
	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;

	data->Clear();
	data->WriteInt16(12);
	data->WriteInt16(S_DUNGEON_COOL_TIME_LIST);
	data->WriteInt32(0);
	data->WriteInt32(0);

	caller->Send(data);
}