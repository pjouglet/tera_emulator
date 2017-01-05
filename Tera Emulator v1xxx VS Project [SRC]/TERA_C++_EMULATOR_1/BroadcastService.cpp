#include "BroadcastService.h"
#include "Client.hpp"
#include "Stream.h"
#include "Inventory.h"
#include "ItemEnum.h"
#include "Account.hpp"
#include "Player.hpp"
#include "Drop.h"
#include "ChatEnum.h"
#include "OpCodesEnum.h"

BroadcastSystem::BroadcastSystem()
{
	_mainRun = true;
	_mainThread = std::thread(Main, this);
	_mainThread.detach();

	_sdRun = true;
	_spawnDespawnThread = std::thread(SpawnDespawnMain, this);
	_spawnDespawnThread.detach();
}

BroadcastSystem::~BroadcastSystem()
{
	ToSendPacket * packet = 0;
	while (_toSendList.try_pop(packet))
	{
		if (packet)
			delete packet;
		packet = 0;
	}

	while (_toSendSpawnDespawnList.try_pop(packet))
	{
		if (packet)
			delete packet;
		packet = 0;
	}

	_toSendList.clear();
}

const bool BroadcastSystem::InitBroadcastService(unsigned short threadCount)
{
	_instance = new BroadcastSystem();
	return true;
}

void BroadcastSystem::Release()
{
	_instance->_mainRun = false;
	_instance->_sdRun = false;

	_instance->_wait_Lock.notify_all();
	_instance->_wait_Lock2.notify_all();
	int ticks = 0;
	while (_instance->_sdRunning && _instance->_mainRunning)
	{
		ticks++;
		if (ticks >= BROADCAST_SERVICE_SHUTDOWN_TIMEOUT_TICKS)
			break;
		Sleep(1);
	}

	if (ticks >= BROADCAST_SERVICE_SHUTDOWN_TIMEOUT_TICKS)
	{
		std::cout << "::BroadcastService Shutdown fail!\n";
	}
	else
	{
		std::cout << "::BroadcastService Shutdown success! ticks[" << ticks << "][ms]\n";

		delete _instance;
		_instance = 0;
	}


}

void BroadcastSystem::Broadcast(Client* caller, Stream* s, BC_TYPE type, void** args)
{
	_instance->_toSendList.push(new ToSendPacket(caller, new Stream(s->_raw, s->_size), type, true, args));
	_instance->_wait_Lock.notify_one();
}

const bool BroadcastSystem::BroadcastSpawnDrop(Client * client, Drop * drop)
{
	if (client && drop)
	{
		void **args = new void*{ (void*)drop };
		_instance->_toSendSpawnDespawnList.push(new ToSendPacket(client, nullptr, DROP_SPAWN, false, args));
		_instance->_wait_Lock2.notify_one();
		return true;
	}

	return false;
}

const bool BroadcastSystem::BroadcastDespawnDrop(Client * client, long long dpEntityId)
{
	if (client)
	{
		long long *cpyEntityId = new long long;
		(*cpyEntityId) = dpEntityId;
		void ** args = new void*{ cpyEntityId };
		_instance->_toSendSpawnDespawnList.push(new ToSendPacket(client, nullptr, DROP_DESPAWN, false, args));
		_instance->_wait_Lock2.notify_one();
		return true;
	}
	return false;
}

const bool BroadcastSystem::BroadcastSpawnPlayer(Client * caller, Client * toSpawn)
{
	if (caller && toSpawn)
	{
		void** args = new void*{ (void*)toSpawn };
		_instance->_toSendSpawnDespawnList.push(new ToSendPacket(caller, nullptr, PLAYER_SPAWN, false, args));
		_instance->_wait_Lock2.notify_one();
		return true;
	}
	return false;
}

const bool BroadcastSystem::BroadcastDespawnPlayer(Client * caller, int entityid, int subId)
{
	if (caller)
	{
		long long *id = new long long;
		(*id) = (long long)(entityid << 32 | subId);
		void** args = new void*{ id };

		_instance->_toSendSpawnDespawnList.push(new ToSendPacket(caller, nullptr, PLAYER_DESPAWN, false, args));
		_instance->_wait_Lock2.notify_one();
		return true;
	}

	return false;
}

