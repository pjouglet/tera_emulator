#include "RCanCreatePlayer.h"
#include "PlayerService.h"
#include "Client.hpp"
#include "Account.hpp"

RCanCreatePlayer::RCanCreatePlayer() : SendPacket(C_CAN_CREATE_USER)
{
}

void RCanCreatePlayer::Process(OpCode opCode, Stream * data, Client * caller) const
{
	data->Clear();
	data->WriteInt16(5);
	data->WriteInt16(S_CAN_CREATE_USER);
	data->WriteByte((caller->GetAccount()->GetPlayerCount() < MAX_PLAYERS_PER_ACCOUNT) ? 1 : 0);
	caller->Send(data);
	data->Clear();
}