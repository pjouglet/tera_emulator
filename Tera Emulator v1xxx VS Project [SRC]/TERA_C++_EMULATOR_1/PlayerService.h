#ifndef PLAYER_SERVICE_H
#define PLAYER_SERVICE_H

#include <thread>
#include <vector>
#include <mutex>

#include "PlayerEnums.h"
#include "Crypt\data_type.hpp"


class Account;
class Player;
class Client;
class MySqlDriver;
class PlayerService
{
public:
	static const int InitializePlayerService(MySqlDriver * driver);

	static const bool CheckPlayerNameForm(std::string name);
	static const bool CheckPlayerName(std::string name);
	static Account* PerformAccountLogin(const char* unsername, const char* password);
	static Account * GetAccount(int accountIndex);
	static unsigned int GetAccountCount();

	static void UpdateAccountData(Account * account);
	static void SendPlayerSettings(Client* client, bool broadcast = true);

	static void ReleaseData();

	static void SendExternalChange(Client * caller,bool sendToVisivle = true, bool broadcast = true);
private:

	static std::vector<Account*> _accounts;
	static std::vector<std::string> _playerNames;
	static std::vector<std::string> _accountsNames;
	static std::mutex _mainMutex;
	static std::mutex _dbMutex;
	static MySqlDriver * _driver;

};

#endif