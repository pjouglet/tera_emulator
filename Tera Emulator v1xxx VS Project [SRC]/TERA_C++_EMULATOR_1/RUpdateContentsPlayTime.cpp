#include "RUpdateContentsPlayTime.h"


RUpdateContentsPlayTime::RUpdateContentsPlayTime() : SendPacket(C_UPDATE_CONTENTS_PLAYTIME)
{
}

void RUpdateContentsPlayTime::Process(OpCode opCode, Stream * data, Client * caller)const
{
	//todo
}