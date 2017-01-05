#pragma once
#include "SendPacket.h"
class RLoadTopoFin :
	public SendPacket
{
public:
	RLoadTopoFin();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

