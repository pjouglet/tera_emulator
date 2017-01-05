#include "SkillService.h"
#include "Skill.h"
#include "Stream.h"
#include "Client.hpp"
#include "Account.hpp"
#include "Player.hpp"
#include "FileStream.h"
#include "OpCodesEnum.h"
#include "Inventory.h"
#include "BroadcastService.h"

#include <fstream>
#include "XMLDocumentParser.h"


void SkillService::Release()
{
	for (size_t i = 0; i < _skills.size(); i++)
	{
		if (_skills[i])
		{
			delete _skills[i];
			_skills[i] = 0;
		}
	}
	_skills.clear();

	_warriorLearnSkillList.clear();
	_berserkerLearnSkillList.clear();
	_lancerLearnSkillList.clear();
	_slayerLearnSkillList.clear();
	_archerLearnSkillList.clear();
	_gunnerLearnSkillList.clear();
	_brawlerLearnSkillList.clear();
	_ninjaLearnSkillList.clear();
	_reaperLearnSkillList.clear();
	_mysticLearnSkillList.clear();
	_priestLearnSkillList.clear();
	_sorcererLearnSkillList.clear();
}

const bool SkillService::LoadSkills(const char * file)
{
	std::stringstream ss;
	ss << file << "\\info.txt" << '\0';
	std::fstream infoFile = std::fstream(ss.str());
	if (!infoFile.is_open())
		return false;

	int toReadFileCount = 0; std::string line;
	std::getline(infoFile, line); sscanf(line.c_str(), "count =%d", &toReadFileCount);
	if (toReadFileCount == 0)
		return false;
	std::vector<std::string> learnSkillLists;
	while (!infoFile.eof())
	{
		std::getline(infoFile, line);
		learnSkillLists.push_back(line);
	}
	infoFile.close();


	for (size_t i = 0; i < toReadFileCount; i++)
	{
		ss.clear();
		ss.str("");

		ss << file << "//SkillData-" << i << ".xml" << '\0';
		std::cout << "Loading skills from [SkillData-" << i << ".xml]\n";
		if (!XMLDocumentParser::ParseSkillXMLDocument(ss.str().c_str(), _skills))
			continue;
	}


#pragma region LearnSkillList
	ss.str("");
	ss.clear();

	while (1)
	{
		ss << file << "//" << line;
		if (ServerUtils::StringStartsWith(line, "warrior", true))
		{
			FileStream fs = FileStream(ss.str().c_str());
			if (!fs.IsOpen())
				break;

			int count = fs.ReadInt32();
			for (int i = 0; i < count; i++)
			{
				LearnSkill ls = LearnSkill(0, 0, 0, 0, 0, 0, 0);
				ls.unk1 = fs.ReadInt16();
				ls.unk2 = fs.ReadInt16();
				ls.unk3 = fs.ReadInt16();
				ls.unk4 = fs.ReadInt16();

				ls.skillId = fs.ReadInt32();
				ls.cost = fs.ReadInt32();
				ls.level = fs.ReadInt32();

				_warriorLearnSkillList.push_back(ls);
			}

		}
		else if (ServerUtils::StringStartsWith(line, "berserker", true))
		{
			FileStream fs = FileStream(ss.str().c_str());
			if (!fs.IsOpen())
				break;

			int count = fs.ReadInt32();
			for (int i = 0; i < count; i++)
			{
				LearnSkill ls = LearnSkill(0, 0, 0, 0, 0, 0, 0);
				ls.unk1 = fs.ReadInt16();
				ls.unk2 = fs.ReadInt16();
				ls.unk3 = fs.ReadInt16();
				ls.unk4 = fs.ReadInt16();

				ls.skillId = fs.ReadInt32();
				ls.cost = fs.ReadInt32();
				ls.level = fs.ReadInt32();

				_berserkerLearnSkillList.push_back(ls);
			}
		}

		//todo
		break;
	}

#pragma endregion
	return true;
}

const unsigned int SkillService::GetCount()
{
	return _skills.size();
}

Skill * SkillService::ResolveSkill(int id)
{
	for (size_t i = 0; i < _skills.size(); i++)
	{
		if (_skills[i] && _skills[i]->_id == id)
			return _skills[i];
	}
	return nullptr;
}

