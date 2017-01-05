#pragma once
#include "SendPacket.h"
class RChat : public SendPacket
{
public:
	RChat();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

