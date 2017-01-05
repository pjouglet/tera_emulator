#include "CreatureBase.h"

CreatureBase::CreatureBase(): Entity()
{
	memset(&_stats, 0, sizeof CreatureStats);
}
CreatureBase::~CreatureBase()
{
	
}
