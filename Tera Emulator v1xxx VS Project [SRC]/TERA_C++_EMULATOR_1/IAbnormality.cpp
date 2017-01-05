#include "IAbnormality.h"
#include "Client.hpp"



IAbnormality::IAbnormality()
{
	memset(this, 0, sizeof IAbnormality);
}

IAbnormality::~IAbnormality()
{
	for (size_t i = 0; i < _effects.size(); i++)
	{
		if (_effects[i])
		{
			delete _effects[i];
			_effects[i] = nullptr;
		}
	}
	_effects.clear();
}
