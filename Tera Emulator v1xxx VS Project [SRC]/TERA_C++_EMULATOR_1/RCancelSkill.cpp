#include "RCancelSkill.h"

RCancelSkill::RCancelSkill() : SendPacket(C_CANCEL_SKILL)
{
}

void RCancelSkill::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	int skill = stream->ReadInt32();
	int type = stream->ReadInt32();

	//todo
}