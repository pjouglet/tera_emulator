#pragma once
#include "SendPacket.h"
class RDungeonClearCountList :
	public SendPacket
{
public:
	RDungeonClearCountList();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

