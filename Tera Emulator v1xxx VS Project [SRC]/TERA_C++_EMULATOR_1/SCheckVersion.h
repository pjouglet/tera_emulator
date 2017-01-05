#ifndef SCHECKVERSION_H
#define SCHECKVERSION_H

#include "SendPacket.h"

class SCheckVersion : public SendPacket
{
public:
	SCheckVersion();

	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};
#endif
