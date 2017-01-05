#pragma once

enum CreatureReaction : int
{
	Friendly = 1

};

enum CreatureActionState : int
{
	STATE_NONCOMBAT = 0,
	STATE_COMBAT = 1,
};

enum CreatureStatus : int
{
	Dead = 0,
	Alive = 1,
	Ghost = 3 //admin only
};