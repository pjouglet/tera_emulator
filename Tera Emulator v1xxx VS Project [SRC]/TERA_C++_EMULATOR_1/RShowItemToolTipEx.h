#pragma once
#include "SendPacket.h"
class RShowItemToolTipEx :
	public SendPacket
{
public:
	RShowItemToolTipEx();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

