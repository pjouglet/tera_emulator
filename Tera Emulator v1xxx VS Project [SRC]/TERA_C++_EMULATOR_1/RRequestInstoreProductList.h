#pragma once
#include "SendPacket.h"
class RRequestInstoreProductList :
	public SendPacket
{
public:
	RRequestInstoreProductList();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

