#include "CreatureStats.h"


float CreatureStats::GetImpact()
{
	return _impactFactor + _impact + _impactModifier;
}

float CreatureStats::GetBalance()
{
	return _balance + _balanceFactor + _balanceModifier;
}

float CreatureStats::GetCritResist()
{
	return _critResist + _additionalCritResist;
}

float CreatureStats::GetCritChance()
{
	return _critChance + _additionalCitChance;
}

float CreatureStats::GetWeakeningResistance()
{
	return _weakeningResistance + _additionalWeakeningResistance;
}

float CreatureStats::GetPeriodicDamageResistance()
{
	return _periodicDamageResistance + _additionalPeriodicDamageResistance;
}

float CreatureStats::GetStunResistance()
{
	return _stunResistance + _additionalStunResistance;
}

int CreatureStats::GetStaminaHp()
{
	return 0;
}

int CreatureStats::GetStaminaMp()
{
	return 0;
}

int CreatureStats::GetAttackSpeed()
{
	return _attackSpeed + _additionalAttackSpeed;
}

int CreatureStats::GetMovementSpeed()
{
	return _movementSpeed + _additionalMovementSpeed;
}

int CreatureStats::GetPower()
{
	return _power;
}

int CreatureStats::GetEndurance()
{
	return _endurance + _additionalEndureance;
}

int CreatureStats::GetCritPower()
{
	return _critPower + _additionalCirtPower;
}

int CreatureStats::GetHP()
{
	return _currentHp;
}

int CreatureStats::GetMP()
{
	return _currentMp;
}

int CreatureStats::GetAttack()
{
	return GetPower() + _attackModifier + _additionalAttack;
}

int CreatureStats::GetDefense()
{
	return GetEndurance() + _defenseModifier + _additionalDefense;
}

int CreatureStats::GetMpRegen()
{

	return _naturalMpRegen;
}

int CreatureStats::GetHpRegen()
{
	return _naturalHpRegen;
}

int CreatureStats::GetComabtMpRegen()
{
	return _combatMpRegen;
}

int CreatureStats::GetComabtHpRegen()
{
	return _combatHpRegen;
}

void CreatureStats::SetMaxHpAndMp()
{
	_currentHp = _maxHp + GetStaminaHp();
	_currentMp = _maxMp + GetStaminaMp();
}

void CreatureStats::Refresh()
{
	//std::lock_guard<std::mutex> _lock(_statsLock);


	//todo
}

void CreatureStats::Lock()
{
	_statsLock.lock();
}

void CreatureStats::Unlock()
{
	_statsLock.unlock();
}

int CreatureStats::GetLevel()
{
	return _level;
}
