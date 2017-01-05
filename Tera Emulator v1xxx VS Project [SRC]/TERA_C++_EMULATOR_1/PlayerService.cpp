#include "PlayerService.h"

#include "Area.h"
#include "Stream.h"
#include "Account.hpp"
#include "Client.hpp"
#include "Player.hpp"
#include "mysql\MySqlDriver.h"
#include "mysql\SQLStream.h"
#include "ServerUtils.hpp"
#include "OpCodesEnum.h"

#include "PlayerEnums.h"
#include "Player.hpp"
#include "Account.hpp"
#include "WorldPosition.h"
#include "InventoryService.h"
#include "WorldSystem.h"
#include "SkillService.h"
#include "ServerTimer.h"
#include "LevelingService.h"
#include "BroadcastService.h"
#include "Inventory.h"
#include "InventorySlot.h"
#include "Skill.h"
#include "CreatureStats.h"
#include "StatsService.h"
#include "ItemEnum.h"

#include <sstream>
#include <Windows.h>
#include <ostream>
#include "PassivityService.h"

const int PlayerService::InitializePlayerService(MySqlDriver * driver)
{
	if (!driver)
		return -1;
	_driver = driver;
	int t = 0;
	while (!driver->Lock())
	{
		t++;
		if (t >= 500)
			break;
	}
	if (t >= 500)
		return -2;

	int count = 0;
	sql::ResultSet * result = 0;
	result = driver->ExecuteQuery("SELECT * FROM accounts");
	std::stringstream sbuild;
	while (result->next())
	{
		Account * newAccount = new Account();


		newAccount->_username = result->getString(2).c_str();
		newAccount->_password = result->getString(3).c_str();
		newAccount->_email = result->getString(4).c_str();
		newAccount->_lasOnlineUtc = result->getInt64(5);
		newAccount->_coins = result->getInt(6);
		newAccount->_isGm = result->getBoolean(7);
		newAccount->_remainingPlayTime = (short)result->getInt(8);
		newAccount->_hardwareInfo = "";

		std::istream * hardwareInfoBlob = result->getBlob(9);
		std::istream * accountSettings = result->getBlob(10);

		if (hardwareInfoBlob)
		{
			Stream tempHardwareStream = Stream(hardwareInfoBlob);
			newAccount->_hardwareInfo = std::string((const char*)tempHardwareStream._raw, tempHardwareStream._size);

			tempHardwareStream.Clear();
			delete hardwareInfoBlob;
			hardwareInfoBlob = nullptr;
		}

		if (accountSettings)
		{
			accountSettings->seekg(0, std::ifstream::end);
			int SettingsSize = accountSettings->tellg();
			accountSettings->seekg(0, std::ifstream::beg);
			if (SettingsSize > 0)
			{
				newAccount->_accountSettingsSize = SettingsSize;
				newAccount->_accountSettings = new byte[newAccount->_accountSettingsSize];
				accountSettings->read((char*)newAccount->_accountSettings, newAccount->_accountSettingsSize);
			}
			else
			{
				newAccount->_accountSettingsSize = 0;
				newAccount->_accountSettings = nullptr;
			}
			delete accountSettings;
			accountSettings = 0;
		}
		else
		{
			newAccount->_accountSettings = nullptr;
			newAccount->_accountSettingsSize = 0;
		}

		_accountsNames.push_back(newAccount->_username);

		sbuild << "SELECT *, a.id as account_id FROM players p LEFT JOIN accounts a ON (a.username = p.username) WHERE p.username='" << newAccount->_username << "'";
		sql::ResultSet* res = 0; res = driver->ExecuteQuery(sbuild.str().c_str());
		while (res->next()) //Get players
		{
			Player * newPlayer = new Player();
			newPlayer->_id = res->getInt("id");
			newPlayer->_account_id = res->getInt("account_id");
			newPlayer->_subId = newAccount->_lasPlayerSubId;
			newAccount->_lasPlayerSubId++;

			newPlayer->_newPlayer = false;
			newPlayer->_playerInfo = new Player::PlayerInfo;

			newPlayer->_name = res->getString("name").c_str();
			_playerNames.push_back(newPlayer->_name);
			newPlayer->_position = new WorldPosition();
			newPlayer->_position->_X = (float)res->getDouble("x");
			newPlayer->_position->_Y = (float)res->getDouble("y");
			newPlayer->_position->_Z = (float)res->getDouble("z");
			newPlayer->_position->_heading = (float)res->getInt("h");

			newPlayer->_position->_continentId = (short)res->getInt("areaId");
			/*newPlayer->_position->_worldMapGuardId = res->getInt(21);
			newPlayer->_position->_worldMapWorldId = res->getInt(22);
			newPlayer->_position->_worldMapSectionId = res->getInt(23);*/

			newPlayer->_playerInfo->pRace = (PlayerRace)res->getInt("race");
			newPlayer->_playerInfo->pGender = (PlayerGender)res->getInt("gender");
			newPlayer->_playerInfo->pClass = (PlayerClass)res->getInt("class");

			newPlayer->_exp = res->getInt(10);
			newPlayer->_restedExp = res->getInt(11);
			newPlayer->_stats._level = (short)res->getInt("level");

			newPlayer->_lastOnlineUTC = res->getInt64("lastOnlineUTC");
			newPlayer->_creationTimeUTC = res->getInt64("creationTimeUTC");
			newPlayer->_banTimeUTC = res->getInt64("banTimeUTC");

			std::istream *details1S = res->getBlob("details1");
			std::istream *details2S = res->getBlob("details2");
			std::istream * dataS = res->getBlob("headData");
			//std::istream * visitedSectionsBlob = res->getBlob(20); //todo
			std::istream * visitedSectionsBlob = nullptr;
			std::cout << "6" << std::endl;
			newPlayer->_data = new byte[8];
			newPlayer->_details1 = new byte[32];
			newPlayer->_details2 = new byte[64];


			details1S->read((char*)newPlayer->_details1, 32);
			details2S->read((char*)newPlayer->_details2, 64);
			dataS->read((char*)newPlayer->_data, 8);

			delete dataS;
			dataS = 0;
			delete details1S;
			details1S = 0;
			delete details2S;
			details2S = 0;

			if (visitedSectionsBlob)
			{
				delete visitedSectionsBlob;
				visitedSectionsBlob = 0;
			}

			newPlayer->_model = 10000;
			newPlayer->_model += (newPlayer->_playerInfo->pRace * 2 + 1 + newPlayer->_playerInfo->pGender) * 100;
			newPlayer->_model += newPlayer->_playerInfo->pClass + 1;


			sbuild.clear(); sbuild.str("");

			sbuild << "SELECT * FROM `player_inventory` WHERE username='" << newAccount->_username << "' AND name='" << newPlayer->_name << "'";
			sql::ResultSet * inventory = 0;
			inventory = driver->ExecuteQuery(sbuild.str().c_str());
			sbuild.clear();
			sbuild.str("");

			sbuild << "SELECT * FROM `player_deposit` WHERE username='" << newAccount->_username << "' AND name='" << newPlayer->_name << "'";
			sql::ResultSet * bank = 0;
			bank = driver->ExecuteQuery(sbuild.str().c_str());
			sbuild.clear();
			sbuild.str("");

			sbuild << "SELECT * FROM `player_skills` WHERE username='" << newAccount->_username << "' AND name='" << newPlayer->_name << "'";
			sql::ResultSet * skills = 0;
			skills = driver->ExecuteQuery(sbuild.str().c_str());
			sbuild.clear();
			sbuild.str("");

			sbuild << "SELECT * FROM `player_settings` WHERE username='" << newAccount->_username << "' AND name='" << newPlayer->_name << "'";
			sql::ResultSet * settings = 0;
			settings = driver->ExecuteQuery(sbuild.str().c_str());
			//todo : Revoir la fonction d'inventaire
			newPlayer->_inventory = new Inventory(newPlayer);
			if (inventory && inventory->next())
			{
				newPlayer->_inventory->Initialize((short)inventory->getInt(4));
				newPlayer->_inventory->AddGold(inventory->getInt64(5));

				int itemsCount = inventory->rowsCount();
				if(itemsCount <= 72 + 19)
				{
					for(size_t i = 0; i < itemsCount; i++)
					{
						
					}
				}
				std::istream * blobData = inventory->getBlob(3);

				Stream st = Stream(blobData);

				itemsCount = st.ReadInt32();
				newPlayer->_inventory->_itemCount = itemsCount;
				if (itemsCount <= 72 + 19)
					for (size_t i = 0; i < itemsCount; i++)
					{
						int slotId = st.ReadInt32();
						int itemId = st.ReadInt32();

						IItem * item = InventoryService::ResolveItem(itemId);
						if (!item)
							continue;

						(*newPlayer->_inventory)[slotId]->_isEmpty = 0;
						(*newPlayer->_inventory)[slotId]->_info->_item = item;
						(*newPlayer->_inventory)[slotId]->_info->_itemId = itemId;

						(*newPlayer->_inventory)[slotId]->_info->_hasCrystals = st.ReadByte();
						for (byte j = 0; j < (*newPlayer->_inventory)[slotId]->_info->_hasCrystals; j++)
							(*newPlayer->_inventory)[slotId]->_info->_crystals[j] = st.ReadInt32();

						(*newPlayer->_inventory)[slotId]->_info->_isMasterworked = st.ReadByte();
						(*newPlayer->_inventory)[slotId]->_info->_isAwakened = st.ReadByte();
						(*newPlayer->_inventory)[slotId]->_info->_isEnigmatic = st.ReadByte();
						(*newPlayer->_inventory)[slotId]->_info->_enchantLevel = st.ReadByte();
						(*newPlayer->_inventory)[slotId]->_info->_isBinded = st.ReadByte();
						(*newPlayer->_inventory)[slotId]->_info->_binderEntityId = st.ReadInt32();
						(*newPlayer->_inventory)[slotId]->_info->_isCrafted = st.ReadByte();
						(*newPlayer->_inventory)[slotId]->_info->_crafterEntityId = st.ReadInt32();
						(*newPlayer->_inventory)[slotId]->_info->_stackCount = st.ReadInt32();

						short passivitiesCount = st.ReadInt16();
						for (short j = 0; j < passivitiesCount; j++)
						{
							Passivity * ps = PassivityService::ResolvePassivity(st.ReadInt32());
							if (ps)
								(*newPlayer->_inventory)[slotId]->_info->_passivities.push_back(ps);
						}

					}

				st.Clear();
				if (blobData)
				{
					delete blobData;
					blobData = 0;
				}

				newPlayer->_inventory->RecalculateLevels();

				delete inventory;
				inventory = 0;
			}
			else
				newPlayer->_inventory->Initialize(40);

			if (bank && bank->next())
			{
				delete bank;
				bank = 0;
			} //needs work

			if (skills && skills->next())
			{
				int skillsCount = skills->getInt(4);
				std::istream * blobData = skills->getBlob(3);
				if (blobData)
				{
					Stream skillStream = Stream(blobData);

					for (size_t i = 0; i < skillsCount; i++)
					{
						Skill *sk = nullptr;
						if ((sk = SkillService::ResolveSkill(skillStream.ReadInt32())))
							newPlayer->_skillList.push_back(sk);
					}

					delete blobData;
					blobData = 0;
				}

				delete skills;
				skills = 0;
			}

			if (settings && settings->next())
			{
				std::istream* blobData = settings->getBlob(3);
				if (blobData)
				{
					blobData->seekg(0, std::ifstream::end);
					int size = blobData->tellg();
					blobData->seekg(0, std::ifstream::beg);

					newPlayer->_playerSettings = new byte[size];
					memset(newPlayer->_playerSettings, 0, size);

					blobData->read((char*)newPlayer->_playerSettings, size);

					newPlayer->_settingSize = size;

					delete blobData;
					blobData = 0;
				}
				else
				{
					newPlayer->_playerSettings = nullptr;
					newPlayer->_settingSize = 0;
				}

				delete settings;
				settings = 0;
			}

			StatsService::CalculatePlayerStats(newPlayer);
			newAccount->AddPlayer(newPlayer);
		}
		if (res)
		{
			delete res;
			res = 0;
		}

		sbuild.clear();	sbuild.str("");
		_accounts.push_back(newAccount);
		if (count == -1)
			count = 1;
		else
			count++;
	}

	driver->Unlock();
	return count;
}

