#pragma once
#include "SendPacket.h"
class RGetPlayerGuildLogo : public SendPacket
{
public:
	RGetPlayerGuildLogo();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

