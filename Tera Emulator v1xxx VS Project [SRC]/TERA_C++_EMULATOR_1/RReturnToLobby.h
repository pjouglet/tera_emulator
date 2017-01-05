#pragma once
#include "SendPacket.h"
class RReturnToLobby :
	public SendPacket
{
public:
	RReturnToLobby();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

