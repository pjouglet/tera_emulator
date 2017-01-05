#include "RGuardPkPolicy.h"



RGuardPkPolicy::RGuardPkPolicy() : SendPacket(C_GUARD_PK_POLICY)
{
}

void RGuardPkPolicy::Process(OpCode opCode, Stream * data, Client * caller)const
{
	data->Clear();
	data->WriteInt16(7);
	data->WriteInt16(S_GUARD_PK_POLICY);
	data->WriteInt16(1);
	data->WriteByte(0);
	BroadcastSystem::Broadcast(caller, data, ME, 0);
}