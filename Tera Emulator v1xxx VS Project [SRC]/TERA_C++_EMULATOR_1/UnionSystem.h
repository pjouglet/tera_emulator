#ifndef UNION_SYSTEM_H
#define UNION_SYSTEM_H
#include "Area.h"
#include "Stream.h"
#include "Account.hpp"
#include "Client.hpp"
#include "Player.hpp"
#include "mysql\MySqlDriver.h"
#include "mysql\SQLStream.h"
#include "ServerUtils.hpp"
#include "OpCodesEnum.h"

#include "PlayerEnums.h"
#include "Player.hpp"
#include "Account.hpp"
#include "WorldPosition.h"
#include "InventoryService.h"
#include "WorldSystem.h"
#include "SkillService.h"
#include "ServerTimer.h"
#include "LevelingService.h"

#include <sstream>
#include <Windows.h>
class Account;
class Player;
class Client;
class MySqlDriver;

class UnionSystem
{
public:
	static void SendElectionState(Client* client);

};
#endif
