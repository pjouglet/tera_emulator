#pragma once

#include "Crypt\data_type.hpp"

#include <vector>
#include <mutex>

class Creature; class Client; class Area;
class HuntingZone
{
public:
	HuntingZone();
	~HuntingZone();

	const bool Initialize();
	const bool LockZone();
	void UnlockZone();
	int _id;
	int _top;
	int _bottom;
	int _right;
	int _left;
	int _monsterType;
	byte _isDangerZone;
	Area * _area;

	void Action();

	void Spawn(Creature * creature);
	void Spawn(int creatureId);

	std::vector<Creature*> _creatures;

	std::mutex _lockZone;
};

