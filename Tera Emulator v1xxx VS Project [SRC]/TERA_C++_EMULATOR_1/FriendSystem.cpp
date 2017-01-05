#include "FriendSystem.h"
#include "WorldSystem.h"
#include "Area.h"
#include "Account.hpp"
#include "Client.hpp"
#include "Player.hpp"
#include "WorldObject.h"
#include "Creature.h"
#include "PlayerEnums.h"
#include "HuntingZone.h"
#include "EffectZone.h"
#include "Projectile.h"
#include "StatsService.h"

#include "FileStream.h"
#include "Stream.h"



void FriendSystem::SendFriendList(Client * client)
{
	Stream s = Stream();

	s.WriteInt16(0);
	s.WriteInt16(0x8084); //S_FRIEND_LIST

	s.WriteInt32(0);
	short name_pos = s._pos;
	s.WriteInt16(0);
	s.WriteInt16(0); //unk 5b00 91
	s.WritePos(name_pos);
	s.WriteString("Gazah Server");
	s.WriteInt16(0);

	s.WritePos(0);

	client->Send(s._raw, s._size);
	
}
