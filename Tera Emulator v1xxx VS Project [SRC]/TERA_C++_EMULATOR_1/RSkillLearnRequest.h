#pragma once
#include "SendPacket.h"
class RSkillLearnRequest :
	public SendPacket
{
public:
	RSkillLearnRequest();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

