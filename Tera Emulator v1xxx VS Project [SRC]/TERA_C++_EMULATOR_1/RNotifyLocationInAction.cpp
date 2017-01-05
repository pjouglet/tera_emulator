#include "RNotifyLocationInAction.h"

RNotifyLocationInAction::RNotifyLocationInAction() : SendPacket(C_NOTIFY_LOCATION_IN_ACTION)
{
}

void RNotifyLocationInAction::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	int skill = stream->ReadInt32();
	int unk1 = stream->ReadInt32();

	float x = stream->ReadFloat();
	float y = stream->ReadFloat();
	float z = stream->ReadFloat();
	short heading = stream->ReadInt16();


	//todo the skill system
}