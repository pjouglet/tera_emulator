#pragma once

class WorldPosition; class HuntingZone;
class GeoService
{
public:
	
	static WorldPosition* GetRandom(HuntingZone * zone);
};

