#include "EffectZone.h"



EffectZone::EffectZone(Area * area)
{
	_area = area;
	_active = true;
}

EffectZone::~EffectZone()
{
	_area = 0;
}

void EffectZone::Action()
{
	if (_active)
	{
		
	}
}

const bool EffectZone::Intialize()
{
	return false;
}

void EffectZone::Active()
{
	_active = true;
}
//effect zone, zone that apllyes effect on targets within zone , like aoe etc
void EffectZone::Deactive()
{
	_active = false;
}

const bool EffectZone::LockEffectZone()
{
	return _lockMutex.try_lock();
}

void EffectZone::UnlockEffectZone()
{
	_lockMutex.unlock();
}
