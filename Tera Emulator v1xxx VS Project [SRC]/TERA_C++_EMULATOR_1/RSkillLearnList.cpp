#include "RSkillLearnList.h"
#include "SkillService.h"


RSkillLearnList::RSkillLearnList() :SendPacket(C_SKILL_LEARN_LIST)
{
}

void RSkillLearnList::Process(OpCode opCode, Stream * data, Client * caller)const
{
	int unk = data->ReadInt32(); //-1 ??

	SkillService::SendSkillLearnList(caller, false);
}