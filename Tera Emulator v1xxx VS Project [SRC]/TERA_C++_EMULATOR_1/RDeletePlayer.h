#pragma once
#include "SendPacket.h"

class RDeletePlayer : public SendPacket
{
public:
	RDeletePlayer();
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

