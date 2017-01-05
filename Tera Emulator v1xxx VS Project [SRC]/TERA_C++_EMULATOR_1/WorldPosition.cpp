#include "WorldPosition.h"
#include "Climb.h"
#include "Vector3.hpp"

bool WorldPosition::IsNull()
{
	return(_X == 0.0f && _Y == 0.0f && _Z == 0.0f);
}

void WorldPosition::operator=(WorldPosition * t)
{
	this->_continentId = t->_continentId;
	this->_X = t->_X;
	this->_Y = t->_Y;
	this->_Z = t->_Z;
}

WorldPosition::WorldPosition()
{
	_X = _Y = _Z = 0.0f;
	_heading = 0;
	_continentId = 0;
}

WorldPosition::WorldPosition(float x, float y, float z, short heading, int continentId, int worldMapSectionId, int worldMapGuardId, int worldMapWorldId)
{
	_X = x;
	_Y = y;
	_Z = z;
	_heading = heading;
	_continentId = continentId;
	_worldMapGuardId = worldMapGuardId;
	_worldMapSectionId = worldMapSectionId;
	_worldMapWorldId = worldMapWorldId;
}

double WorldPosition::DistanceTo(float x, float y)
{
	double a = x - _X;
	double b = y - _Y;

	return sqrt(a* a + b *b);
}

double WorldPosition::DistanceTo(float x, float y, float z)
{
	double a = x - _X;
	double b = y - _Y;
	double c = z - _Z;

	return sqrt(a* a + b *b + c *c);
}

double WorldPosition::DistanceTo(WorldPosition * p1)
{
	if (!p1)
		return 0xffffffff;

	double a = p1->_X - _X;
	double b = p1->_Y - _Y;
	double c = p1->_Z - _Z;

	return sqrt(a* a + b *b + c *c);
}

double WorldPosition::FastDistanceTo(WorldPosition * p1)
{
	if (!p1)
		return 0xffffffff;

	double a = p1->_X - _X;
	double b = p1->_Y - _Y;
	

	return sqrt(a* a + b *b);
}

double WorldPosition::DistanceTo(Climb * climb)
{
	if (!climb)
		return 0xffffffff;

	double a = climb->X1 - _X;
	double b = climb->Y1 - _Y;
	double c = climb->Z1 - _Z;


	return sqrt(a* a + b *b + c *c);
}

WorldPosition* WorldPosition::Clone()
{
	WorldPosition * out = new WorldPosition;
	out->_X = _X;
	out->_Y = _Y;
	out->_Z = _Z;
	out->_continentId = _continentId;
	out->_heading = _heading;

	return out;
}

short WorldPosition::GetHeadingToTarget(WorldPosition * p)
{
	return 0; //TODO return Geom.GetHeading(((float) ((worldPosition.X - X)/DistanceTo(worldPosition))*45),
			  //                    ((float)((worldPosition.Y - Y) / DistanceTo(worldPosition)) * 45));
}

Vector3D & WorldPosition::ToVector3D()
{
	return Vector3D(_X, _Y, _Z);
}

int WorldPosition::CopyTo(WorldPosition * p1)
{
	return memcpy_s((void*)p1, sizeof(WorldPosition), (const void*)this, sizeof(WorldPosition));
}
