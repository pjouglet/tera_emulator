#include "SkillStructs.h"

Cost::Cost()
{
	HP = 0;
	MP = 0;
}

Cost * Cost::Clone()
{
	Cost * out = new Cost();
	if (HP == 0 && MP == 0)
		return out;
	memcpy_s((void*)out, sizeof Cost, (const void*)this, sizeof Cost);
	return out;
}

Precondition::Precondition()
{
	cost = Cost();
	coolTime = 0;
	exclusiveAbnormality = 0;
	modeChangeMethod = 0;
	modeNo = 0;
}

Precondition * Precondition::Clone()
{
	Precondition * out = new Precondition();
	memcpy_s((void*)out, sizeof Precondition, (const void*)this, sizeof Precondition);
	return out;
}

Animation::Animation()
{
	dir = 0;
	duraction = 0;
	rootMotion = false;
	rootRotate = false;
	rotateYaw = 0;
}

Animation * Animation::Clone()
{
	Animation * out = new Animation();
	memcpy_s(out, sizeof Animation, this, sizeof Animation);
	return out;
}

AnimSeq::AnimSeq()
{
	memset(this, 0, sizeof AnimSeq);
}

AnimSeq * AnimSeq::Clone()
{
	AnimSeq* out = new AnimSeq();
	memcpy_s(out, sizeof AnimSeq, this, sizeof AnimSeq);
	return out;
}

ActionStage::ActionStage()
{
	memset(this, 0, sizeof ActionStage);
}

ActionStage * ActionStage::Clone()
{
	ActionStage* out = new ActionStage();
	memcpy_s(out, sizeof ActionStage, this, sizeof ActionStage);

	return out;
}

SkillAction::SkillAction()
{
	memset(this, 0, sizeof SkillAction);
}

SkillAction * SkillAction::Clone()
{
	SkillAction* out = new SkillAction();
	memcpy_s(out, sizeof SkillAction, this, sizeof SkillAction);
	return out;
}

ChargeStage::ChargeStage()
{
	memset(this, 0, sizeof ChargeStage);
}

