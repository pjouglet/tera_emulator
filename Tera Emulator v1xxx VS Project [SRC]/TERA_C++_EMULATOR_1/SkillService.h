#ifndef SKILLSERVICE_H
#define SKILLSERVICE_H

#include <vector>
#include <mutex>

class Client; class Account; class Player; class Skill;
class SkillService
{
public:
	struct LearnSkill
	{
		short unk1;
		short unk2;
		short unk3;
		short unk4;
		int skillId;
		int cost; //?
		int level; //?

		LearnSkill(int i1, int i2, int i6, int i7, int i3, int i4, int i5);
	};

	static void Release();

	static const bool LoadSkills(const char* dir);
	static const unsigned int GetCount();

	static Skill* ResolveSkill(int id);
	static void ResolveSkillSet(std::vector<int>& ids, std::vector<Skill*> & skillSet);

	static void SendSkillList(Client * caller, bool broadcast = true);
	static void SendSkillLearnList(Client* caller, bool broadcast = true);
	static const bool LearnNewSkill(Client* caller, int skillId);
	static void GetStarterSkillList(Player* caller);


	static const int GetSkillBaseId(int skillId);
private:
	static void SendWarriorLearnSkillList(Client * caller, bool broadcast = true);

	static std::vector<Skill*> _skills;
	static std::vector<LearnSkill> _warriorLearnSkillList;
	static std::vector<LearnSkill> _berserkerLearnSkillList;
	static std::vector<LearnSkill> _slayerLearnSkillList;
	static std::vector<LearnSkill> _archerLearnSkillList;
	static std::vector<LearnSkill> _gunnerLearnSkillList;
	static std::vector<LearnSkill> _brawlerLearnSkillList;
	static std::vector<LearnSkill> _mysticLearnSkillList;
	static std::vector<LearnSkill> _priestLearnSkillList;
	static std::vector<LearnSkill> _sorcererLearnSkillList;
	static std::vector<LearnSkill> _lancerLearnSkillList;
	static std::vector<LearnSkill> _reaperLearnSkillList;
	static std::vector<LearnSkill> _ninjaLearnSkillList;
};

#endif
