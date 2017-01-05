#include "WorldSystem.h"
#include <vector>
#include "Area.h"
#include "Account.hpp"
#include "Client.hpp"
#include "Player.hpp"
#include "WorldObject.h"
#include "Creature.h"
#include "PlayerEnums.h"
#include "HuntingZone.h"
#include "EffectZone.h"
#include "Projectile.h"
#include "StatsService.h"
#include "ServerUtils.hpp"
#include "FileStream.h"
#include "EntityService.h"
#include "Vector3.hpp"
#include "Drop.h"
#include "Stream.h"
#include "OpCodesEnum.h"
#include "BroadcastService.h"
#include "XMLDocumentParser.h"
#include "MessagingSystem.h"
#include "Inventory.h"



const bool WorldSystem::LoadCreatures(const char * creturesFilePath)
{

	return true;
}

const bool WorldSystem::LoadObjects(const char * objectsFilePath)
{
	return false; //todo
}

Creature * WorldSystem::ResolveCreature(int id)
{
	for (size_t i = 0; i < _creatures.size(); i++)
	{
		break;
	}
	return nullptr;
}

WorldObject * WorldSystem::ResolveWorldObject(int id)
{
	for (size_t i = 0; i < _objects.size(); i++)
	{
		if (_objects[i] && _objects[i]->_id == id)
			return _objects[i]->Clone();
	}

	return nullptr;
}

EffectZone * WorldSystem::ResolveEffectZone(int id, Area* area)
{
	return nullptr;
}

const bool WorldSystem::InitializeWorldSystem(const char * areasFilePath, const char * creaturesFilePath, const char * objectsFilePath)
{
	FileStream fs = FileStream(".//Config//world.config");
	if (!fs.IsOpen())
		return false;
	ZeroMemory(&_worldConfig, sizeof _worldConfig);
	_worldConfig.startContinentId = fs.ReadInt32();
	int toStartCound = fs.ReadInt32();
	for (size_t i = 0; i < toStartCound; i++)
	{
		_worldConfig.toStartAreas.push_back(fs.ReadInt32());
	}

	if (!LoadAreas(areasFilePath))
		return false;
	/*if (!LoadCreatures(creaturesFilePath))
		return false;
	if (!LoadObjects(objectsFilePath))
		return false;*/

	return true;
}

const bool WorldSystem::EnterWorld(Client * client)
{
	Player *p = nullptr;
	if (!(p = client->GetSelectedPlayer()))
		return false;

	Area *  a = nullptr;
	if ((a = GetArea(p->_position->_continentId)))
	{
		a->EnterArea(client);
		return true;
	}

	return false;
}

void WorldSystem::ExitWorld(Client * client)
{
	Player *p = nullptr;
	if ((p = client->GetSelectedPlayer()) && p->_currentArea)
		p->_currentArea->ExitArea(client);
}

void WorldSystem::StartSystem()
{
	int c = 0;
	for (size_t x = 0; x < _worldConfig.toStartAreas.size(); x++)
	{
		for (size_t i = 0; i < _areas.size(); i++)
		{
			if (_areas[i]->_continentId == _worldConfig.toStartAreas[x])
			{
				_areas[i]->_mainRun = true;
				_areas[i]->_areaThread = std::thread(Main, _areas[i]);
				_areas[i]->_areaThread.detach();
				c++;
			}
		}
	}

	std::cout << ">>Started [" << c << "] areas. \n";
}

void WorldSystem::ShutdownSystem()
{
	int t = 0; int inactive = 0; int active = 0; int fails = 0;
	for (size_t i = 0; i < _areas.size(); i++)
	{
		if (_areas[i] && _areas[i]->_running)
		{
			std::string name = _areas[i]->_name; int id = _areas[i]->_continentId;
			_areas[i]->CloseArea();
			while (_areas[i] && _areas[i]->_running)
			{
				t++;
				if (t >= 500)
					break;
				Sleep(10);
			}
			if (t >= 500)
			{
				std::cout << "::Failed to close area[" << name << "] ContinentId[" << id << "] tiemout\n";
				fails++;
			}
			else
			{
				std::cout << "::Closed ACTIVE area[" << name << "] ContinentId[" << id << "] timeoutCount[" << t << "]\n";
				active++;
			}
		}
		else if (_areas[i] && !_areas[i]->_running)
			inactive++;
		t = 0;
	}

	std::cout << "\n::Were ACTIVE[" << active << "] INACTIVE[" << inactive << "] areas. CLOSE_FAILS[" << fails << "]\n\n";
}

