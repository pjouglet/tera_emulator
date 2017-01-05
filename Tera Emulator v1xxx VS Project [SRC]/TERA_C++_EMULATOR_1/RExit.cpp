#include "RExit.h"


RExit::RExit() : SendPacket(C_EXIT)
{
}

void RExit::Process(OpCode opCode, Stream * data, Client * caller) const
{
	data->Clear();
	data->WriteInt16(5);
	data->WriteInt16(S_EXIT);
	data->WriteByte(1);

	BroadcastSystem::Broadcast(caller, data, ME, 0);
}