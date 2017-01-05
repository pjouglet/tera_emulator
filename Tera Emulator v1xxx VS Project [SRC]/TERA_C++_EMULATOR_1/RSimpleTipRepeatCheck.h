#pragma once
#include "SendPacket.h"
class RSimpleTipRepeatCheck :
	public SendPacket
{
public:
	RSimpleTipRepeatCheck();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

