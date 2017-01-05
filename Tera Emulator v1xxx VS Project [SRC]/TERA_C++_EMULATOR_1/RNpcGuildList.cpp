#include "RNpcGuildList.h"


RNpcGuildList::RNpcGuildList() : SendPacket(C_NPCGUILD_LIST)
{
}

void RNpcGuildList::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;
	short nameOffset = data->ReadInt16();

	data->_pos = nameOffset;
	std:: string _playerName = data->ReadUTF16StringBigEdianToASCII();

	short npcGuildCount = 1;
	data->Clear();

	data->WriteInt16(0);
	data->WriteInt16(S_NPCGUILD_LIST);
	data->WriteInt16(npcGuildCount); //npc guild count [faction]
	short next_pos = data->NextPos();

	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);

	for (short i = 0; i < npcGuildCount; i++)
	{
		data->WritePos(next_pos);
		data->WriteInt16(data->_pos);
		next_pos = data->_pos;

		data->WriteInt32(9); //region
		data->WriteInt32(610); //faction
		data->WriteInt32(6); //rank  # enum { suspicious = 0, apprehensive = 3, wavering, neutral, favorable, friendly, trusted, revered }
		data->WriteInt32(0); //reputation
		data->WriteInt32(0); //credits
	}
	
	
	data->WritePos(0);
	caller->Send(data);
}