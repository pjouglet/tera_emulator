#include "RReturnToLobby.h"



RReturnToLobby::RReturnToLobby() : SendPacket(C_RETURN_TO_LOBBY)
{
}

void RReturnToLobby::Process(OpCode opCode, Stream * data, Client * caller)const
{//todo

	WorldSystem::ExitWorld(caller);
	data->Clear();
	data->WriteInt16(8);
	data->WriteInt16(S_PREPARE_RETURN_TO_LOBBY);
	data->WriteInt32(0); //seconds
	caller->Send(data);
	
	data->Clear();
	data->WriteInt16(5);
	data->WriteInt16(S_RETURN_TO_LOBBY);
	data->WriteByte(1);
	caller->Send(data);
}
