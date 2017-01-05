#include "Creature.h"
#include "WorldPosition.h"
#include "Client.hpp"
#include "Stream.h"
#include "Area.h"
#include "WorldSystem.h"
#include "CreatureStats.h"

Creature::Creature() : Entity(), CreatureBase()
{
	_spawnData = new Stream();
	_despawnData = new Stream();
	_area = 0;
	_spawned = false;
	_position = new WorldPosition();
}

Creature::~Creature()
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

	if (_position)
	{
		delete _position;
		_position = 0;
	}
}

void Creature::Despawn()
{
	if (!_spawned || !_area)
		return;

	std::vector<Client*> clients;
	int count = WorldSystem::GetNearClients(_position, _area, 1000, clients);


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

void Creature::Spawn(Area * area, int huntingZoneId, WorldPosition * position)
{
	if (_spawned)
		return;
	position->CopyTo(position);
	_area = area;
	
	std::vector<Client*> clients;

	//todo build spawn and despawn data [for type and stuff]



	int count = WorldSystem::GetNearClients(_position, _area, 1000, clients);

	for (int i = 0; i < count; i++)
	{
		if (clients[i])
		{
			clients[i]->Send(_spawnData->_raw, _spawnData->_size);
		}
	}

	_spawned = true;
}

void Creature::Show(Client *client)
{
	client->Send(_spawnData->_raw, _spawnData->_size);
}

void Creature::Hide(Client *client)
{
	client->Send(_despawnData->_raw, _despawnData->_size);
}

Creature * Creature::Clone()
{
	Creature * newC = new Creature();
	memcpy_s((void*)newC, sizeof Creature, (const void*)this, sizeof Creature);
	return newC;
}
