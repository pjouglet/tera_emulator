#pragma once
#include "SendPacket.h"
class RDungeonCoolTimeList :
	public SendPacket
{
public:
	RDungeonCoolTimeList();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

