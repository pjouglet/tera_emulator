#include "RSkillLearnRequest.h"
#include "SkillService.h"
#include "Inventory.h"

RSkillLearnRequest::RSkillLearnRequest() : SendPacket(C_SKILL_LEARN_REQUEST)
{
}

void RSkillLearnRequest::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	Player *  p = caller->GetSelectedPlayer();
	if (!p)
		return;

	int unk1 = stream->ReadInt32();
	short skillId = stream->ReadInt16();
	short unk2 = stream->ReadInt16();
	byte unk3 = stream->ReadByte();
	bool result = SkillService::LearnNewSkill(caller, skillId);
	if (result)
		SkillService::SendSkillList(caller, false);

	p->_inventory->SendInventory(caller, 0, false);

	stream->Clear();
	stream->WriteInt16(14);
	stream->WriteInt16(S_SKILL_LEARN_RESULT);
	stream->WriteInt16(result ? 1 : 0);
	stream->WriteInt32((int)unk3);
	stream->WriteInt32(skillId);
	caller->Send(stream);
}
