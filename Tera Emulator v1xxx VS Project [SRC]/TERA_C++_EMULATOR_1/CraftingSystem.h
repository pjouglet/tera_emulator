#ifndef CRAFTING_SYSTEM_H
#define CRAFTING_SYSTEM_H

class Account;
class Player;
class Client;
class MySqlDriver;

class CraftingSystem
{
public:
	CraftingSystem();
	~CraftingSystem();

	static void SendArtisanSkillList(Client * client);
	static void SendArtisanRecipeList(Client* client);

};

#endif