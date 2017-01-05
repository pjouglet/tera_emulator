#ifndef WORLDPOSITION_H
#define WORLDPOSITION_H

#include <math.h>
#include <memory>

struct Climb;
class Vector3D;
class WorldPosition
{
public:
	int
		_continentId,
		_worldMapSectionId,
		_worldMapGuardId,
		_worldMapWorldId;
		
	float _X,_Y,_Z;
	short _heading;
public:
	WorldPosition();
	WorldPosition(float x, float y, float z, short heading, int continentId,int worldMapSectionId,int worldMapGuardId,int worldMapWorldId);

	double DistanceTo(float x, float y);
	double DistanceTo(float x, float y, float z);
	double DistanceTo(WorldPosition *);
	double FastDistanceTo(WorldPosition*);
	double DistanceTo(Climb*);
	WorldPosition* Clone();
	short GetHeadingToTarget(WorldPosition * p);
	Vector3D& ToVector3D();
	int CopyTo(WorldPosition *);
	bool IsNull();


	void operator=(WorldPosition* t);
};
#endif
