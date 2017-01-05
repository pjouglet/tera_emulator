#include "RVisitNewSection.h"
#include "Area.h"

RVisitNewSection::RVisitNewSection() : SendPacket(C_VISIT_NEW_SECTION)
{
}

void RVisitNewSection::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player * p = 0;
	if (!(p = caller->GetSelectedPlayer()))
		return;

	//0001 0000 0019 0000 D9230900
	int worldMapWorldId = data->ReadInt16();
	data->ReadInt16(); //unk1

	int worldMapGuardId = data->ReadInt16();
	data->ReadInt16(); //unk1

	int worldMapSectionId = data->ReadInt32();

	p->_position->_worldMapWorldId = worldMapWorldId;
	p->_position->_worldMapGuardId = worldMapGuardId;
	p->_position->_worldMapSectionId = worldMapSectionId;

	//todo save sactionsIds so we can send them [for map to be discovered]...

	data->Clear();
	data->WriteInt16(19);
	data->WriteInt16(S_VISIT_NEW_SECTION);
	data->WriteByte(1);
	data->WriteInt32(p->_position->_worldMapWorldId);
	data->WriteInt32(p->_position->_worldMapGuardId);
	data->WriteInt32(p->_position->_worldMapSectionId);
	data->WriteInt16(0);
	BroadcastSystem::Broadcast(caller, data, ME, 0);
}

