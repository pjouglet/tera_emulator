#include "RCancelDeletePlayer.h"


RCancelDeletePlayer::RCancelDeletePlayer() : SendPacket(C_CANCEL_DELETE_USER)
{
}

void RCancelDeletePlayer::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Account * a = caller->GetAccount();
	if (!a)
		return;

	int id = data->ReadInt32();
	a->GetPlayerByLobbyId(id)->_banTimeUTC = 0;

	data->Clear();
	data->WriteInt16(5);
	data->WriteInt16(S_CANCEL_DELETE_USER);
	data->WriteByte(1);
	caller->Send(data);
	data->Clear();
}