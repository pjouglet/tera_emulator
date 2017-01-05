#ifndef PLAYERENUMS_H
#define PLAYERENUMS_H


enum PlayerClass : short //TODO: add values
{
	WARRIOR = 0,
	LANCER = 1,
	SLAYER = 2,
	BERSERKER = 3,
	SORCERER = 4,
	ARCHER = 5,
	PRIEST = 6,
	MYSTIC = 7,
	REAPER = 8,
	ENGINEER = 9, //gunner
	FIGHTER = 10, //brawler
	ASSASSIN = 11 //ninja
};

enum PlayerGender :short
{
	MALE = 0,
	FEMALE = 1
};

enum PlayerRace : short //TODO: add values
{
	HUMAN = 0,
	HIGHELF = 1,
	AMAN = 2,
	CASTANIC = 3,
	ELIN = 4,
	POPORI = 5,
	BARAKA = 6,

};

enum MobSize : int
{
	Small		= 1,
	Medium			= 2,
	Large			= 3,
	All				= 4,
	TPlayer		= 5
};

enum PlayerMoveType : int
{
	P_MOVE_NORMAL = 0,
	P_JUMP_START = 1,
	P_JUMP_END = 2
};
#endif // !PLAYERENUMS_H
