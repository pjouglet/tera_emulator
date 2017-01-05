#pragma once
#include "SendPacket.h"
class RNotifyLocationInAction :
	public SendPacket
{
public:
	RNotifyLocationInAction();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

