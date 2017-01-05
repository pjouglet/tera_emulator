#include "RRequestGameStatPing.h"



RRequestGameStatPing::RRequestGameStatPing() : SendPacket(C_REQUEST_GAMESTAT_PING)
{
}

void RRequestGameStatPing::Process(OpCode opCode, Stream * data, Client * caller)const
{
	data->Clear();
	data->WriteInt16(4);
	data->WriteInt16(S_RESPONSE_GAMESTAT_PONG);
	caller->Send(data);
}
