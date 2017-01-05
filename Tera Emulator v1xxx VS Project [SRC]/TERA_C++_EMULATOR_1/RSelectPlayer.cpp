#include "RSelectPlayer.h"
#include "Client.hpp"
#include "Account.hpp"
#include "Player.hpp"
#include "PlayerService.h"
#include "SkillService.h"
#include "InventoryService.h"
#include "Server.hpp"
#include "GuildSystem.h"
#include "WorldSystem.h"
#include "CraftingSystem.h"
#include "UnionSystem.h"
#include "Area.h"
#include "Inventory.h"
#include "ItemEnum.h"

RSelectPlayer::RSelectPlayer() : SendPacket(C_SELECT_USER)
{
}

void RSelectPlayer::Process(OpCode opCode, Stream * data, Client * caller)const
{
	int lobbyid = data->ReadInt32();
	Player * p = caller->GetAccount()->SelectPlayer(lobbyid);
	Inventory * iv = p->_inventory;

	data->Clear();
	data->WriteInt16(16);
	data->WriteInt16(S_SELECT_USER);
	data->WriteInt32(p == 0 ? 0 : 1);
	data->WriteInt64(0);
	caller->Send(data);
	data->Clear();
	if (!p)
		return;


	GuildSystem::BrodcastGuildFlag(caller);
	UnionSystem::SendElectionState(caller);

	data->WriteInt16(8);
	data->WriteInt16(S_ONGOING_HUNTING_EVENT_LIST);
	data->WriteInt32(0);
	caller->Send(data);
	data->Clear();

#pragma region S_LOGIN

	data->WriteInt16(0);
	data->WriteInt16(S_LOGIN);

	short name_pos = data->NextPos();

	short details1_pos = data->NextPos();
	data->WriteInt16(32);

	short details2_pos = data->NextPos();
	data->WriteInt16(64);

	data->WriteInt32(p->_model);

	data->WriteInt32(p->_entityId); //player id
	data->WriteInt32(p->_subId);    //player sub id
	data->WriteInt32(20 + SERVER_ID);	//server id
	data->WriteInt32(p->_lobbyId);  //lobby  id

	data->WriteInt32(0);   //unk
	data->WriteByte(p->_stats.GetHP() > 0 ? 1 : 0);
	data->WriteInt32(0);   //unk
	data->WriteInt32(50);  //unk
	data->WriteInt32(110); //unk
	data->Write(p->_data, 8); //int64 data [appearance]

	data->WriteInt16(1); //unk
	data->WriteInt16(p->_stats._level);

	data->WriteInt16(1);	//mining
	data->WriteInt16(0);	//0
	data->WriteInt16(1);	//plants 
	data->WriteInt16(1);	//energy

	data->WriteInt32(1);	//unk
	data->WriteInt16(0);	//unk

	data->WriteInt32(0);    //unk
	
	data->WriteInt64(p->_exp); //rested exp?
	data->WriteInt64(p->_exp); //player exp
	data->WriteInt64(840); //next level exp

	data->WriteInt64(0);	//unk
	data->WriteInt64(0);	//unk
	data->WriteInt32(0x04BD0768); //restedCurrent
	data->WriteInt32(0x04BD0768); //restedMax
	data->WriteFloat(1);	//unk
	data->WriteInt32(0);	//unk

	data->WriteInt32((*iv)[PROFILE_WEAPON]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_ARMOR]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_GLOVES]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_BOOTS]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_INNERWARE]->_info->_itemId); //unk
	data->WriteInt32((*iv)[PROFILE_HEAD_ADRONMENT]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_MASK]->_info->_itemId);

	data->WriteInt64(0x0B59F357); //creation time ?
	data->WriteInt64(1); //unk
	data->WriteByte(0); //unk

	data->WriteInt32(0); //reaper? 03 00 00 00 în cazul în care 3, cuvintele "Îngerul Morții"
	data->WriteInt32(0); 

	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00

	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00

	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00
	data->WriteInt32(0);  // 00 00 00 00

	data->WriteByte((*iv)[PROFILE_WEAPON]->_info->_enchantLevel);
	data->WriteByte((*iv)[PROFILE_ARMOR]->_info->_enchantLevel);
	data->WriteByte((*iv)[PROFILE_GLOVES]->_info->_enchantLevel);
	data->WriteByte((*iv)[PROFILE_BOOTS]->_info->_enchantLevel);

	data->WriteByte(0);
	data->WriteInt32(0); // 78 00 00 00 .//karma player.get Karma ()
	data->WriteByte(0);

	data->WriteInt32((*iv)[PROFILE_SKIN_HEAD]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_FACE]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_BACK]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_WEAPON]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_BODY]->_info->_itemId);
	data->WriteInt32(0); //unk

	data->WriteInt32(0); // 00 00 00 00
	data->WriteInt32(0); // 00 00 00 00
	data->WriteInt32(0); // 00 00 00 00

	data->WriteInt32(1); // 01 00 00 00
	data->WriteInt32(0); // 00 00 00 00
	data->WriteByte(0);	

	data->WriteInt32(100); 
	data->WriteFloat(1.0f);

	data->WriteByte(0);	 
	data->WriteInt32(0); 
	 
	data->WriteInt32(0); //unk

	data->WritePos(name_pos);
	data->WriteString(p->_name);

	data->WritePos(details1_pos);
	data->Write(p->_details1, 32);

	data->WritePos(details2_pos);
	data->Write(p->_details2, 64);

	data->WritePos(0);
	caller->Send(data);
	data->Clear();
