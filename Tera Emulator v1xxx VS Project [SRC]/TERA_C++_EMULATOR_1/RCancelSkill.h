#pragma once
#include "SendPacket.h"
class RCancelSkill : public SendPacket
{
public:
	RCancelSkill();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

