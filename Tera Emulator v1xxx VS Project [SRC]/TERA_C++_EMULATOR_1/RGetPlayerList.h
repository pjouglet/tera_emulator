#ifndef GET_PLAYER_LIST_H
#define GET_PLAYER_LIST_H

#include "SendPacket.h"
#include <vector>

class RGetPlayerList : public SendPacket
{
public:
	RGetPlayerList();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

#endif





			
