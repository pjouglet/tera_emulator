#include "CraftingSystem.h"
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


CraftingSystem::CraftingSystem()
{
}
CraftingSystem::~CraftingSystem()
{
}

void CraftingSystem::SendArtisanSkillList(Client * client)
{
	Stream s = Stream();

	s.WriteInt16(0);
	s.WriteInt16(S_ARTISAN_SKILL_LIST);
	s.WriteHexString("000000000001");

	s.WritePos(0);
	client->Send(s._raw, s._size);
}

void CraftingSystem::SendArtisanRecipeList(Client * client)
{
	Stream s = Stream();

	s.WriteInt16(0);
	s.WriteInt16(S_ARTISAN_RECIPE_LIST);
	s.WriteHexString("05001900000000000000000000000048440E0000001900390006000000060000000000803FFFFFFFFF01000000FFFFFFFF000000003900590007000000070000000000803FFFFFFFFF01000000FFFFFFFF000000005900790015000000150000000000803FFFFFFFFF01000000FFFFFFFF000000007900990016000000160000000000803FFFFFFFFF01000000FFFFFFFF000000009900000017000000170000000000803FFFFFFFFF01000000FFFFFFFF00000000");


	s.WritePos(0);
	client->Send(s._raw, s._size);
}
