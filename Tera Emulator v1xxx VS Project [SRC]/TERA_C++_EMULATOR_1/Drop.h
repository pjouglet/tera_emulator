#pragma once
#include "Entity.h"
#include <vector>
class Drop :
	public Entity
{
public:
	Drop();
	Drop(int itemId, float x = 0.0f, float y = 0.0f, float z = 0.0f, int stackCount = 1, int expire = 0, int mobEntityid = 0);
	~Drop();

	void AddOwner(int entityId);

	int
		_itemId,
		_stackCount,
		_expire,
		_mobEntityid,
		_unk1, _unk2, _unk4, _unk5;

	short
		_unk3;

	float
		X, Y, Z;

	std::vector<int>  _ownersEntityIds;
};

