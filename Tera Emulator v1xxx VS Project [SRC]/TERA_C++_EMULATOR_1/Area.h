#ifndef AREA_H
#define AREA_H

#include <thread>
#include <concurrent_queue.h>
#include <mutex>
#include <string>
#include <vector>
#include "Entity.h"

#define CLIENT_LOCK_TIMEOUT 100
#define MAX_PLAYERS_PER_AREA 1000
class WorldSystem; class Client; class Player; class Account; class Creature; class WorldObject; class Projectile; class EffectZone; class HuntingZone; class WorldPosition; class Vector3D; class Drop;

struct Fence
{
	float x, y, z;
};
class AreaSection
{
public:
	const bool operator ==(AreaSection& a);
	const bool operator !=(AreaSection& a);

	AreaSection();
	~AreaSection();
	std::string name;

	int
		continentId,
		worldMapSectionId,
		huntingZoneId,
		priority,
		nameId,
		campId,
		floor;

	float
		substractMinZ,
		addMaxZ,
		subtractMinZ;

	bool
		restExpBonus,
		ride,
		vender,
		pk,
		ignoreObstacleShortTel;
	std::vector<Fence*> _fences;

};

class Area : public Entity
{
	friend class GeoService;
	friend class WorldSystem;
	friend class XMLDocumentParser;
public:
	Area();
	~Area();

	const bool Initialize();
	void Lock();
	void Unlock();

	WorldPosition * GetStartPosition();

	const bool ChangeArea(Client * client, Area * area);
	void CloseArea();
	const bool EnterArea(Client * client);
	const bool EnterArea(Client * client, int sectionId);
	void ClearDrop();
	void RemoveDrop(int dropid);
	void ExitArea(Client * client);

	void AddDrop(Drop * drop);
	void RemoveDrop(Drop* drop);

	std::string _name;
	bool
		_mainRun,
		_running,
		_ride,
		_edit;

	int
		_continentId,
		_worldMapWorldId,
		_worldMapGuardId,
		_startWorldMapSectionId,
		_chanel;



private:
	void InitPlayerWorld(Client* client);
	void ChangeSection(Client * client, int sectionId);

	int
		_playersCount;

	Vector3D * _startPosition;
	short _startHeading;

	concurrency::concurrent_queue<Client*> _toAdd;
	concurrency::concurrent_queue<Drop*> _toAddDrop;
	std::thread _areaThread;

	std::vector<Client*> _clients;
	std::vector<Creature*> _npcs;
	std::vector<WorldObject*> _worldObjects;
	//std::vector<Projectile*> _projectiles;
	std::vector<EffectZone*> _effectsZones;
	std::vector<HuntingZone*>_huntingZones;
	std::vector<AreaSection*> _sections;
	std::vector<Drop*> _drop;

	std::vector<Fence*> _fences;
	std::mutex _lockMutex;
	std::mutex _lootLockMutex;
	std::mutex _sectionMutex;
};


#endif