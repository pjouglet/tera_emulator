#include "Server.hpp"
#include "OpCodes.hpp"
#include "BroadcastService.h"

#include "PlayerService.h"
#include "InventoryService.h"
#include "SkillService.h"
#include "ServerTimer.h"
#include "AbnormalitiesService.h"
#include "WorldSystem.h"
#include "PassivityService.h"
#include "ServerUtils.hpp"
#include "EquipmentSet.h"

#include "SLoginArbiter.h"
#include "SCheckVersion.h"
#include "SSetVisibleRange.h"
#include "RGetPlayerList.h"
#include "RCanCreatePlayer.h"
#include "RStrEvaluateList.h"
#include "RCheckUsername.h"
#include "RCreatePlayer.h"
#include "RHardwareInfo.h"
#include "RReqVipSystemInfo.h"
#include "RSelectPlayer.h"
#include "RMovePlayer.h"
#include "RSavePlayerAccountSettings.h"
#include "RGetPlayerGuildLogo.h"
#include "RDeletePlayer.h"
#include "RChangeUserLobbySlotId.h"
#include "RCancelDeletePlayer.h"
#include "RLoadTopoFin.h"
#include "RTradeBrokerHighestItemLevel.h"
#include "RUnionSummary.h"
#include "RServerTime.h"
#include "RUpdateContentsPlayTime.h"
#include "RSimpleTipRepeatCheck.h"
#include "RSaveUserSettings.h"
#include "RRequestInstoreProductList.h"
#include "RGuardPkPolicy.h"
#include "RDungeonCoolTImeList.h"
#include "RRequestUserItemLevelInfo.h"
#include "RDungeonClearCountList.h"
#include "RNpcGuildList.h"
#include "RRaignInfo.h"
#include "RVisitNewSection.h"
#include "REventGuide.h"
#include "RShowInven.h"
#include "RSkillLearnRequest.h"
#include "RSkillLearnList.h"
#include "RStartSkill.h"
#include "RCancelSkill.h"
#include "RNotifyLocationInAction.h"
#include "RRequestGameStatPing.h"
#include "RExit.h"
#include "RChat.h"
#include "RReturnToLobby.h"
#include "RShowItemToolTipEx.h"
#include "RDelItem.h"
#include "RMoveItemPos.h"
#include "REquipItem.h"
#include "RRequestContract.h"
#include "RInventoryAutoSort.h"
#include "RUnequipItem.h"
#include "RTryLootDropItem.h"

Server::Server()
{
	_listener = 0;
	_connectedClients = 0;
	_mysqlDriver = 0;
}

Server::~Server()
{
	if (_listener)
	{
		_listener->Stop();
		delete _listener;
		_listener = 0;
	}

	
	int times = 0; int connectedClients = _connectedClients; int clientCloseFails = 0;
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i])
		{
			_clients[i]->Close();
			while ( _clients[i] && _clients[i]->_mainRunnging)
			{
				times++;
				if (times >= SERVER_CLIENTS_DISCONNECTION_TIMEOUT)
				{
					clientCloseFails++;
					break;
				}
			}

			if (times >= SERVER_CLIENTS_DISCONNECTION_TIMEOUT)
			{
				// force close client...??
			}
		}
	}
	if (clientCloseFails > 0)
		std::cout << ">>Clients disconnected [" << connectedClients - clientCloseFails << "] || error[client disconnection timeout reached, not all clients were disconnected successfuly].\n::>Remaining running threads[" << clientCloseFails << "].\n\n";
	else
		std::cout << ">>All [" << connectedClients << "] clients were disconnected succesfuly.\n\n";


	
	
	WorldSystem::ReleaseData();			   //clean up world data
	InventoryService::Release();		   //clean up inventory data
	AbnormalitiesService::Release();	   //clean up abnormality data
	SkillService::Release();			   //clean up skill data
	PassivityService::Release();		   //clean up passivity data
	EquipmentSet::Release();			   //clean up equipmentSet data
	OpCodes::Release();					   //clean up opcodes resolutions

	WSACleanup();
	if (_mysqlDriver)
	{
		delete _mysqlDriver;			   //release mysql connection and clean up
		_mysqlDriver = 0;
	}


	PlayerService::ReleaseData();		   //clean up player data
}

