#include "SendPacket.h"

SendPacket::SendPacket(OpCode toRecv,bool ordered)
{
	_toRecv = toRecv;
	_orderedPacket = ordered;
}
