#include "RCheckUsername.h"
#include "PlayerService.h"


RCheckUsername::RCheckUsername() : SendPacket(C_CHECK_USERNAME)
{
}

void RCheckUsername::Process(OpCode opCode, Stream * data, Client * caller)const
{
	short nameOffset = data->ReadInt16();
	
	std::string name = data->ReadUTF16StringBigEdianToASCII();
	byte  b = PlayerService::CheckPlayerName(name);

	data->Clear();
	data->WriteInt16(0);
	data->WriteInt16(S_CHECK_USERNAME);
	data->WriteByte(b);
	data->WritePos(0);

	caller->Send(data);
	data->Clear();
}