#pragma once
#include "SendPacket.h"
class REventGuide :
	public SendPacket
{
public:
	REventGuide();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

