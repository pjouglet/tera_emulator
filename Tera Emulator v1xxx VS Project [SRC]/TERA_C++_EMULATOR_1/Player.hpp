#ifndef PLAYER_H
#define PLAYER_H

#ifndef byte
#define byte unsigned char
#endif

#include "PlayerEnums.h"
#include "WorldPosition.h"
#include "CreatureBase.h"
#include <vector>


class IItem; class Skill; class Area; class Inventory;  class Area; struct AreaSection; class Stream;
class Player : public CreatureBase
{
	
public:
	struct PlayerInfo
	{
		PlayerClass		pClass;
		PlayerGender	pGender;
		PlayerRace		pRace;
	};
	
public:
	Player();
	~Player();

	PlayerInfo * _playerInfo;
	WorldPosition * _position;
	Inventory * _inventory;
	Area * _currentArea;

	byte
		* _playerSettings,
		*_details2,
		*_details1,
		*_data,
		_newPlayer,
		_toDelete;

	int
		_id,
		_account_id,
		_settingSize,
		_visibleRange,
		_model,
		_subId,
		_lobbyId,
		_exp;

	long long
		_banTimeUTC,
		_creationTimeUTC,
		_lastOnlineUTC,
		_restedExp,
		_maxExp;

	std::string _name;
	Stream * _moveStream;

	
	std::vector<int> _visitedSections;
	AreaSection* _currentVisitedSection;
};

#endif
