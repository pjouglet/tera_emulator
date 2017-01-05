#include "RMovePlayer.h"
#include "Server.hpp"

RMovePlayer::RMovePlayer() : SendPacket(C_PLAYER_LOCATION)
{
}

void RMovePlayer::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	Player * p = caller->GetSelectedPlayer();
	
	float x = stream->ReadFloat();
	float y = stream->ReadFloat();
	float z = stream->ReadFloat();
	int w = stream->ReadInt32();
	float x2 = stream->ReadFloat();
	float y2 = stream->ReadFloat();
	float z2 = stream->ReadFloat();
	int type = stream->ReadInt32();
	short speed = stream->ReadInt16();
	byte unk = stream->ReadByte();
	int time = stream->ReadInt32();


	p->_position->_X = x2;
	p->_position->_Y = y2;
	p->_position->_Z = z2;
	p->_position->_heading = w;

	stream->Clear();
	stream->WriteInt16(0);
	stream->WriteInt16(S_USER_LOCATION);

	stream->WriteInt32(p->_entityId);
	stream->WriteInt32(p->_subId);

	stream->WriteFloat(x);
	stream->WriteFloat(y);
	stream->WriteFloat(z);
	stream->WriteInt32(w);
	stream->WriteInt16(p->_stats.GetMovementSpeed());
	stream->WriteFloat(x2);
	stream->WriteFloat(y2);
	stream->WriteFloat(z2);
	stream->WriteInt32(type);
	stream->WriteByte(1);
	stream->WritePos(0);

	//BroadcastSystem::Broadcast(caller, stream, MOVEMENT_BROADCAST, 0);
	caller->SendToVisibleClients(stream);
	//WorldSystem::ProcessMovement(caller, x, y, z, w);
}

