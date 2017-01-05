#pragma once
#include "SendPacket.h"
class RTradeBrokerHighestItemLevel :
	public SendPacket
{
public:
	RTradeBrokerHighestItemLevel();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

