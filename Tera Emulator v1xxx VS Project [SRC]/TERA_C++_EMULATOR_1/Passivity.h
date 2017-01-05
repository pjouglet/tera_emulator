#pragma once

#include "PlayerEnums.h"

#ifndef byte
#define byte unsigned char
#endif

class Passivity
{
public:
	Passivity();
	
	MobSize _mobSize;
	
	int
		_conditionValue,
		_conditionCategory,
		_abnormalityKind,
		_abnormalityCategory,
		_condition,
		_tickInterval,
		_method,
		_kind,
		_id,
		_prevPassivityId,
		_passivityChangeId,
		_passivityChangeTime,
		_type;

	float
		_value,
		_probability;

	byte
		_judgmentOnce,
		_balancedByTargetCount;
};

