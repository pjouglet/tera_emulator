#include "Projectile.h"



Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::Action()
{
}

const bool Projectile::Lock()
{
	return _lockMutex.try_lock();
}
//projectile....
void Projectile::Unlock()
{
	_lockMutex.unlock();
}
