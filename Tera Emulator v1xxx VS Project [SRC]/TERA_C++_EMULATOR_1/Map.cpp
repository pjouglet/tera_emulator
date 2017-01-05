#include "Map.h"
#include "Account.hpp"
#include "Player.hpp"
#include "Client.hpp"

Map::Map()
{
	_locked = 0;
	_run = false;
	_running = false;
}

Map::~Map()
{
	if (!_locked && !_running)
	{
		for (size_t i = 0; i < _zones.size(); i++)
		{
			if (_zones[i])
			{
				for (size_t j= 0; j < _zones[i]->_objects.size(); j++)
				{
					WorldObject * obj = _zones[i]->_objects[j];
					if (obj)
					{
						delete obj;
						obj = 0;
					}
				}
				_zones[i]->_objects.clear();

				for (size_t j = 0; j < _zones[i]->_objects.size(); j++)
				{
					Creature * creature = _zones[i]->_creatures[j];
					if (creature)
					{
						delete creature;
						creature = 0;
					}
				}
				_zones[i]->_creatures.clear();

				delete _zones[i];
				_zones[i] = 0;
			}
		}
		_zones.clear();


	}
}

const bool Map::InitMap(int id, WorldSystem * worldSystem)
{










	//lock the Map instance for exterrior changes and start main map thread
	_locked = true;
	_run = true;
	_mainThread = std::thread(Map::Main, this, worldSystem);
	_mainThread.detach();

	return true;
}

void Map::AddZone(Zone * z)
{
	if (!_locked)
	{
		_zones.push_back(z);
	}
}

void Map::EnterMap(Client * client)
{
	_addClientMutex.lock();

	_peddingClients.push(client);

	_addClientMutex.unlock();
}

void Map::Release()
{
	if (_locked)
	{
		_run = false;
		_locked = false;
	}
}

void Map::Main(Map* instance, WorldSystem * worldSystem)
{
	instance->_running = true;
	while (instance->_run)
	{
		Client * c = 0;
		while (instance->_peddingClients.try_pop(c))
		{
			instance->InitPlayer(c);
			instance->_clients.push_back(c);
		}
		



	}
	instance->_running = false;
}

void Map::InitPlayer(Client * client)
{
	//todo add zone init logic here
}