void BroadcastSystem::Main(BroadcastSystem * instance)
{
	ToSendPacket * packet = 0;
	instance->_mainRunning = true;
	while (instance->_mainRun)
	{
		if (instance->_toSendList.empty())
		{
			instance->_wait_Lock.wait(std::unique_lock<std::mutex>(instance->_locker));
		}
		while (instance->_mainRun && instance->_toSendList.try_pop(packet))
		{
			if (packet && packet->_callerClient)
			{

				switch (packet->_bcType)
				{
				case ME:
				{
					packet->_callerClient->Send(packet->_data);

				}break;
				case VISIBLE_CLIENTS:
				{
					packet->_callerClient->SendToVisibleClients(packet->_data);
				}break;
				case ME_VISIBLE_CLIENTS:
				{

					packet->_callerClient->Send(packet->_data);
					packet->_callerClient->SendToVisibleClients(packet->_data);
				}break;

				case CHAT:
				{
					ChatType type = (ChatType)*(int*)packet->_args[0];

					switch (type)
					{
					case MAIN_CHAT:
					{
						for (size_t i = 0; i < packet->_callerClient->_visibleClients.size(); i++)
						{
							if (packet->_callerClient->_visibleClients[i])
								packet->_callerClient->_visibleClients[i]->Send(packet->_data);
						}


						packet->_callerClient->Send(packet->_data->_raw, packet->_data->_size);//send to us to



					}break;
					case PARTY_CHAT:
					{

					}break;
					case GUILD_CHAT:
					{

					}break;
					case TRADE_CHAT:
					{

					}
					}

					delete packet->_args[0];
					delete packet->_args;
					packet->_args = 0;

				}break;
				default:
					break;
				}

				packet->_data->Clear();
				delete packet->_data;
				packet->_data = 0;

				delete packet;
				packet = 0;
			}
			else if (packet)
			{
				delete packet;
				packet = nullptr;
			}
		}
	}

	if (packet)
	{
		delete packet;
		packet = nullptr;
	}
	instance->_mainRunning = false;
}

