#ifndef CREATURE_BASE
#define CREATURE_BASE
#include "CreatureStats.h"
#include "Entity.h"

class Skill;
class CreatureBase : public  Entity
{
	friend class StatsService;
public:
	CreatureBase();
	virtual ~CreatureBase();


	CreatureStats  _stats;
	std::vector<Skill*> _skillList;
};

#endif