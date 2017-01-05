#pragma once
#include "SendPacket.h"
class REquipItem : public SendPacket
{
public:
	REquipItem();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

