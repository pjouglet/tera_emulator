#pragma once
#include "SendPacket.h"

class RMovePlayer : public SendPacket
{
public:
	RMovePlayer();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

