#pragma once
#include "SendPacket.h"

class RDelItem: public SendPacket
{
public:
	RDelItem();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

