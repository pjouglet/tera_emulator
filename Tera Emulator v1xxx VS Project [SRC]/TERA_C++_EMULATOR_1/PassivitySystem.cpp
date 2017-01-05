#include "PassivitySystem.h"
#include "CreatureBase.h"
#include <iostream>
using namespace PFUN;

const bool PassivitySystem::Initialize()
{
	_passivitiesResolutions.insert(std::pair<int, PassiveFunction>(1, &IncreaseDamage));

	return true;
}

PassiveFunction PassivitySystem::operator[](int pid)
{
	return _passivitiesResolutions[pid];
}
std::map<int, PassiveFunction> PassivitySystem::_passivitiesResolutions;

void PFUN::IncreaseDamage(CreatureBase * c)
{
	
}
