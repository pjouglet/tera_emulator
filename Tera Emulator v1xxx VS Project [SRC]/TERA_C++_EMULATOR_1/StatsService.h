#pragma once

#include <vector>
#include "PlayerEnums.h"

class CreatureStats; class Creature; class Player; class Client;
class StatsService
{
public:

	static CreatureStats* GetCreatureBaseStats(Creature * creature);
	static void GetPlayerStartStats(Player* p);
	static void SendPlayerStats(Client* c, bool broadcast = true);
	static void CalculatePlayerStats(Player * p);
};