const bool PlayerService::CheckPlayerNameForm(std::string name)
{
	return true; //todo
}

const bool PlayerService::CheckPlayerName(std::string name)
{
	for (size_t i = 0; i < _playerNames.size(); i++)
	{
		if (_playerNames[i] == name)
			return false;
	}
	return true;
}

Account* PlayerService::PerformAccountLogin(const char * unsername, const char * password)
{
	std::lock_guard<std::mutex> lock(_mainMutex);
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_username == unsername && _accounts[i]->_password == password)
		{
			return _accounts[i];
		}
	}

	return nullptr;
}

Account * PlayerService::GetAccount(int accountIndex)
{

	Account * result = nullptr;
	if (accountIndex >= 0 && accountIndex <= (int)_accounts.size())
	{
		result = _accounts[accountIndex];
	}

	return result;
}

unsigned int PlayerService::GetAccountCount()
{
	return _accounts.size();
}

void PlayerService::UpdateAccountData(Account * account)
{
	if (!account || !_driver)
		return;

	sql::PreparedStatement * s = nullptr;
	std::lock_guard<std::mutex> lock(_mainMutex);
	int result = 0;
	for (size_t i = 0; i < account->_playerList.size(); i++)
	{
		Player * p = account->_playerList[i];
		if (!p)
			continue;
		else if (p->_toDelete == 1 && !p->_newPlayer)
		{
			p->_toDelete = 2;
			//players

			s = _driver->GetPreparedStatement("DELETE  FROM players WHERE name=?");
			s->setString(1, p->_name.c_str());
			try
			{
				s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:" << e.what() << "\n";
			}

			delete s;
			s = nullptr;

			//player_inventory
			s = _driver->GetPreparedStatement("DELETE FROM player_inventory WHERE name=?");
			s->setString(1, p->_name.c_str());

			try
			{
				s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:" << e.what() << "\n";
			}
			delete s;
			s = nullptr;

			//player_bank
			s = _driver->GetPreparedStatement("DELETE FROM player_bank WHERE name=?");
			s->setString(1, p->_name.c_str());
			try
			{
				s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:" << e.what() << "\n";
			}
			delete s;
			s = nullptr;

			//player_skills
			s = _driver->GetPreparedStatement("DELETE FROM player_skills WHERE name=?");
			s->setString(1, p->_name.c_str());
			try
			{
				s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:" << e.what() << "\n";
			}
			delete s;
			s = nullptr;

			//player_settings
			s = _driver->GetPreparedStatement("DELETE FROM player_settings WHERE name=?");
			s->setString(1, p->_name.c_str());
			try
			{
				s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:" << e.what() << "\n";
			}
			delete s;
			s = nullptr;

			std::cout << "::DELETED name[" << p->_name << "]\n";

		}
		else if (p->_toDelete == 1 && p->_newPlayer)
			continue;
		else if (p->_toDelete == 0 && p->_newPlayer)
		{
			result = 0; p->_newPlayer = false;
#pragma region account
			s = _driver->GetPreparedStatement("UPDATE accounts SET coins=?,isGm=?,lastOnlineUTC=? WHERE username=?");
			s->setInt(1, 0);//todo----------------------------------------------------
			s->setBoolean(2, account->_isGm);
			s->setInt64(3, ServerTimer::GetCurrentUTC());
			s->setString(4, account->_username.c_str());

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED UPDATE account [" << e.what() << "]\n";
			}

			delete s;
			s = nullptr;

			if (account->_accountSettingsSize > 0 && account->_accountSettings)
			{
				s = _driver->GetPreparedStatement("UPDATE accounts SET accountSettings=?,accountSettingsSize=? WHERE username=?");

				std::istringstream  accSettings = std::istringstream(std::string((const char*)account->_accountSettings, account->_accountSettingsSize));
				s->setBlob(1, &accSettings);
				s->setInt(2, account->_accountSettingsSize);
				s->setString(3, account->_username.c_str());
				try
				{
					result = s->executeUpdate();
				}
				catch (const sql::SQLException& e)
				{
					std::cout << ">>Error:FAILED UPDATE accountSettings [" << e.what() << "]\n";
				}

				delete s;
				s = nullptr;
			}

			if (account->_hardwareInfo.size() > 0)
			{
				s = _driver->GetPreparedStatement("UPDATE accounts SET hardwareInfo=? WHERE username=?");

				std::istringstream  hardwareInfo = std::istringstream(account->_hardwareInfo);
				s->setBlob(1, &hardwareInfo);
				s->setString(2, account->_username.c_str());
				try
				{
					result = s->executeUpdate();
				}
				catch (const sql::SQLException& e)
				{
					std::cout << ">>Error:FAILED UPDATE accountHardwareInfo [" << e.what() << "]\n";
				}

				delete s;
				s = nullptr;
			}
#pragma endregion
#pragma region players
			std::istringstream details1 = std::istringstream(std::string((const char*)p->_details1, 32));
			std::istringstream details2 = std::istringstream(std::string((const char*)p->_details2, 64));
			std::istringstream data = std::istringstream(std::string((const char*)p->_data, 8));

			sql::PreparedStatement * s = _driver->GetPreparedStatement("INSERT INTO players(username,name,x,y,z,h,race,gender,class,exp,restedExp,areaId,level,details1,details2,headData,lastOnlineUTC,creationTimeUTC,banTimeUTC,visitedSections,worldMapGuardId,worldMapWorldId,worldMapSectionId) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
			s->setString(1, account->_username.c_str());
			s->setString(2, p->_name.c_str());

			s->setDouble(3, p->_position->_X);
			s->setDouble(4, p->_position->_Y);
			s->setDouble(5, p->_position->_Z);
			s->setInt(6, p->_position->_heading);

			s->setInt(7, p->_playerInfo->pRace);
			s->setInt(8, p->_playerInfo->pGender);
			s->setInt(9, p->_playerInfo->pClass);

			s->setInt64(10, p->_exp);
			s->setInt64(11, p->_restedExp);

			s->setInt(12, p->_position->_continentId);
			s->setInt(13, p->_stats._level);

			s->setBlob(14, &details1);
			s->setBlob(15, &details2);
			s->setBlob(16, &data);

			s->setUInt64(17, ServerTimer::GetCurrentUTC());
			s->setUInt64(18, p->_creationTimeUTC);
			s->setUInt64(19, p->_banTimeUTC);
			s->setNull(20, 0);

			s->setInt(21, p->_position->_worldMapGuardId);
			s->setInt(22, p->_position->_worldMapWorldId);
			s->setInt(23, p->_position->_worldMapSectionId);
			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED TO INSERT player" << e.what() << "\n";
			}


			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_bank
			Stream bankStream = Stream();
			bankStream.WriteInt32(0);//itemsCount todo

			s = _driver->GetPreparedStatement("INSERT INTO player_bank(username,name,items,slotCount,gold) VALUES(?,?,?,?,?)");
			s->setString(1, account->_username.c_str());
			s->setString(2, p->_name.c_str());

			std::istringstream bankBlob = std::istringstream(std::string((const char*)bankStream._raw, bankStream._size));
			s->setBlob(3, &bankBlob);
			s->setInt(4, (int)(9 * 8) * 4);
			s->setInt(5, 0); //todo

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED TO INSERT player_bank" << e.what() << "\n";
			}

			bankStream.Clear();

			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_inventory
			//todo : Revoir l'inventaire
			Stream * inventoryRaw = p->_inventory->GetItemsRAW();
			std::istringstream invBlob = std::istringstream(std::string((const char*)inventoryRaw->_raw, inventoryRaw->_size));
			s = _driver->GetPreparedStatement("INSERT INTO player_inventory(username, name, items, itemsCount, gold) VALUES(?,?,?,?,?)");
			s->setString(1, account->_username.c_str());
			s->setString(2, p->_name.c_str());
			s->setBlob(3, &invBlob);

			s->setInt(4, p->_inventory->_slotCount);
			s->setInt(5, p->_inventory->_gold);

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED TO INSERT player_inventory" << e.what() << "\n";
			}

			delete inventoryRaw;
			inventoryRaw = 0;

			s->close();
			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_settings
			s = _driver->GetPreparedStatement("INSERT INTO player_settings(username,name,settings) VALUES(?,?,?)");
			s->setString(1, account->_username.c_str());
			s->setString(2, p->_name.c_str());
			if (p->_playerSettings)
			{
				std::istringstream pSettingsBlob = std::istringstream(std::string((const char*)p->_playerSettings, p->_settingSize));
				s->setBlob(3, &pSettingsBlob);
			}
			else
				s->setNull(3, 0);

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED TO INSERT player_settings" << e.what() << "\n";
			}

			s->close();
			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_skills
			Stream skillStream = Stream();
			for (size_t i = 0; i < p->_skillList.size(); i++)
				skillStream.WriteInt32(p->_skillList[i]->_id);
			s = _driver->GetPreparedStatement("INSERT INTO player_skills(username,name,learnedSkills,skillCount) VALUES(?,?,?,?)");
			s->setString(1, account->_username.c_str());
			s->setString(2, p->_name.c_str());

			if (skillStream._size >= 4)
			{
				std::istringstream skillsBlob = std::istringstream(std::string((const char*)skillStream._raw, skillStream._size));
				s->setBlob(3, &skillsBlob);
			}
			else
				s->setNull(3, 0);

			s->setInt(4, p->_skillList.size());

			result = 0;
			try
			{
				s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED TO INSERT player_skills" << e.what() << "\n";
			}

			skillStream.Clear();
			s->close();
			delete s;
			s = nullptr;
