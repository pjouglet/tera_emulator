#include "RLoadTopoFin.h"
#include "CreatureStats.h"
#include "WorldPosition.h"
#include "Area.h"
#include "MessagingSystem.h"
#include "StatsService.h"
#include "CreatureStats.h"

RLoadTopoFin::RLoadTopoFin() : SendPacket(C_LOAD_TOPO_FIN)
{
}

void RLoadTopoFin::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player * p = nullptr;
	if (!(p = caller->GetSelectedPlayer()))
		return;
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_VISITED_SECTION_LIST);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_REQUEST_INVITE_GUILD_TAG);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_USER_BLOCK_LIST);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(0);
	data->WriteInt16(S_FRIEND_GROUP_LIST);
	data->WriteInt16(1);
	data->WriteInt16(8);
	data->WriteInt16(8);
	data->WriteInt16(0);
	data->WriteInt16(18);
	data->WriteInt16(2);
	data->WriteInt16(0);
	data->WriteString("Prieteni1");

	data->WritePos(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(0);
	data->WriteInt16(S_FRIEND_LIST);
	data->WriteInt32(0);
	short name_pos = data->NextPos();
	data->WritePos(name_pos);
	data->WriteString("[Gazah Server]");
	data->WritePos(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_UPDATE_FRIEND_INFO);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	caller->GetAccount()->SendAccountSettings(caller, false);
	PlayerService::SendPlayerSettings(caller, false);
	
	data->WriteInt16(12);
	data->WriteInt16(S_TRADE_BROKER_CALC_NOTIFY);
	data->WriteInt32(0);
	data->WriteInt32(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(14);
	data->WriteInt16(S_PARCEL_READ_RECV_STATUS);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_ONGOING_LEVEL_EVENT_LIST);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_ONGOING_HUNTING_EVENT_LIST);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_EP_SYSTEM_DAILY_EVENT_EXP_ON_OFF);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	if (!WorldSystem::EnterWorld(caller))
		return;

	data->WriteInt16(30);
	data->WriteInt16(S_SPAWN_ME);

	data->WriteInt32(p->_entityId); //pid
	data->WriteInt32(p->_subId); //pid

	data->WriteFloat(p->_position->_X);
	data->WriteFloat(p->_position->_Y);
	data->WriteFloat(p->_position->_Z);
	data->WriteInt16(p->_position->_heading);
	data->WriteInt16(p->_stats.GetHP() > 0 ? 1 : 0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	
	data->WriteInt16(18);
	data->WriteInt16(S_RESET_CHARM_STATUS);
	data->WriteInt32(0);
	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	//MessagingSystem::SendSystemMessage(caller, "@888");

	data->WriteInt16(23);
	data->WriteInt16(S_ADD_CHARM_STATUS);
	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);
	data->WriteInt32(50300); //charm id?
	data->WriteByte(1); // unk
	data->WriteInt32(0x7FFFFFFF);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	StatsService::SendPlayerStats(caller, false);

	data->WriteInt16(22);
	data->WriteInt16(S_PLAYER_CHANGE_ALL_PROF);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(30);
	data->WriteInt16(S_F2P_PremiumUser_Permission);
	data->WriteInt16(1);		//unk
	data->WriteInt16(20);		//unk
	data->WriteInt32(5);		//unk
	data->WriteFloat(1.0f);		//unk
	data->WriteFloat(1.0f);		//unk
	data->WriteInt32(20);		//unk
	data->WriteInt32(1);		//unk
	data->WriteInt16(0);		//unk
	caller->Send(data);
	data->Clear();

	data->WriteInt16(18);
	data->WriteInt16(S_CREST_INFO);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(0);
	data->WriteInt16(S_LOAD_ACHIEVEMENT_LIST);
	data->WriteInt32(0); 
	data->WriteInt16(0);//count
	data->WriteInt16(0);//next
	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);
	data->WriteInt32(1123); //unk
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt16(0);
	data->WritePos(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(10);
	data->WriteInt16(S_LOAD_SKILL_SCRIPT_LIST);
	data->WriteInt32(0);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(19);
	data->WriteInt16(S_USER_STATUS);
	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);
	data->WriteInt32(p->_stats.status);
	data->WriteInt16(0);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(18);
	data->WriteInt16(S_SKILL_PERIOD);
	data->WriteInt32(0);
	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();
}
