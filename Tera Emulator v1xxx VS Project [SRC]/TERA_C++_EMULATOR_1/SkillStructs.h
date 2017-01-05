#ifndef SKILL_STRUCTS_H
#define SKILL_STRUCTS_H


#include "Crypt\data_type.hpp"

#include <memory>
#include <vector>

#include "SkillEnums.h"

struct Cost
{
	Cost();
	int HP;
	int MP;

	Cost* Clone();
};

struct Precondition
{
	Precondition();
	int coolTime;
	Cost cost;
	int exclusiveAbnormality;
	int modeChangeMethod;
	int modeNo;

	Precondition* Clone();
};

struct Animation
{
	Animation();
	int dir;
	std::vector<float> distance;
	int duraction;
	bool rootMotion;
	bool rootRotate;
	int rotateYaw;

	Animation * Clone();
};

struct AnimSeq
{
	AnimSeq();
	Animation animation;
	int blendInTime;
	int duration;
	bool looping;
	float loopingRate;
	int motionId;
	Animation movingAnimation;
	float rate;
	float rootMotionXYRate;
	float rootMotionZRate;
	Animation waitAnimation;

	AnimSeq* Clone();
};

struct ActionStage
{
	ActionStage();
	std::vector<Animation> animationList;

	bool movable;
	int sriptId;

	ActionStage* Clone();
};

struct SkillAction
{
	SkillAction();
	int frontCancelEndTime;
	int moveCancelStartTime;
	int pendingStartTime;
	int rearCancelStartTime;
	std::vector<ActionStage> stageList;
	SkillAction* Clone();
};

struct ChargeStage
{
	ChargeStage();
	float costHPRate;
	float costMPRate;
	float duration;
	int shotSkillID;
};

struct CharginStageList
{
	std::vector<ChargeStage> chargeStageList;
	int costTotalHP;
	int costTotalMP;

	float intervalCostHPRate;
	float intervalCostMPRate;
	bool movable;
};

#endif
