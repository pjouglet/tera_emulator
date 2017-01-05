#pragma once

#include "SendPacket.h"
class RChangeUserLobbySlotId : public SendPacket
{
public:
	RChangeUserLobbySlotId();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