#pragma endregion
		}
		else if (p->_toDelete == 0 && !p->_newPlayer)
		{
			result = 0;
#pragma region account
			s = _driver->GetPreparedStatement("UPDATE accounts SET coins=?,isGm=?,lastOnlineUTC=? WHERE username=?");
			s->setInt(1, 0);//todo----------------------------------------------------
			s->setBoolean(2, account->_isGm);
			s->setInt64(3, ServerTimer::GetCurrentUTC());
			s->setString(4, account->_username.c_str());

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED UPDATE account [" << e.what() << "]\n";
			}

			delete s;
			s = nullptr;

			if (account->_accountSettingsSize > 0 && account->_accountSettings)
			{
				s = _driver->GetPreparedStatement("UPDATE accounts SET accountSettings=?,accountSettingsSize=? WHERE username=?");

				std::istringstream  accSettings = std::istringstream(std::string((const char*)account->_accountSettings, account->_accountSettingsSize));
				s->setBlob(1, &accSettings);
				s->setInt(2, account->_accountSettingsSize);
				s->setString(3, account->_username.c_str());
				try
				{
					result = s->executeUpdate();
				}
				catch (const sql::SQLException& e)
				{
					std::cout << ">>Error:FAILED UPDATE accountSettings [" << e.what() << "]\n";
				}

				delete s;
				s = nullptr;
			}

			if (account->_hardwareInfo.size() > 0)
			{
				s = _driver->GetPreparedStatement("UPDATE accounts SET hardwareInfo=? WHERE username=?");

				std::istringstream  hardwareInfo = std::istringstream(account->_hardwareInfo);
				s->setBlob(1, &hardwareInfo);
				s->setString(2, account->_username.c_str());
				try
				{
					result = s->executeUpdate();
				}
				catch (const sql::SQLException& e)
				{
					std::cout << ">>Error:FAILED UPDATE accountHardwareInfo [" << e.what() << "]\n";
				}

				delete s;
				s = nullptr;
			}
