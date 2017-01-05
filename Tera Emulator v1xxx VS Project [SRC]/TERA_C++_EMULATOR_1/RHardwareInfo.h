#pragma once
#include "SendPacket.h"

class RHardwareInfo :
	public SendPacket
{
public:
	RHardwareInfo();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

