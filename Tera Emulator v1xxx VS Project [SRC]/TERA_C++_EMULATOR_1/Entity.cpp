#include "Entity.h"
#include "EntityService.h"

Entity::Entity()  {
	EntityService::Add(this);
}

Entity::~Entity()
{
	EntityService::Remove(this);
}

