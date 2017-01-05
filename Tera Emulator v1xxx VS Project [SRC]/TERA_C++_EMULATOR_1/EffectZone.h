#pragma once

#include <mutex>
#include <vector>

class Area; class Client; class Creature; class IAbnormality; class Effect;
class EffectZone
{
	friend class WorldSystem;
	friend class Area;
public:
	EffectZone(Area * area);
	~EffectZone();

	void Action();

	const bool Intialize();

	void Active();
	void Deactive();

	const bool LockEffectZone();
	void UnlockEffectZone();
private:
	int top, bottom, left, right;
	int rotation, centerX, centerY, centerZ;

	bool _active;
	std::vector<IAbnormality*> _abnormalities;
	std::vector<Effect*> _effects;

	std::vector<Creature*> _visibleCreatures;
	std::vector<Client*> _visibleClients;

	Area * _area;
	std::mutex _lockMutex;
};

