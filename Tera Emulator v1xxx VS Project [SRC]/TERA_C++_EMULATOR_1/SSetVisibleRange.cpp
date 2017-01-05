#include "SSetVisibleRange.h"
#include "Client.hpp"
#include "Account.hpp"

SSetVisibleRange::SSetVisibleRange() : SendPacket(C_SET_VISIBLE_RANGE)
{
}

void SSetVisibleRange::Process(OpCode opCode, Stream * data, Client * caller) const
{
	Player * p = nullptr;
	if ((p = caller->GetSelectedPlayer()))
		p->_visibleRange = data->ReadInt32();
}