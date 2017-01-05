#ifndef FRIEND_SYSTEM_H
#define FRIEND_SYSTEM_H

#include <mutex>
#include <concurrent_queue.h>
#include <thread>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


class Player; class Account; class Area; class WorldPosition; class Client; class WorldObject; class Creature; class Projectile; class EffectZone; class HuntingZone;
class FriendSystem
{
public:

	static void SendFriendList(Client* client);



};



#endif

