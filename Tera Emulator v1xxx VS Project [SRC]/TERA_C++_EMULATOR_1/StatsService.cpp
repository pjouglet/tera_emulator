#include "StatsService.h"
#include "Creature.h"
#include "Player.hpp"
#include "Client.hpp"
#include "Account.hpp"
#include "CreatureStats.h"
#include "CreatureEnum.h"
#include "Stream.h"
#include "OpCodesEnum.h"
#include "Inventory.h"
#include "BroadcastService.h"

CreatureStats * StatsService::GetCreatureBaseStats(Creature * creaturebool )
{
	CreatureStats * stats = new CreatureStats();
	return stats;
}

void StatsService::GetPlayerStartStats(Player* p)
{
	if (!p)
		return;
	PlayerClass pclass = p->_playerInfo->pClass;

	p->_stats._maxStamina = 120;
	p->_stats._currentStamina = 120;

	p->_stats._currentHp = 100;
	p->_stats._additionalMovementSpeed = 80;
	p->_stats._actionState = STATE_NONCOMBAT;

	switch (pclass)
	{
	case WARRIOR:
		p->_stats._power = 46;
		p->_stats._endurance = 78;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 120;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 41;
		p->_stats._periodicDamageResistance = 41;
		p->_stats._stunResistance = 41;

		p->_stats._maxHp = 903;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 5;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 5;

		p->_stats._hasSpecial = true;
		p->_stats._maxSpecial = 4000;
		p->_stats._currentSpecial = 4000;
		p->_stats._specialRegenRate = 500;
		p->_stats._combatSpecialRegenInterval = 6000; //ms
		p->_stats._naturalSpecialRegenInterval = 1000;//ms

		break;
	case LANCER:
		p->_stats._power = 49;
		p->_stats._endurance = 29;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 105;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 25;
		p->_stats._periodicDamageResistance = 40;
		p->_stats._stunResistance = 40;

		p->_stats._maxHp = 689;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 5;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 5;

		p->_stats._hasSpecial = true;
		p->_stats._maxSpecial = 4000;
		p->_stats._currentSpecial = 4000;
		p->_stats._specialRegenRate = 500;
		p->_stats._combatSpecialRegenInterval = 6000; //ms
		p->_stats._naturalSpecialRegenInterval = 1000;//ms
		break;
	case SLAYER:
		p->_stats._power = 71;
		p->_stats._endurance = 21;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 120;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 20;
		p->_stats._periodicDamageResistance = 35;
		p->_stats._stunResistance = 15;

		p->_stats._maxHp = 648;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = -20;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 10;

		break;
	case BERSERKER:
		p->_stats._power = 78;
		p->_stats._endurance = 26;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 105;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 20;
		p->_stats._periodicDamageResistance = 35;
		p->_stats._stunResistance = 15;

		p->_stats._maxHp = 650;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = -20;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 10;
		break;
	case SORCERER:
		p->_stats._power = 64;
		p->_stats._endurance = 12;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 110;
		p->_stats._critChance = 25;
		p->_stats._critResist = 30;
		p->_stats._weakeningResistance = 35;
		p->_stats._periodicDamageResistance = 20;
		p->_stats._stunResistance = 15;

		p->_stats._maxHp = 518;
		p->_stats._maxMp = 200;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 10;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 10;
		break;
	case ARCHER:
		p->_stats._power = 81;
		p->_stats._endurance = 27;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 110;
		p->_stats._critChance = 25;
		p->_stats._critResist = 30;
		p->_stats._weakeningResistance = 20;
		p->_stats._periodicDamageResistance = 35;
		p->_stats._stunResistance = 15;

		p->_stats._maxHp = 598;
		p->_stats._maxMp = 50;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 5;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 5;
		break;
	case PRIEST:
		p->_stats._power = 32;
		p->_stats._endurance = 13;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 110;
		p->_stats._critChance = 20;
		p->_stats._critResist = 25;
		p->_stats._weakeningResistance = 41;
		p->_stats._periodicDamageResistance = 41;
		p->_stats._stunResistance = 41;

		p->_stats._maxHp = 527;
		p->_stats._maxMp = 250;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 10;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen =10;
		break;
	case MYSTIC:
		p->_stats._power = 35;
		p->_stats._endurance = 73;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 110;
		p->_stats._critChance = 20;
		p->_stats._critResist = 25;
		p->_stats._weakeningResistance = 41;
		p->_stats._periodicDamageResistance = 41;
		p->_stats._stunResistance = 41;

		p->_stats._maxHp = 580;
		p->_stats._maxMp = 200;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 10;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 10;
		break;
	case REAPER:
		p->_stats._power = 55;
		p->_stats._endurance = 38;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 105;
		p->_stats._movementSpeed = 110;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 41;
		p->_stats._periodicDamageResistance = 41;
		p->_stats._stunResistance = 41;

		p->_stats._maxHp = 903;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 5;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 5;
		break;
	case ENGINEER:
		p->_stats._power = 46;
		p->_stats._endurance = 78;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 120;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 41;
		p->_stats._periodicDamageResistance = 41;
		p->_stats._stunResistance = 41;

		p->_stats._maxHp = 903;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 5;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 5;

		p->_stats._hasSpecial = true;
		p->_stats._maxSpecial = 4000;
		p->_stats._currentSpecial = 4000;
		p->_stats._specialRegenRate = 500;
		p->_stats._combatSpecialRegenInterval = 6000; //ms
		p->_stats._naturalSpecialRegenInterval = 1000;//ms
		break;
	case FIGHTER:
		p->_stats._power = 46;
		p->_stats._endurance = 78;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 120;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 41;
		p->_stats._periodicDamageResistance = 41;
		p->_stats._stunResistance = 41;

		p->_stats._maxHp = 903;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 5;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 5;

		p->_stats._hasSpecial = true;
		p->_stats._maxSpecial = 4000;
		p->_stats._currentSpecial = 4000;
		p->_stats._specialRegenRate = 500;
		p->_stats._combatSpecialRegenInterval = 6000; //ms
		p->_stats._naturalSpecialRegenInterval = 1000;//ms
		break;
	case ASSASSIN:
		p->_stats._power = 46;
		p->_stats._endurance = 78;
		p->_stats._impactFactor = 40;
		p->_stats._balanceFactor = 60;
		p->_stats._attackSpeed = 120;
		p->_stats._movementSpeed = 120;
		p->_stats._critChance = 52.0f;
		p->_stats._critResist = 74.0f;
		p->_stats._weakeningResistance = 41;
		p->_stats._periodicDamageResistance = 41;
		p->_stats._stunResistance = 41;

		p->_stats._maxHp = 903;
		p->_stats._maxMp = 100;
		p->_stats._naturalHpRegen = 0;
		p->_stats._naturalMpRegen = 5;
		p->_stats._combatHpRegen = 0;
		p->_stats._combatMpRegen = 5;

		p->_stats._hasSpecial = true;
		p->_stats._maxSpecial = 4000;
		p->_stats._currentSpecial = 4000;
		p->_stats._specialRegenRate = 500;
		p->_stats._combatSpecialRegenInterval = 6000; //ms
		p->_stats._naturalSpecialRegenInterval = 1000;//ms
		break;
	default:
		break;
	}

	p->_stats.Refresh();
}

