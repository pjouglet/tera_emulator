#include "Area.h"
#include "Client.hpp"
#include "Player.hpp"
#include "Account.hpp"
#include "HuntingZone.h"
#include "EffectZone.h"
#include "Vector3.hpp"
#include "Drop.h"
#include "OpCodesEnum.h"
#include "Stream.h"
#include "BroadcastService.h"


Area::Area() : Entity()
{
	_mainRun = _running = false;
	_edit = false;
	_startPosition = 0;
	_playersCount = 0;
}
Area::~Area()
{
	CloseArea();

	for (size_t i = 0; i < _clients.size(); i++)
	{
		_clients[i] = 0;
	}
	_clients.clear();

	for (size_t i = 0; i < _worldObjects.size(); i++)
	{
		if (_worldObjects[i])
		{
			delete _worldObjects[i];
			_worldObjects[i] = 0;
		}
	}
	_worldObjects.clear();


	for (size_t i = 0; i < _effectsZones.size(); i++)
	{
		if (_effectsZones[i])
		{
			delete _effectsZones[i];
			_effectsZones[i] = 0;
		}
	}

	for (size_t i = 0; i < _huntingZones.size(); i++)
	{
		if (_huntingZones[i])
		{
			delete _huntingZones[i];
			_huntingZones[i] = 0;
		}
	}
	_huntingZones.clear();

	if (_startPosition)
	{
		delete _startPosition;
		_startPosition = 0;
	}

	for (size_t i = 0; i < _sections.size(); i++)
	{
		if (_sections[i])
		{
			delete _sections[i];
			_sections[i] = 0;
		}
	}
	_sections.clear();

	for (size_t i = 0; i < _drop.size(); i++)
	{
		if (_drop[i])
		{
			delete _drop[i];
			_drop[i] = nullptr;
		}
	}

}

const bool Area::Initialize()
{
	if (_sections.size() >= 1)
		_startWorldMapSectionId = _sections[0]->worldMapSectionId;

	return true;
}

void Area::Lock()
{
	_lockMutex.lock();
}

void Area::Unlock()
{
	_lockMutex.unlock();
}

WorldPosition * Area::GetStartPosition()
{
	return _startPosition->ToWorldPosition(_startHeading, _continentId, 599001, _worldMapGuardId, _worldMapWorldId); //599001  Stepstone Isle
}

const bool Area::ChangeArea(Client * client, Area * area)
{
	Player * p = 0;
	if (!(p = client->GetSelectedPlayer()))
		return false;

	this->ExitArea(client);
	return area->EnterArea(client);
}
void Area::CloseArea()
{
	Lock();
	if (_mainRun)
		_mainRun = false;
	for (size_t i = 0; i < _clients.size(); i++)
	{
		_clients[i]->Close();
		_clients[i] = 0;
	}
	_clients.clear();

	for (size_t i = 0; i < _drop.size(); i++)
	{
		if (_drop[i])
		{
			delete _drop[i];
			_drop[i] = nullptr;
		}
	}

	//mobs..etc
	Unlock();
}

const bool  Area::EnterArea(Client * client)
{
	if (!client)
		return false;
	Player * p = nullptr;
	if (!(p = client->GetSelectedPlayer()))
		return false;


	p->_position->_continentId = _continentId;
	p->_position->_worldMapGuardId = _worldMapGuardId;
	p->_position->_worldMapWorldId = _worldMapWorldId;
	p->_position->_worldMapSectionId = _startWorldMapSectionId;
	p->_currentArea = this;
	std::lock_guard<std::mutex> lock(_lockMutex);
	InitPlayerWorld(client);
	_clients.push_back(client);
	return true;
}
const bool Area::EnterArea(Client * client, int sectionId)
{
	if (!client)
		return false;
	Player * p = nullptr;
	if (!(p = client->GetSelectedPlayer()))
		return false;

	bool hasSection = false;
	for (size_t i = 0; i < _sections.size(); i++)
		if (_sections[i] && _sections[i]->worldMapSectionId == sectionId)
			hasSection = true;

	if (!hasSection)
		return false;
	p->_position->_continentId = _continentId;
	p->_position->_worldMapGuardId = _worldMapGuardId;
	p->_position->_worldMapWorldId = _worldMapWorldId;
	p->_currentArea = this;
	p->_position->_worldMapSectionId = sectionId;
	InitPlayerWorld(client);
	std::lock_guard<std::mutex> lock(_lockMutex);
	_clients.push_back(client);
	return true;
}

