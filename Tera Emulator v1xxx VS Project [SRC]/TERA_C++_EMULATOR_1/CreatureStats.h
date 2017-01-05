#pragma once
#include "PlayerEnums.h"
#include <string>
#include <vector>
#include <mutex>
#include "CreatureEnum.h"

#define STAMINA_GOOD_HP 2000
#define STAMINA_GOOD_MP 120


struct CreatureStats
{
	friend class Creature;
	friend class RChat;
	friend class StatsService;
	friend class PlayerService;
public:
	CreatureReaction reaction;
	CreatureStatus status;

	int _level;
private:
	std::mutex _statsLock;

	CreatureActionState _actionState;

	//HpMp
	int _currentHp;
	int _maxHp;
	int _staminaHp;
	int _additionalHp;
	
	bool _hasSpecial;
	int _currentSpecial;
	int _aditionalSpecial;
	int _maxSpecial;
	int _specialRegenRate;
	int _naturalSpecialRegenInterval;
	int _combatSpecialRegenInterval;

	int _currentMp;
	int _maxMp;
	int _staminaMp;
	int _additionalMp;
		
	int _infamy;

	//combat
	int _attack;
	int _additionalAttack;

	int _defense;
	int _additionalDefense;

	int _impact;
	int _additionalImapct;

	int _balance;
	int _additionalBalance;

	float _critChance;
	float _additionalCitChance;

	float _critResist;
	float _additionalCritResist;

	int _critPower;
	int _additionalCirtPower;

	//stats
	int _power;
	int _additionalPower;

	int _endurance;
	int _additionalEndureance;

	float _impactFactor;
	float _additionalImpactFactor;

	float _balanceFactor;
	float _additionalBalanceFactor;

	int _attackSpeed;
	int _additionalAttackSpeed;

	int _movementSpeed;
	int _additionalMovementSpeed;
		
	//resistance
	float _weakeningResistance;
	float _additionalWeakeningResistance;

	float _periodicDamageResistance;
	float _additionalPeriodicDamageResistance;

	float _stunResistance;
	float _additionalStunResistance;
		
	//regen
	int _naturalMpRegen;
	int _additioanlMpRegen;

	int _naturalHpRegen;
	int _additioanlHpRegen;

	int _currentStamina;
	int _maxStamina;
	int _additionalStamina;

	int _combatMpRegen;
	int _additioanlCombatMpRegen;

	int _combatHpRegen;
	int _additioanlCombatHpRegen;


	int _attackModifier;
	int _defenseModifier;
	int _impactModifier;
	int _balanceModifier;

public:
	int GetHP();
	int GetMP();
	int GetAttack();
	int GetDefense();
	float GetImpact();
	float GetBalance();
	int GetAttackSpeed();
	int GetMovementSpeed();
	int GetPower();
	int GetEndurance();
	int GetCritPower();
	float GetCritResist();
	float GetCritChance();
	float GetWeakeningResistance();
	float GetPeriodicDamageResistance();
	float GetStunResistance();
	int GetStaminaHp();
	int GetStaminaMp();

	int GetMpRegen();
	int GetHpRegen();

	int GetComabtMpRegen();
	int GetComabtHpRegen();

	void SetMaxHpAndMp();

	void Refresh();

	void Lock();
	void Unlock();

	int GetLevel();
};

