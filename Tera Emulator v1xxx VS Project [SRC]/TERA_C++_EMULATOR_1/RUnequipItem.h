#pragma once
#include "SendPacket.h"
class RUnequipItem :
	public SendPacket
{
public:
	RUnequipItem();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

