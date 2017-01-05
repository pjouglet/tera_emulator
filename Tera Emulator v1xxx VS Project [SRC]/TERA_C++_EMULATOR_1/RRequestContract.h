#pragma once
#include "SendPacket.h"
class RRequestContract :
	public SendPacket
{
public:
	RRequestContract();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