void Area::ClearDrop()
{
	std::lock_guard<std::mutex> locker(_lockMutex);

	for (size_t i = 0; i < _drop.size(); i++)
	{
		if (_drop[i])
		{
			for (size_t j = 0; j < _clients.size(); j++)
					BroadcastSystem::BroadcastDespawnDrop(_clients[j], _drop[i]->_entityId);

			delete _drop[i];
			_drop[i] = nullptr;
		}
	}

	_drop.clear();
}

void Area::RemoveDrop(int dropid)
{
	_lootLockMutex.lock();

	for (size_t i = 0; i < _drop.size(); i++)
	{
		if (_drop[i] && _drop[i]->_entityId == dropid)
		{
			delete _drop[i];
			_drop[i] = nullptr;

			_drop.erase(_drop.begin() + i);
			break;
		}
	}
	_lootLockMutex.unlock();


	for (size_t j = 0; j < _clients.size(); j++)
		BroadcastSystem::BroadcastDespawnDrop(_clients[j], dropid);
}

void Area::ExitArea(Client * client)
{
	if (!client)
		return;
	client->Disappear();
	Player *p = nullptr;
	if (!(p = client->GetSelectedPlayer()))
		return;

	std::lock_guard<std::mutex> lock(_lockMutex);
	for (size_t i = 0; i < _clients.size(); i++)
		if (_clients[i] == client)
		{
			_clients[i] = 0;
			_clients.erase(_clients.begin() + i);
			break;
		}

	p->_currentArea = nullptr;
}

void Area::AddDrop(Drop * drop)
{
	_toAddDrop.push(drop);
}

void Area::RemoveDrop(Drop * drop)
{
}

void Area::InitPlayerWorld(Client * caller)
{
	Player * me = nullptr; Player * you = nullptr;
	if ((me = caller->GetSelectedPlayer()) != 0)
	{
		for (size_t i = 0; i < _clients.size(); i++)
		{
			if (_clients[i] && _clients[i] != caller)
			{
				you = _clients[i]->GetSelectedPlayer();
				if (!you)
					continue;

				if (me->_position->_worldMapSectionId != you->_position->_worldMapSectionId)
					continue;

				double distance = me->_position->FastDistanceTo(you->_position);
				if (distance <= 10000)
				{
					caller->AddVisibleClient(_clients[i]);
					_clients[i]->AddVisibleClient(caller);
				}
			}
		}
		Stream* data = new Stream();
		Drop * dp = nullptr; short ownersPos = 0;
		for (size_t i = 0; i < _drop.size(); i++)
		{
			dp = _drop[i];
			if (!dp)
				continue;

			data->Clear();
			data->WriteInt16(0);
			data->WriteInt16(S_SPAWN_DROPITEM);
			data->WriteInt16(0);
			ownersPos = data->NextPos();
			data->WriteInt64(dp->_entityId);
			data->WriteFloat(dp->X);
			data->WriteFloat(dp->Y);
			data->WriteFloat(dp->Z);
			data->WriteInt32(dp->_itemId);
			data->WriteInt32(dp->_stackCount);
			data->WriteInt32(dp->_unk1);
			data->WriteInt32(dp->_unk2);
			data->WriteInt16(dp->_unk3);
			data->WriteInt32(dp->_unk4);
			data->WriteInt32(dp->_unk5);
			data->WritePos(ownersPos);
			for (size_t j = 0; j < dp->_ownersEntityIds.size(); j++)
				data->WriteInt32(dp->_ownersEntityIds[j]);
			if (dp->_ownersEntityIds.size() == 0)
				data->WriteInt16(0);

			data->WritePos(0);
			BroadcastSystem::Broadcast(caller, data, ME, 0);
		}
	}
}

void Area::ChangeSection(Client * client, int sectionId)
{
	Player * p = nullptr;
	if (!(p = client->GetSelectedPlayer()) || !p->_currentVisitedSection || p->_currentVisitedSection->worldMapSectionId != sectionId)
		return;
	//todo

}

const bool AreaSection::operator==(AreaSection& a)
{
	return (continentId == a.continentId) && (worldMapSectionId == a.worldMapSectionId);
}

const bool AreaSection::operator!=(AreaSection & a)
{
	return (a.continentId != continentId) && (a.worldMapSectionId != worldMapSectionId);
}

AreaSection::AreaSection()
{
	memset(this, 0, sizeof AreaSection);
}

AreaSection::~AreaSection()
{
	for (size_t i = 0; i < _fences.size(); i++)
	{
		if (_fences[i])
		{
			delete _fences[i];
			_fences[i] = 0;
		}
	}
	_fences.clear();
}



