#pragma once
#include "SendPacket.h"
class RRequestGameStatPing: public SendPacket
{
public:
	RRequestGameStatPing();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

