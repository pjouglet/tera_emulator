#pragma once
#include "SendPacket.h"
class RRequestUserItemLevelInfo :
	public SendPacket
{
public:
	RRequestUserItemLevelInfo();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

