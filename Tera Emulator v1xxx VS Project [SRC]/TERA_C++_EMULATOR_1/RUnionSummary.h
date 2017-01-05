#pragma once
#include "SendPacket.h"
class RUnionSummary :
	public SendPacket
{
public:
	RUnionSummary();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