const bool Server::Initialize()
{
	_started = false;

	std::cout << ">Server Starting...------------------------------------------------------------------------------\n\n\n";

	//Server Config----------------------------------------------------------
	_serverConfig = LoadConfigFromFile("Config\\server.txt");
	if (!_serverConfig.isValid)
	{
		std::cout << ">Failed to load config file. [Config//server.txt]\n\n";
		return false;
	}
	std::cout << ">Loaded config file. [Config//server.txt]\n\n";

	//Mysql driver----------------------------------------------------------
	_mysqlDriver = new MySqlDriver();
	if (!_mysqlDriver->initDriver(_serverConfig.mysqlHostAddress.c_str(), _serverConfig.mysqlUsername.c_str(), _serverConfig.mysqlPassword.c_str(), _serverConfig.database.c_str()))
	{
		std::cout << "Failed to start MySqlDriver on[" << _serverConfig.mysqlHostAddress << "] user:[" << _serverConfig.mysqlUsername << "] pass[" << _serverConfig.mysqlPassword << "] db[" << _serverConfig.database << "]\n\n";
		return false;
	}
	std::cout << ">Succesfully started MySqlDriver on[" << _serverConfig.mysqlHostAddress << "] user:[" << _serverConfig.mysqlUsername << "] pass[" << _serverConfig.mysqlPassword << "] db[" << _serverConfig.database << "]\n\n";

	std::cout << "\n>Loading Data...\n\n";
	//WorldSystem--------------------------------------------------------------
	if (!WorldSystem::InitializeWorldSystem(".//data//Area", "", ""))
	{
		std::cout << ">Failed to initialize WorldSystem!.\n\n";
		return false;
	}
	//Passivity service ------------------------------
	if (!PassivityService::LoadPassivities(".//data//Passivity"))
	{
		std::cout << ">Failed to load passivities.\n\n";
		return false;
	}
	//Inventory service----------------------------------------------------------
	if (!InventoryService::LoadItems(".//data//ItemData"))
	{
		std::cout << ">InventoryService failed to load!\n\n";
		return false;
	}
	//EquipmentSet ------------------------------
	if (!EquipmentSet::LoadEquipmentSets(".//data//EquipmentData//EquipmentSetData.xml"))
	{
		std::cout << ">Failed to load equipmentSets.\n\n";
		return false;
	}
	//Abnormalities service----------------------------------------------------------
	if (!AbnormalitiesService::LoadAbnormalities(".//data//Abnormality"))
	{
		std::cout << ">Failed to load abnormalities.\n\n";
		return false;
	}
	//Skills service----------------------------------------------------------
	if (!SkillService::LoadSkills("data//SkillData"))
	{
		std::cout << ">SkillService failed to load!\n\n";
		return false;
	}
	//Player service----------------------------------------------------------
	if (PlayerService::InitializePlayerService(_mysqlDriver) < 0)
	{
		std::cout << ">PlayerService failed to initialize!\n\n";
		return false;
	}

	std::cout << ">WorldSystem Initialized!. Loaded [" << WorldSystem::_areas.size() << "] areas\n\n";
	std::cout << ">Passivity Service Loaded [" << PassivityService::GetCount() << "] passivities.\n\n";
	std::cout << ">EquipmentSets  Loaded [" << EquipmentSet::GetCount() << "].\n\n";
	std::cout << ">Abnormalities Service Loaded [" << AbnormalitiesService::GetCount() << "] abnormalities\n\n";
	std::cout << ">Skill Service loaded[" << SkillService::GetCount() << "] skills.\n\n";
	std::cout << ">Inventory Service loaded[" << InventoryService::_items.size() << "] items.\n\n";
	std::cout << ">Player Service initialized! Loaded[" << PlayerService::GetAccountCount() << "] accounts\n\n";
	std::cout << ">Data Loaded.\n\n\n";

	OpCodes::Add(new RExit());
	OpCodes::Add(new SCheckVersion());
	OpCodes::Add(new SLoginArbiter());
	OpCodes::Add(new SSetVisibleRange());
	OpCodes::Add(new RGetPlayerList());
	OpCodes::Add(new RHardwareInfo());
	OpCodes::Add(new RReqVipSystemInfo());
	OpCodes::Add(new RCanCreatePlayer());
	OpCodes::Add(new RStrEvaluateList());
	OpCodes::Add(new RCheckUsername());
	OpCodes::Add(new RCreatePlayer());
	OpCodes::Add(new RSelectPlayer());
	OpCodes::Add(new RSavePlayerAccountSettings());
	OpCodes::Add(new RMovePlayer());
	OpCodes::Add(new RGetPlayerGuildLogo());
	OpCodes::Add(new RDeletePlayer());
	OpCodes::Add(new RChangeUserLobbySlotId());
	OpCodes::Add(new RCancelDeletePlayer());
	OpCodes::Add(new RLoadTopoFin());
	OpCodes::Add(new RTradeBrokerHighestItemLevel());
	//OpCodes::Add(new RUnionSummary());
	OpCodes::Add(new RServerTime());
	OpCodes::Add(new RUpdateContentsPlayTime()); //todo
	OpCodes::Add(new RSimpleTipRepeatCheck());
	OpCodes::Add(new RSaveUserSettings());
	OpCodes::Add(new RRequestInstoreProductList()); //todo
	OpCodes::Add(new RGuardPkPolicy());
	OpCodes::Add(new RDungeonCoolTimeList());
	OpCodes::Add(new RRequestUserItemLevelInfo());
	OpCodes::Add(new RDungeonClearCountList());
	OpCodes::Add(new RNpcGuildList());
	OpCodes::Add(new RRaignInfo());
	OpCodes::Add(new RVisitNewSection());
	OpCodes::Add(new REventGuide());
	OpCodes::Add(new RShowInven());
	OpCodes::Add(new RSkillLearnRequest());
	OpCodes::Add(new RSkillLearnList()); //todo
	OpCodes::Add(new RStartSkill());
	OpCodes::Add(new RCancelSkill());
	OpCodes::Add(new RNotifyLocationInAction());
	OpCodes::Add(new RRequestGameStatPing());
	OpCodes::Add(new RChat());
	OpCodes::Add(new RReturnToLobby());
	OpCodes::Add(new RShowItemToolTipEx());
	OpCodes::Add(new REquipItem());
	OpCodes::Add(new RDelItem());
	OpCodes::Add(new RMoveItemPos());
	OpCodes::Add(new RRequestContract());
	OpCodes::Add(new RInventoryAutoSort());
	OpCodes::Add(new RUnequipItem());
	OpCodes::Add(new RTryLootDropItem());

	std::cout << ">OpCode system initialized.Instancied [" << OpCodes::Count() << "] OpCodes Resolutions. OPCODE VERSION[4605]\n\n";

	BroadcastSystem::InitBroadcastService(1);
	std::cout << ">BroadcastSystem Initialized!.\n\n";
	
	//WSAStartup----------------------------------------------------------
	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
	{
		std::cout << ">Failed to WSAStartup! error[" << WSAGetLastError() << "].\n\n";
		return false;
	}
	//Listener--------------------------------------------------------------
	_listener = new Listener(_serverConfig.ip.c_str(), _serverConfig.port, _serverConfig.maxClients);
	if (!_listener->Initialize())
	{
		std::cout << ">Listener failed to  initialize on IP [" << _serverConfig.ip << "] PORT[" << _serverConfig.port << "]...\n\n";
		return false;
	}
	std::cout << ">Listener initialized on IP [" << _serverConfig.ip << "] PORT[" << _serverConfig.port << "].\n\n";

	std::cout << ">Server Initialized. Ready to start!\n\n\n\n\n\n";
	if (_serverConfig.autoStart)
	{
		std::cout << ">Server auto-start[ON]!\n\n";
		if (!Run())
		{
			std::cout << ">Server start attempt failed!\n\n";
			return false;
		}
	}
	else
		std::cout << ">Server auto-start[OFF]!\n\n";


	return true;
}

