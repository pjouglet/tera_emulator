#ifndef SENDPAKCET_H
#define SENDPAKCET_H

#include "Stream.h"
#include "OpCodesEnum.h"

#include "Client.hpp"
#include "Account.hpp"
#include "Player.hpp"

#include "PlayerService.h"
#include "InventoryService.h"
#include "WorldSystem.h"
#include "ChatSystem.h"
#include "SkillService.h"
#include "StatsService.h"
#include "FriendSystem.h"
#include "LevelingService.h"
#include "Skill.h"
#include "ServerTimer.h"
#include "BroadcastService.h"
#include "ServerUtils.hpp"

#include <vector>
#include <sstream>

class Client; class Account; class Player;
class SendPacket
{
	friend class BroadcastSystem;
public:
	SendPacket(OpCode toRecv, bool ordered = true);
	virtual void Process(OpCode opCode, Stream * data, Client* caller) const = 0;
	OpCode _toRecv;
	bool _orderedPacket;
};

#endif