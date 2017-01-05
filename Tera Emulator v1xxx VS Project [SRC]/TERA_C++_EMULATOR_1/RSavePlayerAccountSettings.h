#pragma once

#include "SendPacket.h"
class RSavePlayerAccountSettings :public SendPacket
{
public:
	RSavePlayerAccountSettings();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

