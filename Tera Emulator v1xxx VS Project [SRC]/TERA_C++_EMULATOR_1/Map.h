#ifndef MAP_H
#define MAP_H

#include <mutex>
#include <thread>
#include <vector>
#include <concurrent_queue.h>

class Player; class Account; class Creature; class WorldObject; class WorldSystem; class Client;
class Map
{
public:
	struct Zone {
		int id;
		std::string name;
		std::vector<Creature*> _creatures;
		std::vector<WorldObject *> _objects;
	};
public:
	Map();
	~Map();

	const bool InitMap(int id, WorldSystem * worldSystem);

	void AddZone(Zone * z);
	void EnterMap(Client * client);
	void Release();
private:
	static void Main(Map* instance, WorldSystem * worldSystem);

	inline void InitPlayer(Client * client);
private:
	bool _locked;
	bool _run;
	bool _running;
	std::mutex _addClientMutex;
	std::thread _mainThread;

	int _id;
	std::string _name;
	std::vector<Zone*> _zones;
	std::vector<Client*> _clients;
	concurrency::concurrent_queue<Client*> _peddingClients;

};
#endif
