#pragma once
#include "SendPacket.h"
class RTryLootDropItem :
	public SendPacket
{
public:
	RTryLootDropItem();
	

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;

};

