#ifndef SSET_VISIBLE_RANGE_H
#define SSET_VISIBLE_RANGE_H

#include "SendPacket.h"

class SSetVisibleRange : public SendPacket
{
public:
	SSetVisibleRange();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

#endif