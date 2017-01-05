#include "RTradeBrokerHighestItemLevel.h"


RTradeBrokerHighestItemLevel::RTradeBrokerHighestItemLevel() : SendPacket(C_TRADE_BROKER_HIGHEST_ITEM_LEVEL)
{
}

void RTradeBrokerHighestItemLevel::Process(OpCode opCode, Stream * data, Client * caller)const
{
	data->WriteInt16(0);
	data->WriteInt16(S_TRADE_BROKER_HIGHEST_ITEM_LEVEL);
	data->WriteHexString("550200000000");
	data->WritePos(0);

	BroadcastSystem::Broadcast(caller, data, ME, 0);
}