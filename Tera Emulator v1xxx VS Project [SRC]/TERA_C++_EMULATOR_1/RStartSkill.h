#pragma once
#include "SendPacket.h"

class RStartSkill :
	public SendPacket
{
public:
	RStartSkill();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

