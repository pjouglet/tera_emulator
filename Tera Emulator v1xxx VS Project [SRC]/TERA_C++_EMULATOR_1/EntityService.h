#pragma once

#include <mutex>
#include <vector>

class Entity;
class EntityService
{
	friend class Entity;

	static void Add(Entity* e);
	static void Remove(Entity * e);

public:
	static unsigned long long GenerateId();
	static void Initialize(unsigned long long start = 0);
	static Entity * GetEntity(unsigned long long id);

private:
	static std::vector<Entity*> _entities;
	static unsigned long long _lastId;
	static std::mutex _generateMutex;
	static std::mutex _getEntityMutex;
};