void WorldSystem::ReleaseData()
{
	ShutdownSystem();
	int t = 0;
	for (size_t i = 0; i < _areas.size(); i++)
	{
		if (_areas[i] && !_areas[i]->_running)
		{
			t = 0;
			delete _areas[i];
			_areas[i] = 0;
		}
		else if (_areas[i] && _areas[i]->_running)
		{
			t++;
			_areas[i]->CloseArea();
			if (t < 100)
				i--;
			else
				t = 0;
			continue;
		}
	}
	_areas.clear();
}

void WorldSystem::ProcessMovement(Client * client, float prevX, float prevY, float prevZ, short prevH)
{
	Player * p = client->GetSelectedPlayer();
	if (!p || !p->_currentArea)
		return;

	//float deltaX = abs(p->_position->_X - prevX);
	//float deltaY = abs(p->_position->_Y - prevX);
	//float deltaZ = abs(p->_position->_Z - prevX);
	//short deltaH = abs(p->_position->_heading - prevH);

	double distanceBetwen = 0; bool hasClient = false;
	p->_currentArea->Lock();
	for (size_t i = 0; i < p->_currentArea->_clients.size(); i++)
	{
		Client* you = p->_currentArea->_clients[i];
		Player * youP = you->GetSelectedPlayer();

		if (!you || !youP || client == you)
			continue;

		if (youP->_position->_worldMapSectionId == p->_position->_worldMapSectionId)//same section
		{
			distanceBetwen = p->_position->DistanceTo(youP->_position);  hasClient = false;
			for (size_t j = 0; j < client->_visibleClients.size(); j++)
			{
				if (client->_visibleClients[j] == you)
				{
					if (distanceBetwen > 10000)
					{
						client->RemoveVisibleClient(you); you->RemoveVisibleClient(client);
					}


					hasClient = true;
					break;
				}
			}
			if (!hasClient)
			{
				if (distanceBetwen < 10000.0f)
				{
					if (!client->IsVisibleClient(you))
						client->AddVisibleClient(you);

					if (!you->IsVisibleClient(client))
						you->AddVisibleClient(client);
				}
			}
		}
	}
	p->_currentArea->Unlock();
}

const int WorldSystem::GetNearClients(WorldPosition * _point, Area * _area, int range, std::vector<Client*>& _outClients)
{
	if (!_area)
		return 0;
	int c = 0;
	for (size_t i = 0; i < _area->_clients.size(); i++)
	{
		if (_area->_clients[i]->GetSelectedPlayer()->_position->DistanceTo(_point) <= (double)range)
		{
			_outClients.push_back(_area->_clients[i]);
			c++;
		}
	}
	return c;
}

const int WorldSystem::GetNearWorldObjects(WorldPosition * _point, Area * _area, int range, std::vector<WorldObject*>& _outObjects)
{
	return 0;
}

const int WorldSystem::GetNearCreatures(WorldPosition * _point, Area * _area, int range, std::vector<Creature*>& _outCreatures)
{
	return 0;
}

void WorldSystem::OnMovePlayer(Client * client, float x, float y, float z, float x2, float y2, float z2, int heading, int type, short speed, int time)
{
	_mainLock.lock();

	_mainLock.unlock();
}

void WorldSystem::NewPlayerPosition(Player * player)
{
	if (player->_position)
	{
		delete player->_position;
		player->_position = 0;
	}

	Area * a = nullptr;
	if ((a = GetArea(_worldConfig.startContinentId)))
		player->_position = a->GetStartPosition();
	else
		player->_position = nullptr;
}

Area * WorldSystem::GetArea(int continentId)
{
	for (size_t i = 0; i < _areas.size(); i++)
	{
		if (_areas[i] && _areas[i]->_continentId == continentId)
		{
			return _areas[i];
		}
	}

	return nullptr;
}

Area * WorldSystem::GetArea(int worldMapWorldId, int worldMapGuardId)
{
	for (size_t i = 0; i < _areas.size(); i++)
	{
		if (_areas[i] && _areas[i]->_worldMapGuardId == worldMapGuardId &&_areas[i]->_worldMapWorldId == worldMapWorldId)
		{
			return _areas[i];
		}
	}

	return nullptr;
}

void WorldSystem::Main(Area * instance)
{
	instance->_running = true;
	int t = 0; int j = 0;
	Stream* data = new Stream();
	while (instance->_mainRun)
	{
		instance->Lock();
		if (!instance->_mainRun)
			break;
		instance->_lootLockMutex.lock();
		Drop * dp = nullptr;
		while (instance->_toAddDrop.try_pop(dp))
		{
			instance->_drop.push_back(dp);
			for (size_t i = 0; i < instance->_clients.size(); i++)
			{
				Player * p = instance->_clients[i]->GetSelectedPlayer();
				if (p && p->_position->DistanceTo(dp->X, dp->Y, dp->Z) < p->_visibleRange)
					BroadcastSystem::BroadcastSpawnDrop(instance->_clients[i], dp);
			}
		}
		dp = nullptr;
		instance->_lootLockMutex.unlock();


		instance->Unlock();
		Sleep(1);
	}

	delete data;
	data = nullptr;
	instance->_running = false;
}

