#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <string>

#include "Entity.h"
#include "CreatureBase.h"

enum CreatureType : int {
	MONSTER = 0,
	NPC = 1,

};
enum MonsterType : int
{

};
enum NpcType : int
{
	BANKER = 1,
	TRADEBROKER = 2,
	SHOP = 3,
	SPECIALSHOP = 4,

};

class WorldSystem; class Client;  class Area; class Stream; class AIElement; class Bonus; class CreatureStats; class CombatManager; class WorldPosition;
class Creature : public Entity, public CreatureBase
{
	friend  class WorldSystem;
public:
	Creature();
	virtual ~Creature();

	void Despawn();
	void Spawn(Area * area, int huntingZoneId, WorldPosition* position);

	void Show(Client *client);
	void Hide(Client *client);

	Creature * Clone();

	WorldPosition*  _position;
	Area * _area;

	Stream * _spawnData;
	Stream * _despawnData;


	bool _spawned;
	CreatureType _type;
	int _subType;
	int _subId;
};



#endif