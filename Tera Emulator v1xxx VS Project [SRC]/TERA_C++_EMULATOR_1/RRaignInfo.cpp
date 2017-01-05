#include "RRaignInfo.h"


RRaignInfo::RRaignInfo() : SendPacket(C_REIGN_INFO)
{
}

void RRaignInfo::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	int unk1 = stream->ReadInt32();

	stream->Clear();
	stream->WriteInt16(18);
	stream->WriteInt16(S_REIGN_INFO);
	stream->WriteInt16(12);//unk
	stream->WriteInt16(14);//unk

	stream->WriteInt32(unk1);
	stream->WriteInt32(0);
	stream->WriteInt16(0);
	BroadcastSystem::Broadcast(caller, stream, ME, 0);
}