void BroadcastSystem::SpawnDespawnMain(BroadcastSystem * instance)
{
	ToSendPacket * packet = 0;
	instance->_sdRunning = true;
	Stream data = Stream();

	while (instance->_mainRun)
	{
		if (instance->_toSendList.empty())
		{
			instance->_wait_Lock2.wait(std::unique_lock<std::mutex>(instance->_locker2));
		}

		while (instance->_mainRun && instance->_toSendSpawnDespawnList.try_pop(packet))
		{
			if (packet)
			{
				switch (packet->_bcType)
				{
				case DROP_SPAWN:
				{
					if (!packet->_callerClient)
					{
						delete packet->_args[0];
						packet->_args[0] = nullptr;
						delete packet->_args;
						packet->_args = nullptr;
						break;
					}
					Drop * dp = (Drop*)packet->_args[0];

					data.Clear();
					data.WriteInt16(0);
					data.WriteInt16(S_SPAWN_DROPITEM);
					data.WriteInt16(0);
					short ownersPos = data.NextPos();
					data.WriteInt64(dp->_entityId);
					data.WriteFloat(dp->X);
					data.WriteFloat(dp->Y);
					data.WriteFloat(dp->Z);
					data.WriteInt32(dp->_itemId);
					data.WriteInt32(dp->_stackCount);
					data.WriteInt32(dp->_unk1);
					data.WriteInt32(dp->_unk2);
					data.WriteInt16(dp->_unk3);
					data.WriteInt32(dp->_unk4);
					data.WriteInt32(dp->_unk5);
					data.WritePos(ownersPos);
					for (size_t j = 0; j < dp->_ownersEntityIds.size(); j++)
						data.WriteInt32(dp->_ownersEntityIds[j]);
					if (dp->_ownersEntityIds.size() == 0)
						data.WriteInt16(0);
					data.WritePos(0);

					packet->_callerClient->Send(&data);

					packet->_args[0] = nullptr;
				}break;

				case DROP_DESPAWN:
				{
					if (!packet->_callerClient)
					{
						delete packet->_args[0];
						packet->_args[0] = nullptr;
						delete packet->_args;
						packet->_args = nullptr;
						break;
					}
					long long* dpEntityId = (long long*)packet->_args[0];

					data.Clear();
					data.WriteInt16(12);
					data.WriteInt16(S_DESPAWN_DROPITEM);
					data.WriteInt64(*dpEntityId);

					packet->_callerClient->Send(&data);
					data.Clear();

					delete dpEntityId;
					dpEntityId = nullptr;
					packet->_args[0] = nullptr;
				}break;

				case PLAYER_SPAWN:
				{
					Client* toSpawn = (Client*)packet->_args[0];
					if (!packet->_callerClient || !toSpawn || !toSpawn->HasSelectedPlayer() || !packet->_callerClient->HasSelectedPlayer())
					{
						packet->_args[0] = nullptr;
						break;
					}

					Player* p = toSpawn->GetSelectedPlayer();
					Inventory* iv = p->_inventory;

					data.Clear();
					data.WriteInt16(0);
					data.WriteInt16(S_SPAWN_USER);

					data.WriteInt64(0);

					short namePos = data.NextPos();
					short guildNamePos = data.NextPos();
					short Title = data.NextPos();
					short details1Pos = data.NextPos();
					data.WriteInt16(32);
					short gTitlePos = data.NextPos();
					short gTitleIconPos = data.NextPos();
					short details2Pos = data.NextPos();
					data.WriteInt16(64);

					data.WriteInt32(0);
					data.WriteInt32(packet->_callerClient->GetAccount()->_entityId);
					data.WriteInt32(p->_entityId);
					data.WriteInt32(p->_subId);


					data.WriteFloat(p->_position->_X);
					data.WriteFloat(p->_position->_Y);
					data.WriteFloat(p->_position->_Z);
					data.WriteInt16(p->_position->_heading);

					data.WriteInt32(0); //relation ?? enemy / party member ...
					data.WriteInt32(p->_model);
					data.WriteInt16(0); //allawys 0?
					data.WriteInt16(70); //unk2
					data.WriteInt16(170); //unk3
					data.WriteInt16(0); //unk4 allways 0?
					data.WriteInt16(0); //unk5 0-3 ?

					data.WriteByte(1);
					data.WriteByte(p->_stats.GetHP() > 0 ? 1 : 0); //alive

					data.Write(p->_data, 8);

					data.WriteInt32((*iv)[PROFILE_WEAPON]->_info->_itemId);
					data.WriteInt32((*iv)[PROFILE_ARMOR]->_info->_itemId);
					data.WriteInt32((*iv)[PROFILE_GLOVES]->_info->_itemId);
					data.WriteInt32((*iv)[PROFILE_BOOTS]->_info->_itemId);

					data.WriteInt32((*iv)[PROFILE_INNERWARE]->_info->_itemId);
					data.WriteInt32((*iv)[PROFILE_MASK]->_info->_itemId); //head
					data.WriteInt32((*iv)[PROFILE_HEAD_ADRONMENT]->_info->_itemId); //face

					data.WriteInt32(0); //unk 0-1-3 ??
					data.WriteInt32(0); //mount...
					data.WriteInt32(7); //7 ???
					data.WriteInt32(0); // Title id

					data.WriteInt64(0);

					data.WriteInt64(0);
					data.WriteInt64(0);

					data.WriteInt64(0);
					data.WriteInt64(0);

					data.WriteInt64(0);
					data.WriteInt64(0);

					data.WriteInt32(0);	  //unk s
					data.WriteInt16(0);
					data.WriteByte(0); //allaways 0?

					data.WriteByte((*iv)[PROFILE_WEAPON]->_info->_enchantLevel);
					data.WriteByte((*iv)[PROFILE_ARMOR]->_info->_enchantLevel);
					data.WriteByte((*iv)[PROFILE_GLOVES]->_info->_enchantLevel);
					data.WriteByte((*iv)[PROFILE_BOOTS]->_info->_enchantLevel);

					data.WriteByte(0);
					data.WriteByte(0);

					data.WriteInt16(p->_stats._level);
					data.WriteInt16(0);   //always 0?
					data.WriteInt32(0);   //always 0?

					data.WriteInt32(0);
					data.WriteByte(1); //unk boolean?

					data.WriteInt32(0);	//skins ?
					data.WriteInt32(0);	//skins ?
					data.WriteInt32(0);	//skins ?
					data.WriteInt32(0);	//skins ?
					data.WriteInt32(0);	//skins ?
					data.WriteInt32(0); //costumeDye # ?

					data.WriteInt32(0);
					data.WriteInt32(0);

					data.WriteByte(1); //boolean?

					data.WriteInt32(1); //aliance
					data.WriteInt32(100);
					data.WriteInt32(0);
					data.WriteInt32(256001);
					data.WriteInt32(0);

					data.WriteByte(1); //boolean?
					data.WriteInt32(100);

					data.WriteFloat(1); //allways 1.0f?

					data.WritePos(namePos);
					data.WriteString(p->_name);

					data.WritePos(guildNamePos);
					data.WriteInt16(0);


					data.WritePos(Title);
					data.WriteInt16(0);

					data.WritePos(details1Pos);
					data.Write(p->_details1, 32);


					data.WritePos(gTitlePos);
					data.WriteInt16(0);
					data.WritePos(gTitleIconPos);
					data.WriteInt16(0);

					data.WritePos(details2Pos);
					data.Write(p->_details2, 64);
					data.WritePos(0);
					packet->_callerClient->Send(&data);
					data.Clear();

					packet->_args[0] = nullptr;
				}break;

				case PLAYER_DESPAWN:
				{
					if (!packet->_callerClient)
					{
						delete packet->_args[0];
						packet->_args[0] = nullptr;
						break;
					}
					long long  id = *(long long*)packet->_args[0];

					data.WriteInt16(16);
					data.WriteInt16(S_DESPAWN_USER);
					data.WriteInt64(id);
					data.WriteInt32(0);
					packet->_callerClient->Send(&data);
					data.Clear();

					delete packet->_args[0];
					packet->_args[0] = nullptr;

				}break;
				default:
					break;
				}

				delete packet;
				packet = nullptr;
			}

		}
	}

	data.Clear();
	if (packet)
	{
		delete packet;
		packet = nullptr;
	}
	instance->_sdRunning = false;
}


BroadcastSystem * BroadcastSystem::_instance = 0;
