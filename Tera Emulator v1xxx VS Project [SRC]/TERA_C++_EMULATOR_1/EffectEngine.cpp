#include "EffectEngine.h"



EffectEngine::EffectEngine(Server * server, Client * client)
{
	_server = server;
	_owner = client;
}

EffectEngine::~EffectEngine()
{
}

const bool EffectEngine::Load()
{
	_abnormals.insert(std::pair<AbnormalFunc, int>(AB_RegenHealtghTest, 1));

	_passivities.insert(std::pair<PassiveFunc, int>(PS_IncreaseAttackModifierTest, -1));
	return true;
}

const bool EffectEngine::Initialize()
{
	if (!_server || !_owner)
		return false;

	return true;
}

void EffectEngine::Action(ServerTimer::ServerTime* time)
{

}

void EffectEngine::AB_RegenHealtghTest(IAbnormality * ab, Client * owner, Server * server)
{
}

void EffectEngine::PS_IncreaseAttackModifierTest(Passivity * ps, Client * owner, Server * server)
{
}


std::map<AbnormalFunc, int> EffectEngine::_abnormals;
std::map<PassiveFunc, int> EffectEngine::_passivities;