#include "EntityService.h"
#include "Entity.h"

unsigned long long EntityService::GenerateId()
{
	_generateMutex.lock();
	_lastId++;
	_generateMutex.unlock();
	return _lastId;
}

void EntityService::Initialize(unsigned long long start)
{
	_lastId = start;
}

Entity * EntityService::GetEntity(unsigned long long id)
{
	_getEntityMutex.lock();
	Entity*  out = nullptr;
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities[i] && _entities[i]->_entityId == id)
			out = _entities[i];
	}
	_getEntityMutex.unlock();
	return out;
}

void EntityService::Add(Entity * e)
{
	_getEntityMutex.lock();
	e->_entityId = GenerateId();
	_entities.push_back(e);
	_getEntityMutex.unlock();
}

void EntityService::Remove(Entity * e)
{
	_getEntityMutex.lock();
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities[i] == e)
		{
			_entities[i] = 0;
			_entities.erase(_entities.begin() + i);
			break;
		}
	}
	_getEntityMutex.unlock();
}

unsigned long long EntityService::_lastId = 0;
std::mutex   EntityService::_generateMutex;
std::mutex   EntityService::_getEntityMutex;
std::vector<Entity*> EntityService::_entities;