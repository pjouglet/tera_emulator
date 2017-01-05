#include "WorldObject.h"
#include "WorldSystem.h"
#include "Client.hpp"
#include "Area.h"
#include "Stream.h"
#include "Player.hpp"

WorldObject::WorldObject() : Entity()
{
	_spawnData = new Stream();
	_despawnData = new Stream();
	_area = 0;
	_spawned = false;
	memset((void*)&_position, 0, sizeof WorldPosition); //zero the position
}
WorldObject::~WorldObject()
{
	Despawn();

	_spawnData->Clear();
	if (_spawnData)
	{
		delete _spawnData;
		_spawnData = 0;
	}

	_despawnData->Clear();
	if (_despawnData)
	{
		delete _despawnData;
		_despawnData = 0;
	}
}

WorldObject * WorldObject::Clone()
{
	WorldObject * newO = new WorldObject();
	memcpy_s((void*)newO, sizeof WorldObject, (const void*)this, sizeof WorldObject);
	return newO;
}

void WorldObject::Despawn()
{

	if (!_spawned || !_area)
		return;

	std::vector<Client*> clients;
	int count = WorldSystem::GetNearClients(&_position, _area, 1000, clients);


	for (int i = 0; i < count; i++)
	{
		if (clients[i])
		{
			clients[i]->Send(_despawnData->_raw, _despawnData->_size);
		}
	}

	_spawnData->Clear();
	_despawnData->Clear();
	_area = 0;
	_spawned = false;
}
void WorldObject::Spawn(Area * area, WorldPosition* position)
{
	if (_spawned)
		return;
	_position = *position;
	_area = area;
	std::vector<Client*> clients;

	//todo build spawn and despawn data [for type and stuff]



	int count = WorldSystem::GetNearClients(&_position, _area, 1000, clients);

	for (int i = 0; i < count; i++)
	{
		if (clients[i])
		{
			clients[i]->Send(_spawnData->_raw, _spawnData->_size);
		}
	}

	_spawned = true;
}

void WorldObject::Show(Client * client)
{
	client->Send(_spawnData->_raw, _spawnData->_size);
}

void WorldObject::Hide(Client * client)
{
	client->Send(_despawnData->_raw, _despawnData->_size);
}

void WorldObject::Action()
{
}

const bool WorldObject::Lock()
{
	return _lockMutex.try_lock();
}

void WorldObject::Unlock()
{
	_lockMutex.unlock();
}
