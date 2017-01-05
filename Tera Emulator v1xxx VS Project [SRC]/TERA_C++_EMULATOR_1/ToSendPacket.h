#pragma once


enum BC_TYPE :int
{
	ME = 0,
	VISIBLE_CLIENTS,
	ME_VISIBLE_CLIENTS,
	AREA,
	ENEMYE,
	PARTY,
	RAID,
	CHAT,

	DROP_SPAWN,
	DROP_DESPAWN,

	MOB_SPAWN,
	MOB_DESPAWN,
	NPC_SPAWM,
	NPC_DESPAWN,

	COLLECTION_SPAWN,
	COLLECTION_DESPAWN,

	PLAYER_SPAWN,
	PLAYER_DESPAWN
};



class Stream; class Client; 
class ToSendPacket {
	friend class BroadcastSystem;

	Stream * _data;
	Client* _callerClient;
	
	BC_TYPE _bcType;
	bool _ordered;

	void** _args;
	ToSendPacket(Client* caller, Stream * data, BC_TYPE type ,bool ordered, void** args);
	~ToSendPacket();
};