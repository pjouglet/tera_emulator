#pragma once
#include "SendPacket.h"
class RServerTime :public SendPacket
{
public:
	RServerTime();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

