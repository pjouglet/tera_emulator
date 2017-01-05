#pragma once
#include "SendPacket.h"
class RGuardPkPolicy :
	public SendPacket
{
public:
	RGuardPkPolicy();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

