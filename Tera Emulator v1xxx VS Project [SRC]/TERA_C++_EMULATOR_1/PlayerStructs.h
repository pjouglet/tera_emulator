#pragma once

#include <vector>
#include <string>

struct DefaultSkillList
{
public:
	DefaultSkillList();

	short pRace;
	short pGender;
	short pClass;
	int model;
	std::vector<int> skillSet;


};
