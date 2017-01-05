#ifndef PROJECTILE_STRUCTS_H
#define PROJECTILE_STRUCTS_H

#include "AreaEffect.h"
#include "SkillStructs.h"
#include "ProjectileSkill.h"

enum TargetingAreaType : int
{
	EnemyOrPvP = 0,
	Me = 1,
	Enemy = 2,
	PvP = 3,
	AAll = 4,
	AllIncludeVillager = 5,
	AllyOnDeath = 6,
	AllyVillager = 7,
	Ally = 8,
	Party = 9,
	AllyExceptMe = 10,
	PartyExceptMe = 11,
	AllExceptMe = 12,
	No = 13
};

enum AdjustTargetingPos
{
	notUse,
};

enum TargetingType : short
{
	None
};

enum TargetingMethod:short
{
	NNormal = 0,
	LockOn = 1,
	UseCollected = 2,
	RealForward = 3,
	SpiritAttack = 4,
	SpiritFollow = 5
};

struct TargetingArea
{
	int dropItem;
	float crosshairRadius;
	float  crosshairRadius2;
	int maxCount;
	float maxHeight;
	float maxRadius;
	AreaEffect effect;
	float minHeight;
	float minRadius;
	float offsetAngle;
	float offsetDistance;
	int pierceDepth;
	float rangeAngle;
	float rectionBasicRate;
	float rectionMiniRate;
	float rotateAngle;
	TargetingAreaType type;
};

class Targeting
{
public:
	Targeting();

	std::vector<TargetingArea> areaList;
	Cost cost;
	int endTime;
	int id;
	int interval;
	TargetingMethod method;
	TargetingType type;
	int startTime;
	int time;
	int until;
	std::vector<ProjectileSkill> projectileSkillList;
};

struct ProjectileData
{
	int areaBoxSizeX;
	int areaBoxSizeY;
	int areaBoxSizeZ;
	int lifeTime;
	std::vector<Targeting> targetingList;
};



#endif
