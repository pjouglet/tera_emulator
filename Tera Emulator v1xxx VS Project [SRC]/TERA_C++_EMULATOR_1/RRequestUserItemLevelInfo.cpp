#include "RRequestUserItemLevelInfo.h"
#include "Inventory.h"


RRequestUserItemLevelInfo::RRequestUserItemLevelInfo() :SendPacket(C_REQUEST_USER_ITEMLEVEL_INFO)
{
}

void RRequestUserItemLevelInfo::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;


	stream->Clear();
	stream->WriteInt16(12);
	stream->WriteInt16(S_USER_ITEMLEVEL_INFO);
	stream->WriteInt32(p->_inventory->_itemLevel); //warehouse itemlevel
	stream->WriteInt32(p->_inventory->_profileItemLevel); //inventory and warehouse itemlevel
	
	BroadcastSystem::Broadcast(caller, stream, ME, 0);
}