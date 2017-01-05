#pragma once
#include "SendPacket.h"
class RReqVipSystemInfo :
	public SendPacket
{
public:
	RReqVipSystemInfo();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