const bool Server::Run()
{
	if (_started)
		return false;
	std::lock_guard<std::mutex> _lock(_serverMutex);
	_listener->Start(this);
	WorldSystem::StartSystem();
	std::cout << ">--------Wrold systems started.\n\n";

	std::cout << ">Server Runnging...\n\n";
	_started = true;

	return true;
}
const bool Server::Shutdown()
{
	if (!_started)
		return false;
	std::lock_guard<std::mutex> _lock(_serverMutex);
	WorldSystem::ShutdownSystem();

	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i])
		{
			_clients[i]->Close();
		}
	}
	_listener->Stop();
	_started = false;
	return true;
}

void Server::NewConnection(Client * client)
{
	std::lock_guard<std::mutex> _lock(_serverMutex);
	_clients.push_back(client);
	if ((_connectedClients + 1) > _serverConfig.maxClients)
	{
		_listener->Stop();
		std::cout << "::Stopped listening for clients! [Max clients reached][" << _serverConfig.maxClients << "]\n\n";

		client->Close();
		return;
	}
}
void Server::RemoveConnection(Client * c)
{
	std::lock_guard<std::mutex> _lock(_serverMutex);

	for (auto i = _clients.begin(); i != _clients.end(); ++i)
	{
		if ((*i) && (*i) == c)
		{
			(*i)->_mainRunnging = false;
			delete (*i);
			(*i) = 0;
			_clients.erase(i);
			break;
		}
	}


}

Server::Config Server::LoadConfigFromFile(const char * file)
{
	Config out;
	ZeroMemory(&out, sizeof out);


	std::fstream f;
	f.open(file, std::ios::in);

	if (f.is_open())
	{
		std::string line;

		std::getline(f, line);
		out.ip = line;

		std::getline(f, line);
		out.port = atoi(line.c_str());

		std::getline(f, line);
		out.maxClients = atoi(line.c_str());

		std::getline(f, line);
		out.mysqlHostAddress = line;

		std::getline(f, line);
		out.mysqlUsername = line;

		std::getline(f, line);
		out.mysqlPassword = line;

		std::getline(f, line);
		out.database = line;

		int autoStartVal = 0;
		std::getline(f, line);
		sscanf_s(line.c_str(), "autostart = %d", &autoStartVal);
		out.autoStart = (bool)autoStartVal;

		out.isValid = true;
	}

	return out;
}
Server::Config Server::_serverConfig;