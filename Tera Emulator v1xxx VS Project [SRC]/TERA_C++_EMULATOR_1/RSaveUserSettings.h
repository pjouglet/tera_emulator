#pragma once
#include "SendPacket.h"
class RSaveUserSettings :
	public SendPacket
{
public:
	RSaveUserSettings();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