#pragma endregion

	data->WriteInt16(8);
	data->WriteInt16(S_SHOW_NPC_TO_MAP);
	data->WriteInt32(0);
	//caller->Send(data);
	data->Clear();

	p->_inventory->SendInventory(caller, 0,false);

#pragma region S_SKILL_LIST
	data->WriteInt16(10);
	data->WriteInt16(S_SKILL_LIST);
	data->WriteInt16(0);
	data->WriteInt16(8);
	data->WriteInt16(8);
	caller->Send(data);
	data->Clear();
#pragma endregion

	//todo S_SKILL_CATEGORY

	data->WriteInt16(8);
	data->WriteInt16(S_AVAILABLE_SOCIAL_LIST);
	data->WriteInt32(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(6);
	data->WriteInt16(S_CLEAR_QUEST_INFO);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(11);
	data->WriteInt16(S_DAILY_QUEST_COMPLETE_COUNT);
	data->WriteInt16(0);
	data->WriteInt32(20);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();


	data->WriteInt16(0);
	data->WriteInt16(S_ARTISAN_SKILL_LIST);
	data->WriteInt32(0); //count
	data->WriteInt16(0);
	data->WritePos(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(12);
	data->WriteInt16(S_ARTISAN_RECIPE_LIST);
	data->WriteInt32(0);
	data->WriteInt16(256);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(0);
	data->WriteInt16(S_NPCGUILD_LIST);
	data->WriteInt16(0); //npc guild count [faction]
	short unk_pos = data->_pos;

	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);

	data->WritePos(unk_pos);
	data->WriteInt32(0); //region
	data->WriteInt32(0); //faction
	data->WriteInt32(0); //rank  # enum { suspicious = 0, apprehensive = 3, wavering, neutral, favorable, friendly, trusted, revered }
	data->WriteInt32(0); //reputation
	data->WriteInt32(0); //credits
	data->WritePos(0);
	caller->Send(data);
	data->Clear();


	data->WriteInt16(4);
	data->WriteInt16(S_PET_INFO_CLEAR);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(12);
	data->WriteInt16(S_VIRTUAL_LATENCY);
	data->WriteInt32(0);
	data->WriteInt32(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(8);
	data->WriteInt16(S_MOVE_DISTANCE_DELTA);
	data->WriteFloat(200);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(8);
	data->WriteInt16(S_MY_DESCRIPTION);
	data->WriteInt32(6);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(28);
	data->WriteInt16(S_F2P_PremiumUser_Permission);
	data->WriteInt16(1);
	data->WriteInt16(20);
	data->WriteInt32(5);

	data->WriteFloat(1);
	data->WriteFloat(1);

	data->WriteInt32(20);
	data->WriteInt32(1);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(28);
	data->WriteInt16(S_MASSTIGE_STATUS);
	data->WriteInt32(0); //D9 63 01 00
	data->WriteInt32(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	caller->Send(data);
	data->Clear();


#pragma region S_USER_ITEM_EQUIP_CHANGER
	short nextPos = 0; int changer[] = { 1,3,4,5,6,7,8,9,10,11,19,20 };

	data->WriteInt16(0);
	data->WriteInt16(S_USER_ITEM_EQUIP_CHANGER);

	data->WriteInt16(12); //count
	nextPos = data->NextPos();

	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);

	for (size_t i = 0; i < 12; i++)
	{
		data->WritePos(nextPos);
		data->WriteInt16(data->_pos); //base offset
		nextPos = data->NextPos();
		data->WriteInt64(changer[i]);
	}

	data->WritePos(0);
	caller->Send(data);
	data->Clear();
#pragma endregion
#pragma region S_USER_EXTERNAL_CHANGE
	//equiped items
	data->WriteInt16(0);
	data->WriteInt16(S_USER_EXTERNAL_CHANGE);

	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);

	data->WriteInt32((*iv)[PROFILE_WEAPON]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_ARMOR]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_GLOVES]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_BOOTS]->_info->_itemId);


	data->WriteInt32((*iv)[PROFILE_INNERWARE]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_MASK]->_info->_itemId); //head
	data->WriteInt32((*iv)[PROFILE_HEAD_ADRONMENT]->_info->_itemId); //face


	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);

	data->WriteByte((*iv)[PROFILE_WEAPON]->_info->_enchantLevel);
	data->WriteByte((*iv)[PROFILE_ARMOR]->_info->_enchantLevel);
	data->WriteByte((*iv)[PROFILE_GLOVES]->_info->_enchantLevel);
	data->WriteByte((*iv)[PROFILE_BOOTS]->_info->_enchantLevel);


	data->WriteInt32((*iv)[PROFILE_SKIN_HEAD]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_FACE]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_BACK]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_WEAPON]->_info->_itemId);
	data->WriteInt32((*iv)[PROFILE_SKIN_BODY]->_info->_itemId);

	data->WriteInt32(0); //costume dye
	data->WriteByte(1); //enables skin, hair adornment, mask, and costume (back is always on)

	data->WritePos(0);
	caller->Send(data);
	data->Clear();
