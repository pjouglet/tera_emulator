#pragma once
#include "SendPacket.h"
class RShowInven: public SendPacket
{
public:
	RShowInven();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

