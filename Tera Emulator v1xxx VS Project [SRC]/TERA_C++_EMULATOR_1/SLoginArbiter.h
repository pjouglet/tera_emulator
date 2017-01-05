#ifndef SLOGINARBITER_H
#define SLOGINARBITER_H

#include "SendPacket.h"

class SLoginArbiter : public SendPacket
{
public:
	SLoginArbiter();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

#endif