void StatsService::SendPlayerStats(Client * c, bool broadcast)
 {
	Player * p = c->GetSelectedPlayer();
	if (!p)
		return;

	CreatureStats& stats = p->_stats;

	Stream  *data = new Stream();
	data->WriteInt16(0);
	data->WriteInt16(S_PLAYER_STAT_UPDATE); 

	data->WriteInt32(stats._currentHp); //ACTUAL hp
	data->WriteInt32(stats._currentMp); //ACTUAL mp
	data->WriteInt32(0);
	data->WriteInt32(stats._maxHp);
	data->WriteInt32(stats._maxMp);


	data->WriteInt32(stats._power); //base power	[character power + items base power]
	data->WriteInt32(stats._endurance); //base endurance [character endurance + items base endurance]				 
	data->WriteInt32(stats._impactFactor);
	data->WriteInt32(stats._balanceFactor);
	data->WriteInt16(stats._movementSpeed);
	data->WriteInt16(0); //??							
	data->WriteInt16(stats._attackSpeed);
	data->WriteFloat((float)stats._critChance);

	data->WriteFloat((float)stats._critResist);
	data->WriteFloat((float)stats._critPower);

	data->WriteInt32(stats.GetAttack()); 	//base attack range1				
	data->WriteInt32(stats._attack); //base attack range2			

	data->WriteInt32(stats._defense); //defense 1					
	data->WriteInt32(stats._impact);	// impact		
	data->WriteInt32(stats._balance);	//balance		

	data->WriteFloat(stats.GetWeakeningResistance()); //RESISTANCES	weakening
	data->WriteFloat(stats.GetPeriodicDamageResistance()); //RESISTANCES	
	data->WriteFloat(stats.GetStunResistance()); //RESISTANCES	stun

	data->WriteInt32(stats._additionalPower);  //aditional power [from bonuses and effects]			
	data->WriteInt32(stats._additionalEndureance);   //aditional endurance [from bonuses and effects]
	data->WriteInt32(stats._additionalImpactFactor);  //aditional impactFactor
	data->WriteInt32(stats._additionalBalanceFactor);  //aditional balanceFactor
	data->WriteInt32(stats._additionalMovementSpeed);  //aditional movementSpeed
	data->WriteInt32(stats._additionalAttackSpeed);  //aditional attackSpeed
	data->WriteInt32(stats._additionalAttack); //aditional attack range1??
	data->WriteInt32(stats._additionalAttack);	//aditional attack range2??
	data->WriteInt32(stats._additionalImapct); //aditioanl impact ??
	data->WriteInt32(stats._additionalDefense); //aditional defense range1
	data->WriteInt32(stats._additionalDefense); //aditional defense range2

	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);

	data->WriteInt16(0);	 //unk
	data->WriteInt32(stats._level);	 //level
	data->WriteInt16(0);	 //unk

	data->WriteByte(0); //alive / combat ?

	data->WriteInt32(stats._staminaHp);	 //aditioanl stamina hp
	data->WriteInt32(stats._staminaMp );	 //aditioanl stamina mp
	data->WriteInt32(stats._currentStamina);	 //stamina?
	data->WriteInt32(stats._maxStamina);	 //max stamina?

	data->WriteInt32(stats._currentSpecial);	 //RE/WILLPOWER/CHI...CURRENT VALUE
	data->WriteInt32(stats._maxSpecial);	 //RE/WILLPOWER/CHI...VALUE	 1
	data->WriteInt32(stats._aditionalSpecial);	 //RE/WILLPOWER/CHI...VALUE	 2
	data->WriteInt32(stats._infamy);	 //inafmy
	data->WriteInt32(p->_inventory->_itemLevel);	 //inventory item level
	data->WriteInt32(p->_inventory->_profileItemLevel);	 //profile item level
	data->WriteInt32(0);	 //unk
	data->WriteInt32(0);	 //unk
	data->WriteInt32(0);	 //unk
	data->WriteInt32(0);	 //unk
	data->WriteInt32(0);	 //unk

	data->WriteFloat(102.04);
	data->WriteFloat(0);	 //unk
	data->WriteFloat(1.0);	 //unk
	data->WritePos(0);

	if (broadcast)
		BroadcastSystem::Broadcast(c, data, ME, 0);
	else
		c->Send(data);
}

void StatsService::CalculatePlayerStats(Player * p)
{
	if (!p)
		return;

	GetPlayerStartStats(p);
	
	PlayerClass pClass = p->_playerInfo->pClass;

	switch (pClass)
	{
	case WARRIOR:



		break;
	case LANCER:
		break;
	case SLAYER:
		break;
	case BERSERKER:
		break;
	case SORCERER:
		break;
	case ARCHER:
		break;
	case PRIEST:
		break;
	case MYSTIC:
		break;
	case REAPER:
		break;
	case ENGINEER:
		break;
	case FIGHTER:
		break;
	case ASSASSIN:
		break;
	default:
		break;
	}

	p->_stats.Refresh();
	p->_stats.SetMaxHpAndMp();
}
