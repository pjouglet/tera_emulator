#pragma once
#include "CreatureStats.h"
class MobStats :
	public CreatureStats
{
public:
	MobStats();
	~MobStats();

	PlayerClass _class;
	PlayerGender _gender;
	PlayerRace _race;
	std::string _name;
	int _huntingZoneId;

	//level
	int _level;

};