#pragma endregion
#pragma region players
			std::istringstream details1 = std::istringstream(std::string((const char*)p->_details1, 32));
			std::istringstream details2 = std::istringstream(std::string((const char*)p->_details2, 64));
			std::istringstream data = std::istringstream(std::string((const char*)p->_data, 8));

			sql::PreparedStatement * s = _driver->GetPreparedStatement("UPDATE players SET x=?, y=?, z=?, h=?, race=?, gender=?, class=?, exp=?, restedExp=?, areaId=?, level=?, details1=?, details2=?, headData=?, lastOnlineUTC=?, banTimeUTC=? WHERE name=?");
			s->setDouble(1, p->_position->_X);
			s->setDouble(2, p->_position->_Y);
			s->setDouble(3, p->_position->_Z);
			s->setInt(4, p->_position->_heading);

			s->setInt(5, p->_playerInfo->pRace);
			s->setInt(6, p->_playerInfo->pGender);
			s->setInt(7, p->_playerInfo->pClass);

			s->setInt64(8, p->_exp);
			s->setInt64(9, p->_restedExp);

			s->setInt(10, p->_position->_continentId);
			s->setInt(11, p->_stats._level);

			s->setBlob(12, &details1);
			s->setBlob(13, &details2);
			s->setBlob(14, &data);


			s->setInt64(15, ServerTimer::GetCurrentUTC());
			s->setInt64(16, p->_banTimeUTC);

			/*s->setInt(17, p->_position->_worldMapGuardId);
			s->setInt(18, p->_position->_worldMapWorldId);
			s->setInt(19, p->_position->_worldMapSectionId);*/

			s->setString(17, p->_name.c_str());
			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED UPDATE players [" << e.what() << "]\n";
			}

			s->close();
			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_inventory
			//todo : revoir le système d'inventaire
			s = _driver->GetPreparedStatement("DELETE FROM player_inventory WHERE name=?");
			s->setString(1, p->_name.c_str());
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED UPDATE player_inventory [" << e.what() << "]\n";
			}
			s->close();
			delete s;
			s = nullptr;

			Stream* rawItems = p->_inventory->GetItemsRAW(); std::istringstream itemsBlob = std::istringstream(std::string((const char*)rawItems->_raw, rawItems->_size));
			s = _driver->GetPreparedStatement("INSERT INTO player_inventory(username, name, items, itemsCount, gold) VALUES(?,?,?,?,?)");
			s->setString(1, account->_username.c_str());
			s->setString(2, p->_name.c_str());
			s->setBlob(3, &itemsBlob);

			s->setInt(4, p->_inventory->_slotCount);
			s->setInt(5, p->_inventory->_gold);

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED UPDATE player_inventory [" << e.what() << "]\n";
			}


			if (rawItems)
			{
				delete rawItems;
				rawItems = 0;
			}
			s->close();
			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_settings
			s = _driver->GetPreparedStatement("UPDATE player_settings SET settings=? WHERE name=?");

			if (p->_playerSettings)
			{
				std::istringstream pSettingsBlob = std::istringstream(std::string((const char*)p->_playerSettings, p->_settingSize));
				s->setBlob(1, &pSettingsBlob);
			}

			s->setString(2, p->_name.c_str());

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED UPDATE player_settings [" << e.what() << "]\n";
			}

			s->close();
			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_skills
			s = _driver->GetPreparedStatement("DELETE FROM player_skills WHERE name=?");
			s->setString(1, p->_name.c_str());
			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED TO DELETE player_skills" << e.what() << "\n";
			}
			s->close();
			delete s;
			s = nullptr;


			Stream skillStream = Stream();
			for (size_t i = 0; i < p->_skillList.size(); i++)
				skillStream.WriteInt32(p->_skillList[i]->_id);
			s = _driver->GetPreparedStatement("INSERT INTO player_skills(username,name,learnedSkills,skillCount) VALUES(?,?,?,?)");
			s->setString(1, account->_username.c_str());
			s->setString(2, p->_name.c_str());

			if (skillStream._size >= 4)
			{
				std::istringstream skillsBlob = std::istringstream(std::string((const char*)skillStream._raw, skillStream._size));
				s->setBlob(3, &skillsBlob);
			}
			else
				s->setNull(3, 0);

			s->setInt(4, p->_skillList.size());

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED TO INSERT player_skills" << e.what() << "\n";
			}

			skillStream.Clear();
			s->close();
			delete s;
			s = nullptr;
