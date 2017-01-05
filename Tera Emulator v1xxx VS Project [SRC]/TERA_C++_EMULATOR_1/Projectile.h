#pragma once

#include <vector>
#include <mutex>


class Projectile
{
public:
	Projectile();
	~Projectile();

	void Action();

	const bool Lock();
	void Unlock();

private:
	std::mutex _lockMutex;
};