void SkillService::ResolveSkillSet(std::vector<int>& ids, std::vector<Skill*>& skillSet)
{
	for (size_t i = 0; i < ids.size(); i++)
	{
		Skill* k = ResolveSkill(ids[i]);
		if (k)
		{
			skillSet.push_back(k);
		}
	}
}

void SkillService::SendSkillList(Client * caller, bool broadcast)
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;

	Stream data = Stream();
	data.WriteInt16(0);
	data.WriteInt16(S_SKILL_LIST);
	data.WriteInt32(p->_skillList.size());
	short next = data.NextPos();

	for (size_t i = 0; i < p->_skillList.size(); i++)
	{
		data.WritePos(next);
		data.WriteInt16(data._pos);
		next = data.NextPos();
		
		data.WriteInt32(p->_skillList[i]->_id); // skillId
		data.WriteInt16(1); //unk
	}
	data.WritePos(0);

	if (broadcast)
		BroadcastSystem::Broadcast(caller, &data, ME, 0);
	else
		caller->Send(&data);

}

void SkillService::SendSkillLearnList(Client * caller, bool broadcast)
{
	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;

	switch (p->_playerInfo->pClass)
	{
	case WARRIOR:
	{
		SendWarriorLearnSkillList(caller, broadcast);
	}break;

	default:
		break;
	}
}

const bool SkillService::LearnNewSkill(Client * caller, int skillId)
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return false;
	Skill * sk = ResolveSkill(skillId);
	if (!sk)
		return false;

	for (size_t i = 0; i < _warriorLearnSkillList.size(); i++)
	{
		if (_warriorLearnSkillList[i].skillId == skillId)
		{
			
			p->_inventory->TakeGold(_warriorLearnSkillList[i].cost);

			for (size_t j = 0; j < p->_skillList.size(); j++)
			{
				if (p->_skillList[j]->_baseId == GetSkillBaseId(skillId))
				{
					p->_skillList.erase(p->_skillList.begin() + j);
					j--;
				}
			}
			p->_skillList.push_back(sk);
			return true;
		}
	}
	return false;
}

void SkillService::GetStarterSkillList(Player * caller)
{
}

const int SkillService::GetSkillBaseId(int skillId)
{
	return (skillId / 1000) * 1000 + 100;
}

void SkillService::SendWarriorLearnSkillList(Client * caller, bool broadcast)
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;

	Stream s = Stream();

	s.WriteInt16(0);
	s.WriteInt16(S_SKILL_LEARN_LIST);

	s.WriteInt32(_warriorLearnSkillList.size());
	short next = s.NextPos();


	for (size_t i = 0; i < _warriorLearnSkillList.size(); i++)
	{
		s.WritePos(next);
		s.WriteInt16(s._pos);
		next = s.NextPos();

		s.WriteInt16(_warriorLearnSkillList[i].unk1);
		s.WriteInt16(_warriorLearnSkillList[i].unk2);
		s.WriteInt16(_warriorLearnSkillList[i].unk3);
		s.WriteInt16(_warriorLearnSkillList[i].unk4);

		s.WriteInt32(_warriorLearnSkillList[i].skillId);

		s.WriteByte(p->_inventory->_gold >= _warriorLearnSkillList[i].cost ? 1 : 0); //can buy?
		s.WriteInt32(_warriorLearnSkillList[i].cost);
		s.WriteInt32(_warriorLearnSkillList[i].level);
		s.WriteByte(p->_stats._level >= _warriorLearnSkillList[i].level ? 1 : 0); //can learn ???
	}

	s.WritePos(0);


	if (broadcast)
		BroadcastSystem::Broadcast(caller, &s, ME, 0);
	else
		caller->Send(&s);
}

std::vector<Skill*> SkillService::_skills;
std::vector<SkillService::LearnSkill> SkillService::_warriorLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_berserkerLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_slayerLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_archerLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_gunnerLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_brawlerLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_mysticLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_priestLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_sorcererLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_lancerLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_reaperLearnSkillList;
std::vector<SkillService::LearnSkill> SkillService::_ninjaLearnSkillList;

SkillService::LearnSkill::LearnSkill(int i1, int i2, int i6, int i7, int i3, int i4, int i5)
{
	unk1 = i1;
	unk2 = i2;
	unk3 = i6;
	unk4 = i7;
	skillId = i3;
	cost = i4;
	level = i5;
}
