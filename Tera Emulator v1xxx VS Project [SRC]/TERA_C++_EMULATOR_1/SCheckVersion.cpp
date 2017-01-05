#include "SCheckVersion.h"

SCheckVersion::SCheckVersion() : SendPacket(C_CHECK_VERSION)
{
}

void SCheckVersion::Process(OpCode opCode, Stream * data, Client * caller) const
{
	data->Clear();
	data->WriteInt16(5);
	data->WriteInt16(S_CHECK_VERSION);
	data->WriteByte(1);

	caller->Send(data);
}