#pragma endregion
#pragma region player_bank
			Stream bankStream = Stream();
			bankStream.WriteInt32(0); //itemsCount

			s = _driver->GetPreparedStatement("UPDATE player_bank SET items=?, itemscount=?, gold=? WHERE account_id=?");

			std::istringstream bankBlob = std::istringstream(std::string((const char*)bankStream._raw, bankStream._size));
			s->setBlob(1, &bankBlob);

			s->setInt(2, (int)(9 * 8) * 4);
			s->setInt(3, 0); 
			s->setInt(4, p->_account_id);

			result = 0;
			try
			{
				result = s->executeUpdate();
			}
			catch (const sql::SQLException& e)
			{
				std::cout << ">>Error:FAILED UPDATE player_bank [" << e.what() << "]\n";
			}

			bankStream.Clear();
			s->close();
			delete s;
			s = nullptr;
#pragma endregion
		}
	}

}

void PlayerService::SendPlayerSettings(Client * client, bool broadCast)
{
	if (client->HasSelectedPlayer())
	{
		Player * p = client->GetSelectedPlayer();
		Stream s = Stream();
		s.WriteInt16(0);
		s.WriteInt16(S_LOAD_CLIENT_USER_SETTING);
		s.WriteInt16(8);
		s.WriteInt16(p->_settingSize);
		s.Write(p->_playerSettings, p->_settingSize);
		s.WritePos(0);

		if (broadCast)
			BroadcastSystem::Broadcast(client, &s, ME, 0);
		else
			client->Send(&s);
	}
}

