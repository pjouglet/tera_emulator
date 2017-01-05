#include "REventGuide.h"

REventGuide::REventGuide() : SendPacket(C_EVENT_GUIDE)
{
}

void REventGuide::Process(OpCode opCode, Stream * data, Client * caller)const
{
	data->WriteInt16(8);
	data->WriteInt16(S_EVENT_GUIDE);
	data->WriteInt32(0);


	BroadcastSystem::Broadcast(caller, data, ME, 0);
}