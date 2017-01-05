#ifndef BROADCAST_SERVICE_H
#define BROADCAST_SERVICE_H

#include <thread>
#include <vector>
#include <mutex>
#include <concurrent_queue.h>

#include "Stream.h"
#include "ToSendPacket.h"

#define BROADCAST_SERVICE_SHUTDOWN_TIMEOUT_TICKS 200

class Drop;
class BroadcastSystem
{
public:
	BroadcastSystem();
	~BroadcastSystem();
	static const bool InitBroadcastService(unsigned short threadCount);
	static void Release();
	static void Broadcast(Client* caller, Stream* s, BC_TYPE type, void** args);
	static const bool BroadcastSpawnDrop(Client* client, Drop * drop);
	static const bool BroadcastDespawnDrop(Client* client, long long dropEntityId);
	static const bool BroadcastSpawnPlayer(Client* caller, Client* toSpawn);
	static const bool BroadcastDespawnPlayer(Client* caller, int entityid, int subId);
private:
	static void Main(BroadcastSystem * instance);
	static void SpawnDespawnMain(BroadcastSystem * instance);

	

	bool 
		_mainRun,
		_sdRun,
		_mainRunning,
		_sdRunning;


	static BroadcastSystem * _instance;
	std::thread _mainThread;
	std::thread _spawnDespawnThread;
	concurrency::concurrent_queue<ToSendPacket*> _toSendList;
	concurrency::concurrent_queue<ToSendPacket*> _toSendSpawnDespawnList;
	std::mutex _locker;
	std::mutex _locker2;

	std::condition_variable _wait_Lock2;
	std::condition_variable _wait_Lock;
};


#endif


