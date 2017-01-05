#ifndef RCREATE_PLAYER_H
#define RCREATE_PLAYER_H

#include "SendPacket.h"
#include "mysql\MySqlDriver.h"

class RCreatePlayer : public SendPacket
{
public:
	RCreatePlayer();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};
#endif
