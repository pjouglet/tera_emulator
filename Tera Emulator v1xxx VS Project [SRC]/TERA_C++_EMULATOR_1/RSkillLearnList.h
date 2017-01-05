#pragma once
#include "SendPacket.h"
class RSkillLearnList :public SendPacket
{
public:
	RSkillLearnList();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

