#ifndef IABNORMALITY_H
#define IABNORMALITY_H

#include <vector>
#include "AbnormalityEffect.h"

#ifndef byte
#define byte unsigned char
#endif

class IAbnormality
{
public:
	IAbnormality();
	~IAbnormality();

	std::vector<AbnormalityEffect*> _effects;

	int _id,
		_kind,
		_level,
		_priority,
		_property,
		_time,
		_bySkillCategory;

	std::string
		_toolTip,
		_name;

	bool
		_notCareDeth,
		_infinity,
		_isBuff,
		_isShow,
		_isHideOnRefresh;
};

#endif