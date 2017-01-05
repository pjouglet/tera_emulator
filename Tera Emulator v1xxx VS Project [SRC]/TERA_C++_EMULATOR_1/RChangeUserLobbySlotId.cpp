#include "RChangeUserLobbySlotId.h"
#include "Client.hpp"
#include "Account.hpp"
#include "Player.hpp"


RChangeUserLobbySlotId::RChangeUserLobbySlotId() : SendPacket(C_CHANGE_USER_LOBBY_SLOT_ID)
{
}

void RChangeUserLobbySlotId::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	Account * a = caller->GetAccount();
	if (!a)
		return;

	short id1 = stream->ReadInt16();
	stream->_pos = 22;
	short id2 = stream->ReadInt16();

	//todo
}