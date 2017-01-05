#include "RChat.h"
#include "ChatEnum.h"
#include "Inventory.h"
#include "Area.h"
#include "MessagingSystem.h"
#include "Server.hpp"
#include "CreatureStats.h"
#include "ItemEnum.h"
#include "PassivityService.h"
#include "PassivitySystem.h"
#include "StatsService.h"

RChat::RChat() : SendPacket(C_CHAT)
{
}

void RChat::Process(OpCode opCode, Stream * data, Client * caller) const
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;

	short textOffset = data->ReadInt16();
	ChatType type = (ChatType)data->ReadInt16();

	data->_pos = textOffset;
	std::string text = data->ReadUTF16StringBigEdianToASCII();
	std::string message = "";


	if (text.size() > 12)
		for (size_t i = 6; i < text.size() - 7; i++)
		{
			message += text[i];
		}
	if (message != "" && ServerUtils::StringStartsWith(message, "./"))
	{
		if (ServerUtils::StringStartsWith(message, "./spawn"))
		{
			if (message.size() > 8)
			{
				int mobId = 0;
				sscanf_s(message.c_str(), "./spawn %d", &mobId);
				std::cout << ">>SPAWNED MobId[" << mobId << "]\n";
			}
			else
			{
				//todo send back notice [with ./spawn form]
			}

			return;
		}
		else if (ServerUtils::StringStartsWith(message, "./setlevel"))
		{
			int level = 0;
			sscanf_s(message.c_str(), "./setlevel %d", &level);
			p->_stats._level = level;
			StatsService::SendPlayerStats(caller);
		}
		else if (ServerUtils::StringStartsWith(message, "./setmovespeed"))
		{
			int speed = 0;
			sscanf_s(message.c_str(), "./setmovespeed %d", &speed);
			p->_stats._movementSpeed = speed;
			StatsService::SendPlayerStats(caller);
		}
		else if (ServerUtils::StringStartsWith(message, "./addgold"))
		{
			int gold = 0;
			sscanf_s(message.c_str(), "./addgold %d", &gold);
			p->_inventory->AddGold(gold);
			p->_inventory->SendInventory(caller, 0);
		}
		else if (ServerUtils::StringStartsWith(message, "./expandinventory"))
		{
			int rows = 0;
			sscanf_s(message.c_str(), "./expandinventory %d", &rows);
			p->_inventory->ExpandInventory(rows);
			p->_inventory->SendInventory(caller, 0);
		}
		else if (ServerUtils::StringStartsWith(message, "./cleargold"))
		{
			p->_inventory->ClearGold();
			p->_inventory->SendInventory(caller, 0);
		}
		else if (ServerUtils::StringStartsWith(message, "./st"))
		{
			int status = 0; int val2 = 0; int last = 0;
			sscanf_s(message.c_str(), "./st %d %d %d", &status, &val2, &last);


			data->Clear();
			data->WriteInt16(19);
			data->WriteInt16(S_USER_STATUS);
			data->WriteInt32(p->_entityId);
			data->WriteInt32(p->_subId);
			data->WriteInt32(status);
			data->WriteInt16(val2);
			data->WriteByte(last);
			caller->Send(data);
			data->Clear();

			caller->Send(data);
		}
		else if (ServerUtils::StringStartsWith(message, "./drop"))
		{
			int itemId = 0;
			sscanf_s(message.c_str(), "./drop %d", &itemId);

			WorldSystem::DropItem(caller, itemId);
		}
		else if (ServerUtils::StringStartsWith(message, "./rf"))
		{
			StatsService::SendPlayerStats(caller);
		}
		else if (ServerUtils::StringStartsWith(message, "./pf"))
		{
			data->Clear();

			data->WriteInt16(22);
			data->WriteInt16(S_PLAYER_CHANGE_ALL_PROF);
			data->WriteInt32(0);
			data->WriteInt32(0);
			data->WriteInt32(0);
			data->WriteInt32(0);
			data->WriteInt16(0);

			caller->Send(data);
		}
		else if (ServerUtils::StringStartsWith(message, "./cleardp"))
		{
			Area * ar = p->_currentArea;
			ar->ClearDrop();
		}
		else if (ServerUtils::StringStartsWith(message, "./sysmsg"))
		{
			std::string msg = "";
			for (size_t i = 8; i < message.size(); i++)
				msg += message[i];
			if (!ServerUtils::StringStartsWith(msg, "@"))
				msg.insert(msg.begin(), '@');

			MessagingSystem::SendSystemMessage(caller, msg);
		}
		else if (ServerUtils::StringStartsWith(message, "./dg"))
		{
			int type = 1;
			sscanf_s(message.c_str(), "./dg %d", &type);
			int toWrite[] = { 1, 2,3,4,5,6 };
			data->Clear();
			data->WriteInt16(6);
			data->WriteInt16(S_DUNGEON_UI_HIGHLIGHT);

			data->WriteInt16(0); //count
			short next = data->NextPos();

			for (size_t i = 0; i < 6; i++)
			{
				data->WritePos(next);
				data->WriteInt16(data->_pos);
				next = data->NextPos();
				data->WriteInt32(toWrite[i]);
				data->WriteByte(type);
			}

			data->WritePos(0);
			caller->Send(data);
			data->Clear();
		}
		else if (ServerUtils::StringStartsWith(message, "./exit"))
		{
			std::cout << ">>CLIENT DISCONNECT REQUEST\n";
			data->Clear();
			caller->Close();
			return;
		}
		else if (ServerUtils::StringStartsWith(message, "./additem"))
		{
			int id = 0; int ammount = 1;
			sscanf(message.c_str(), "./additem %d %d", &id, &ammount);
			if (id > 0)
			{
				if (ammount > 0 && ammount < 1000)
					for (size_t k = 0; k < ammount; k++)
					{
						(*p->_inventory) << id;
					}
				else
					(*p->_inventory) << id;

				p->_inventory->SendInventory(caller, 0);
			}
		}
		else if (ServerUtils::StringStartsWith(message, "./clearinventory"))
		{
			p->_inventory->ClearInventory(caller);

		}
		return;
	}

	data->Clear();
	data->WriteInt16(0);
	data->WriteInt16(S_CHAT);
	short namePos = data->NextPos();
	short textPos = data->NextPos();
	data->WriteInt32(type);
	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);
	data->WriteByte(0); //chat icon...
	data->WriteByte(caller->GetAccount()->_isGm ? 1 : 0); //is gm
	data->WriteByte(0); //unk chat icon
	data->WritePos(namePos);
	data->WriteString(p->_name);
	data->WritePos(textPos);
	data->WriteString(text);
	data->WritePos(0);

	BroadcastSystem::Broadcast(caller, data, ME, 0);
	BroadcastSystem::Broadcast(caller, data, VISIBLE_CLIENTS, 0);
}
