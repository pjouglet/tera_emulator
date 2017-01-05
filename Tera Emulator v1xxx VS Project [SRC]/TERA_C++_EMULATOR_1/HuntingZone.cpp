#include "HuntingZone.h"
#include "Creature.h"
#include "Client.hpp"
#include "PlayerService.h"
#include "GeoService.h"

HuntingZone::HuntingZone()
{
}

HuntingZone::~HuntingZone()
{
	for (size_t i = 0; i < _creatures.size(); i++)
	{
		if (_creatures[i])
		{
			delete _creatures[i];
			_creatures[i] = 0;
		}
	}
}

const bool HuntingZone::Initialize()
{
	return true;
}

const bool HuntingZone::LockZone()
{
	return _lockZone.try_lock();
}

void HuntingZone::UnlockZone()
{
	_lockZone.unlock();
}

void HuntingZone::Action()
{
}

void HuntingZone::Spawn(Creature * creature)
{
	creature->Spawn(_area, _id, GeoService::GetRandom(this));

	_creatures.push_back(creature);
}
