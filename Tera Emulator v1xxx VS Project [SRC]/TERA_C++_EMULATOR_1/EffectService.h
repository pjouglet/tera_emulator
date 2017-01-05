#ifndef EFFECT_SERVICE_H
#define EFFECT_SERVICE_H

#include <vector>
#include <mutex>
#include <fstream>
#include "AbnormalityEffect.h"

class EffectService
{
public:
	static const bool LoadEffects(const char * file = "data/effects.bin");

	

	static void Release();
	static unsigned int GetCount();
private:
	static std::vector<AbnormalityEffect *> _effects;
};

#endif