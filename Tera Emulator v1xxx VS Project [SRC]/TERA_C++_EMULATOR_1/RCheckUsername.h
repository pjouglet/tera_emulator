#pragma once
#include "SendPacket.h"
class RCheckUsername :
	public SendPacket
{
public:
	RCheckUsername();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

