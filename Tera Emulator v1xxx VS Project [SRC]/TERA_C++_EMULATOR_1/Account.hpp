#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <string>
#include "Entity.h"

#include "Crypt\data_type.hpp"

#define MAX_PLAYERS_PER_ACCOUNT 8

class Player; class Client;
class Account : public Entity
{
	friend class PlayerService;
public:
	Account();
	~Account();

	const unsigned int GetPlayerCount() const;

	Player* GetPlayer(int id);
	Player* GetPlayerByLobbyId(int lobbyid);
	Player* GetSelectedPlayer();
	Player*  SelectPlayer(int lobbyId);

	void SendPlayerList(Client* caller);
	void AddPlayer(Player* p);
	const bool RemovePlayer(Player * p);

	void SendAccountSettings(Client * caller, bool broadcast = true);

	std::string
		_username,
		_password,
		_email,
		_hardwareInfo;

	int _lasOnlineUtc,
		_accountSettingsSize,
		_coins,
		_playerCount,
		_lasPlayerSubId;

	byte  
		*_accountSettings,
		_lastLobbyId;

	long long 
		_remainingPlayTime;


	bool
		_isGm;
	Client *
		_owner;
private:
	Player * _selectedPlayer;
	std::vector<Player*> _playerList;
};
#endif

