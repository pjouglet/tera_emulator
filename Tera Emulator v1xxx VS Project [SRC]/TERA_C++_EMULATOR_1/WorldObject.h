#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include  <vector>
#include <mutex>
#include "WorldPosition.h"
#include "Entity.h"

enum WorldObjectType :int {
	NONE = -1
};

class WorldSystem; class Client;  class Area; class Stream;
class WorldObject : public Entity
{
	friend  class WorldSystem;

	WorldObject();
	virtual ~WorldObject();

	WorldObject* Clone();

	void Despawn();
	void Spawn(Area * area, WorldPosition* position);

	void Show(Client *client);
	void Hide(Client *client);

	void Action();

	const bool Lock();
	void Unlock();

private:
	bool _spawned;
	int _id;
	std::mutex _lockMutex;
	Area * _area;

	Stream * _spawnData;
	Stream * _despawnData;

	WorldObjectType _type;
	WorldPosition 	 _position;
};

#endif