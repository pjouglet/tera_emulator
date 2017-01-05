#include "RGetPlayerGuildLogo.h"



RGetPlayerGuildLogo::RGetPlayerGuildLogo() : SendPacket(C_GET_USER_GUILD_LOGO)
{
}

void RGetPlayerGuildLogo::Process(OpCode opCode, Stream * data, Client * caller)const
{
	data->Clear();
	data->WriteInt16(8);
	data->WriteInt16(S_GET_USER_GUILD_LOGO);
	data->WriteInt32(0);
	BroadcastSystem::Broadcast(caller, data, ME, 0);
}