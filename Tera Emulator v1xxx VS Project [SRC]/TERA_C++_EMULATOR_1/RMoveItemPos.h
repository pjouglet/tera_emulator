#pragma once
#include "SendPacket.h"

class RMoveItemPos : public SendPacket
{
public:
	RMoveItemPos();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

