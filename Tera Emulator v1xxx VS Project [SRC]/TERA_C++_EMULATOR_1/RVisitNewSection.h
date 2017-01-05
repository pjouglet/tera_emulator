#pragma once
#include "SendPacket.h"
class RVisitNewSection :
	public SendPacket
{
public:
	RVisitNewSection();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

