#ifndef ABNORMALITY_EFFECT_H
#define ABNORMALITY_EFFECT_H
class AbnormalityEffect
{
public:
	AbnormalityEffect();

	float 
		_value;

	int _type,
		_tickInterval,
		_overlayEffectId,
		_isEnemyCheck,
		_appearEffectId,
		_attackEffectId,
		_damageEffectId,
		_dissappearEffectId,
		_method;
};

#endif