#pragma once
#include "SendPacket.h"
class RRaignInfo :
	public SendPacket
{
public:
	RRaignInfo();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

