#ifndef WORLDSYSTEM_H
#define WORLDSYSTEM_H

#include <mutex>
#include <concurrent_queue.h>
#include <thread>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#define AREA_UPDATE_TIMEOUT 100

class Player; class Account; class Area; class WorldPosition; class Client; class WorldObject; class Creature; class Projectile; class EffectZone; class HuntingZone; class CreatureBase;
class WorldSystem
{
	friend class Server;
	friend int main();
public:
	struct WorldConfig
	{
		int startContinentId;
		std::vector<int> toStartAreas;
	};

	
public:

	static const bool InitializeWorldSystem(const char* areasFilePath, const char * creaturesFilePath, const char* objectsFilePath);

	static const bool EnterWorld(Client* player);
	static void ExitWorld(Client * player);

	static void StartSystem();
	static void ShutdownSystem();
	static void ReleaseData();

	static void ProcessMovement(Client* client, float prevX, float prevY, float prevZ, short prevH);
	static const int GetNearClients(WorldPosition* _point, Area* _area, int range, std::vector<Client*>& _outClients);
	static const int GetNearWorldObjects(WorldPosition* _point, Area* _area, int range, std::vector<WorldObject*>& _outObjects);
	static const int GetNearCreatures(WorldPosition* _point, Area* _area, int range, std::vector<Creature*>& _outCreatures);

	static void OnMovePlayer(Client * client, float x, float y, float z, float x2, float y2, float z2, int heading, int type, short speed, int time);
	static void NewPlayerPosition(Player * player);
	static Area* GetArea(int continentId);
	static Area* GetArea(int worldMapWorldId, int worldMapGuardId);
	static void Main(Area* instance);


	static void DropItem(Client * c, int itemId);
	static void DropItem(CreatureBase * c, int itemId);
	static void LootItem(Client* caller, int itemId);
private:
	static const bool LoadAreas(const char* areasFilePath);
	static const bool LoadCreatures(const char* creturesFilePath);
	static const bool LoadObjects(const char* objectsFilePath);
	static Creature* ResolveCreature(int id);
	static WorldObject * ResolveWorldObject(int id);
	static EffectZone* ResolveEffectZone(int id, Area* area);

	static std::vector<Area *> _areas;
	static std::vector<Creature*> _creatures;
	static std::vector<WorldObject*> _objects;
	static std::mutex _mainLock;
	static WorldConfig _worldConfig;
};

#endif