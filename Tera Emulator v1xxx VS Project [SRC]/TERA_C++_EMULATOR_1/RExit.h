#pragma once
#include "SendPacket.h"
class RExit : public SendPacket
{
public:
	RExit();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)  const override;
};

