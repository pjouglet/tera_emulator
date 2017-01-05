#pragma once
#include "SendPacket.h"
class RCancelDeletePlayer :
	public SendPacket
{
public:
	RCancelDeletePlayer();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