void PlayerService::ReleaseData()
{
	for (size_t i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i])
		{
			delete _accounts[i];
			_accounts[i] = 0;
		}
	}
	_accounts.clear();

	_playerNames.clear();
	_accountsNames.clear();

	_driver = nullptr;
}

void PlayerService::SendExternalChange(Client * caller, bool sendToVisivle , bool broadcast)
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;

	Stream * data = new Stream();
	data->WriteInt16(0);
	data->WriteInt16(S_USER_EXTERNAL_CHANGE);

	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);

	data->WriteInt32((*p->_inventory)[PROFILE_WEAPON]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_ARMOR]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_GLOVES]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_BOOTS]->_info->_itemId);

	data->WriteInt32((*p->_inventory)[PROFILE_INNERWARE]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_MASK]->_info->_itemId); //head
	data->WriteInt32((*p->_inventory)[PROFILE_HEAD_ADRONMENT]->_info->_itemId); //face


	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);
	data->WriteInt64(0);

	data->WriteByte((*p->_inventory)[PROFILE_WEAPON]->_info->_enchantLevel);
	data->WriteByte((*p->_inventory)[PROFILE_ARMOR]->_info->_enchantLevel);
	data->WriteByte((*p->_inventory)[PROFILE_GLOVES]->_info->_enchantLevel);
	data->WriteByte((*p->_inventory)[PROFILE_BOOTS]->_info->_enchantLevel);

	data->WriteInt32((*p->_inventory)[PROFILE_SKIN_HEAD]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_SKIN_FACE]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_SKIN_BACK]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_SKIN_WEAPON]->_info->_itemId);
	data->WriteInt32((*p->_inventory)[PROFILE_SKIN_BODY]->_info->_itemId);

	data->WriteInt32(0); //costume dye
	data->WriteByte(1); //enables skin, hair adornment, mask, and costume (back is always on)

	data->WritePos(0);

	if (broadcast)
	{
		if (sendToVisivle)
			BroadcastSystem::Broadcast(caller, data, ME_VISIBLE_CLIENTS, 0);
		else
			BroadcastSystem::Broadcast(caller, data, ME, 0);
	}
	else
	{
		if (sendToVisivle)
			caller->SendToVisibleClients(data);

		caller->Send(data);
	}

	data->Clear();
	delete data;
	data = 0;
}


std::vector<Account*> PlayerService::_accounts;
std::mutex PlayerService::_mainMutex;
std::mutex PlayerService::_dbMutex;
std::vector<std::string> PlayerService::_playerNames;
std::vector<std::string> PlayerService::_accountsNames;
MySqlDriver * PlayerService::_driver = 0;


