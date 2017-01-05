#include "RDungeonClearCountList.h"



RDungeonClearCountList::RDungeonClearCountList() :SendPacket(C_DUNGEON_CLEAR_COUNT_LIST)
{
}

void RDungeonClearCountList::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;

	data->ReadInt16();
	std::string _playerName = data->ReadUTF16StringBigEdianToASCII();

	data->Clear();
	data->WriteInt16(8);
	data->WriteInt16(S_DUNGEON_CLEAR_COUNT_LIST);
	data->WriteInt32(0); //todo
	data->WriteInt32(3659340); //0x4CD63700

	caller->Send(data);
}