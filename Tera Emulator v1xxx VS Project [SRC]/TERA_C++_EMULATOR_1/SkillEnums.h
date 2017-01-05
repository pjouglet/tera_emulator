#pragma once
enum PushTarget :  unsigned char
{
	Pass = 0,
	Stop = 1,
	Push = 2
};

enum SkillType : short
{
	Normal = 0,
	Instance = 1,
	MovingSkill = 2,
	MovingCharge = 3,
	Projectile = 4,
	Evade = 5,
	Combo = 6,
	ComboInstance = 7,
	NoTimeline = 8,
	Stand = 9,
	Switch = 10,
	Defence = 11,
	Firewood = 12,
	Summon = 13,
	Gamble = 14,
	Charm = 15,
	Rebirth = 16,
	Eventseed = 17,
	CommanderNormal = 18,
	CommanderScan = 19,
	Mount = 20,
	Drain = 21,
	DrainBack = 22,
	Userslug = 23,
	ShortTel = 24,
	Capture = 25,
	Connect = 26,
	Dash = 27,
	CatchBack = 28,
	ChaseEffect = 29
};




