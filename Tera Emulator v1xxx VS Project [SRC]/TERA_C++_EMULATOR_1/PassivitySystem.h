#pragma once
#include <map>

class Passivity; class CreatureBase;
typedef void(*PassiveFunction)(CreatureBase*);
class PassivitySystem {
public:
	static const bool Initialize();
	PassiveFunction operator [] (int pid);

private:
	static std::map<int, PassiveFunction> _passivitiesResolutions;

};

namespace PFUN
{
	void IncreaseDamage(CreatureBase *c);
}