void WorldSystem::DropItem(Client * c, int itemId)
{
	Player * p = c->GetSelectedPlayer();
	if (!p)
		return;
	Area * ar = p->_currentArea;
	if (!ar)
		return;

	Drop* newDrop = new Drop(itemId, p->_position->_X + 5, p->_position->_Y + 5, p->_position->_Z);
	ar->AddDrop(newDrop);
}

void WorldSystem::LootItem(Client * caller, int dropId)
{
	if (!caller)
		return;

	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;
	Inventory * inv = p->_inventory;
	if (inv->IsFull())
	{
		MessagingSystem::SendSystemMessage(caller, "@350"); //test
		return;
	}
	Drop * dp = (Drop*)EntityService::GetEntity(dropId);
	if (dp)
	{
		if (dp->_ownersEntityIds.size() == 0)
		{
			(*inv) << dp->_itemId;
			inv->SendInventory(caller,0);
			p->_currentArea->RemoveDrop(dropId);
			return;
		}
		for (size_t i = 0; i < dp->_ownersEntityIds.size(); i++)
		{
			if (dp->_ownersEntityIds[i] == p->_entityId)
			{
				(*inv) << dp->_itemId;
				inv->SendInventory(caller, 0);
				break;
			}
		}

		p->_currentArea->RemoveDrop(dropId);
	}
}

const bool WorldSystem::LoadAreas(const char* areasFilePath) //here
{
	std::stringstream ss;
	ss << areasFilePath << "//info.txt";
	std::string line = "";
	int areaCount = 0;
	int sectionCount = 0;
	std::ifstream infoFile = std::ifstream(ss.str());
	if (!infoFile.is_open())
		return false;

	std::getline(infoFile, line);
	sscanf(line.c_str(), "count=%d", &areaCount);
	infoFile.close();




	if (!XMLDocumentParser::ParseRegionStrSheetXMLDocument(".//data//Area//StrSheet_Region.xml"))
	{
		std::cout << "::Could not read [.//data//Area//StrSheet_Region.xml]\n";
		return false;
	}

	for (size_t i = 0; i < areaCount; i++)
	{
		ss.clear(); ss.str(""); ss << areasFilePath << "//Area-" << i << ".xml";
		XMLDocumentParser::ParseAreaXMLDocument(ss.str().c_str(), _areas);
		std::cout << ">Loaded area[" << ss.str() << "]\r" << std::flush;
	}
	std::cout << "\n::Loaded [" << _areas.size() << "] areas\n\n";
	/*for(size_t i = 0; i < _areas.size(); i++)
	{
		std::cout << _areas[i]->_name << std::endl;
	}*/



	ss.clear(); ss.str(""); ss << areasFilePath << "//areaStartPositions.bin";
	std::cout << ">Loading aresStartPositions.bin file.\n";
	FileStream startPositionsFile = FileStream(ss.str().c_str());
	if (!startPositionsFile.IsOpen())
	{
		for (size_t i = 0; i < _areas.size(); i++)
		{
			delete _areas[i];
			_areas[i];
		}
		_areas.clear();

		std::cout << "::Failed to load aresStartPositions.bin file.\n";
		return false;
	}
	int id = 0; int bindCount = 0;
	int count = startPositionsFile.ReadInt32();
	for (size_t i = 0; i < count; i++)
	{
		id = startPositionsFile.ReadInt32();
		for (size_t j = 0; j < _areas.size(); j++)
		{
			if (_areas[j] && _areas[j]->_continentId == id)
			{
				float x = startPositionsFile.ReadFloat(), y = startPositionsFile.ReadFloat(), z = startPositionsFile.ReadFloat();
				_areas[j]->_startPosition = new Vector3D(x, y, z);
				_areas[j]->_startHeading = startPositionsFile.ReadInt16();

				bindCount++;
				break;
			}
		}
	}

	std::cout << "::Loaded [" << count << "] startPositions, binded[" << bindCount << "] startPositions to areas.\n\n";

	return true;
}

std::vector<Area*> WorldSystem::_areas;
std::vector<Creature*>  WorldSystem::_creatures;
std::vector<WorldObject*>  WorldSystem::_objects;
std::mutex WorldSystem::_mainLock;
WorldSystem::WorldConfig WorldSystem::_worldConfig;