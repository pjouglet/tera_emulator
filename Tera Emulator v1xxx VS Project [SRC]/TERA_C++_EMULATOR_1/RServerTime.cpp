#include "RServerTime.h"


RServerTime::RServerTime() : SendPacket(C_SERVER_TIME)
{
}

void RServerTime::Process(OpCode opCode, Stream * data, Client * caller)const
{
	data->WriteInt16(14);
	data->WriteInt16(S_SERVER_TIME);
	data->WriteInt64(ServerTimer::GetCurrentUTC());
	data->WriteInt16(0);

	BroadcastSystem::Broadcast(caller, data, ME, 0);
}
