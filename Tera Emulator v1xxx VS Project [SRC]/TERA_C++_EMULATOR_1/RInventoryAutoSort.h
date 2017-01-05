#pragma once
#include "SendPacket.h"
class RInventoryAutoSort :
	public SendPacket
{
public:
	RInventoryAutoSort();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