#pragma endregion

	data->WriteInt16(10);
	data->WriteInt16(S_FESTIVAL_LIST);
	data->WriteInt16(0);//count
	data->WriteInt16(8);
	data->WriteInt16(8);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(21);
	data->WriteInt16(S_LOAD_TOPO);
	data->WriteInt32(p->_position->_continentId);
	data->WriteFloat(p->_position->_X);
	data->WriteFloat(p->_position->_Y);
	data->WriteFloat(p->_position->_Z);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(8);
	data->WriteInt16(S_LOAD_HINT);
	data->WriteInt32(0);
	caller->Send(data);
	data->Clear();

	StatsService::SendPlayerStats(caller, false);

	data->WriteInt16(9);
	data->WriteInt16(S_ACCOUNT_BENEFIT_LIST);
	data->WriteInt32(0);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(16);
	data->WriteInt16(S_SEND_USER_PLAY_TIME);
	data->WriteInt32(p->_lastOnlineUTC);
	data->WriteInt64(0);
	caller->Send(data);
	data->Clear();


	data->WriteInt16(6);
	data->WriteInt16(S_CLEAR_WORLD_QUEST_VILLAGER_INFO);
	data->WriteInt16(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(12);
	data->WriteInt16(S_PCBANGINVENTORY_DATALIST);
	data->WriteInt64(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(12);
	data->WriteInt16(S_FATIGABILITY_POINT);
	data->WriteInt32(1);
	data->WriteInt32(4000);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(44);
	data->WriteInt16(S_LOAD_EP_INFO);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	caller->Send(data);
	data->Clear();

}


//A601CCA9 32014601 20006601 40005D2B
//0000D755 AC0F0080 0001AC0F 00000150
//37000000 00000100 00000036 00000078
//00000065 00020202 01010001 00010000
//00000000 00000001 00000000 00000000
//00010000 00000000 00010000 00000000
//00480300 00000000 00000000 00000000
//00000000 00000000 00000000 00A30100
//00000000 00000000 00112700 009C3A00
//009D3A00 009E3A00 00000000 00000000
//00000000 005D92C2 0B000000 00010000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000001 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 01000000 00000000
//00640000 00000080 3F010000 00000000
//00005400 61007200 74006100 72006900
//6E006100 00001004 080D0000 0000101B
//1F001010 00001C09 00130C0A 10000D1F
//0C091310 00000113 10131310 1313130F
//0F0F0F0F 0F0F1013 0A000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 0000

//BF02CEBE 04003B00 7263AC0F 00800001
//00000000 00000000 00010028 00000001
//00000001 00000000 00000000 00000000
//00000000 00000000 0000003B 00DC0000
//000000DA 00112700 00D3B581 31000000
//00015037 00000000 00010000 00000000
//00010000 00000000 001E0000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000005 00000005 00000005
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//FFFFFFFF 00000000 00000000 DC007D01
//00000000 7B019C3A 0000D4B5 81310000
//00000150 37000000 00000300 00000000
//00000100 00000000 00001E00 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 01000000 01000000
//01000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00FFFFFF FF000000 00000000 007D011E
//02000000 001C029D 3A0000D5 B5813100
//00000001 50370000 00000004 00000000
//00000001 00000000 0000001E 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00010000 00010000
//00010000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//0000FFFF FFFF0000 00000000 00001E02
//00000000 0000BD02 9E3A0000 D6B58131
//00000000 01503700 00000000 05000000
//00000000 01000000 00000000 1E000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000100 00000100
//00000100 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//000000FF FFFFFF00 00000000 000000


