#ifndef RCAN_CREATE_PLAYER_H
#define RCAN_CREATE_PLAYER_H

#include "SendPacket.h"

class RCanCreatePlayer :public SendPacket
{
public:
	RCanCreatePlayer();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};
#endif
