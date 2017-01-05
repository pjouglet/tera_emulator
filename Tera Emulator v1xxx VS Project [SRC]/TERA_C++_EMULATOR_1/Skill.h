#ifndef SKILL_H
#define SKILL_H

#include <vector>
#include <string>

#include "SkillStructs.h"
#include "ProjectileStructs.h"


class Skill
{
public:
	Skill();
	std::vector<Targeting> _targetingList;

	int
		_nextSkill,
		_templateId,
		_id,
		_baseId,
		_level,
		_needSkill,
		_parentId,
		_totalStk,
		_totalStkPvP;

	std::vector<SkillAction> _actions;
	std::string
		_category,
		_name;

	float
		_attackRangeMax,
		_attackRange,
		_totalAttack,
		_timeRate,
		_totalAtk;

	bool
		_autoUse,
		_needWeapon,
		_changeDirToChanter,
		_keepMovingCharge,
		_keptMovingCharge,
		_useSkillWhileReaction;

		
	SkillType _type;
	PushTarget _pushtarget;
	Animation _animation;
	CharginStageList _chargingStageList;
	Precondition _precondition;
	ProjectileData _projectileData;
	PushTarget _pushTarget;
	AdjustTargetingPos _adjustTargetingPos;
};

#endif