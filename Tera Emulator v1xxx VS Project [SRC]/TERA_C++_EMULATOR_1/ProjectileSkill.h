#ifndef PROJECTILE_SKILL_H
#define PROJECTILE_SKILL_H


class ProjectileSkill
{
public:
	ProjectileSkill();
	~ProjectileSkill();


public:
	int detachAngle;
	int detachDistance;
	int detachHeight;
	float flyingDistance;
	int id;
	int shootAngle;
};

#endif