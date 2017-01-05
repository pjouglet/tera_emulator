#ifndef AREA_EFFECT_H
#define AREA_EFFECT_H

#include <vector>
#include <string>

class IAbnormality;
class AreaEffect
{
public:
	AreaEffect();
	~AreaEffect();

public:
	std::vector<IAbnormality*> abnormalityOnCommon;
	std::vector<IAbnormality*> abnormalityOnPvP;
	float abnormalityRate;
	float atk;
	int hpDIff;
	int id;
	int mpDiff;
	int X, Y, Z;
	int startTime;
};

#endif