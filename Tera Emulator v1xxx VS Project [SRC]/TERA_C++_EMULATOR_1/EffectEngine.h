#pragma once
#include <map>
#include <vector>
#include "ServerTimer.h"


class IAbnormality; class Passivity; class Inventory; class Client; class Server; class CreatureStats;
typedef void(*AbnormalFunc)(IAbnormality* ab, Client* owner, Server* server);
typedef void(*PassiveFunc)(Passivity* ps, Client* owner, Server* server);


class EffectEngine
{
public:
	EffectEngine(Server * server, Client * client);
	~EffectEngine();
	static const bool Load();

	const bool Initialize();

	void Action(ServerTimer::ServerTime* time);
private:


private:
	static std::map<AbnormalFunc, int> _abnormals;
	static std::map<PassiveFunc, int> _passivities;
#pragma region ABNORMALS
	static void AB_RegenHealtghTest(IAbnormality* ab, Client* owner, Server* server);
#pragma endregion
#pragma region PASSIVITIES
	static void PS_IncreaseAttackModifierTest(Passivity* ps, Client* owner, Server* server);
#pragma endregion

	std::vector<IAbnormality*> _abs;
	std::vector<Passivity*> _pas;

	Server* _server;
	Client * _owner;
};

