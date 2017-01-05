#include "RDeletePlayer.h"

RDeletePlayer::RDeletePlayer() : SendPacket(C_DELETE_USER)
{
}

void RDeletePlayer::Process(OpCode opCode, Stream * data, Client * caller)const
{
	int id = data->ReadInt32();
	bool result = false;
	Player * p = caller->GetAccount()->GetPlayerByLobbyId(id);
	if (p)
	{
		if (p->_stats._level > 40)
		{
			p->_banTimeUTC = ServerTimer::GetCurrentUTC() + 86400; //1 day
		}
		else
			p->_toDelete = 1;

		result = true;
	}

	data->Clear();
	data->WriteInt16(5);
	data->WriteInt16(S_DELETE_USER);
	data->WriteByte(result == true ? 1 : 0);
	caller->Send(data);
	data->Clear();
}