#include "RSimpleTipRepeatCheck.h"


RSimpleTipRepeatCheck::RSimpleTipRepeatCheck() : SendPacket(C_SIMPLE_TIP_REPEAT_CHECK)
{
}

void RSimpleTipRepeatCheck::Process(OpCode opCode, Stream * data, Client * caller)const
{
	int tip = data->ReadInt32();

	data->Clear();
	data->WriteInt16(11);
	data->WriteInt16(S_SIMPLE_TIP_REPEAT_CHECK);
	data->WriteInt32(tip);
	data->WriteInt16(1);
	data->WriteByte(0);
	BroadcastSystem::Broadcast(caller, data, ME, 0);
}