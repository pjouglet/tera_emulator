#include "Player.hpp"
#include "ServerTimer.h"
#include "Area.h"
#include "Stream.h"
#include "OpCodesEnum.h"

Player::Player() : CreatureBase()
{
	_toDelete = 0;
	_playerInfo = 0;
	_exp = 0;
	_restedExp = 0;
	_data = 0;
	_details1 = 0;
	_details2 = 0;
	_name = "";
	_lastOnlineUTC = 0;
	_banTimeUTC = 0;
	_creationTimeUTC = 0;
	_newPlayer = 0;
	_visibleRange = 2000;
	_playerSettings = 0;
}

Player::~Player()
{
	if (_playerInfo)
	{
		delete _playerInfo;
		_playerInfo = 0;
	}

	if (_data)
	{
		delete[] _data;
		_data = 0;
	}
	if (_details1)
	{
		delete[] _details1;
		_details1 = 0;
	}
	if (_details2)
	{
		delete[] _details2;
		_details2 = 0;
	}
	if (_position)
	{
		delete _position;
		_position = 0;
	}
	if (_playerSettings)
	{
		delete[] _playerSettings;
		_playerSettings = 0;
	}
	if (_inventory)
	{
		delete _inventory;
		_inventory = 0;
	}
	if (_moveStream)
	{
		delete _moveStream;
		_moveStream = 0;
	}
	
}



