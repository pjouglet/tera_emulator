#include "UnionSystem.h"

void UnionSystem::SendElectionState(Client * client)
{
	Stream s = Stream();

	s.WriteInt16(28);
	s.WriteInt16(S_CURRENT_ELECTION_STATE);

	s.WriteInt32(0);
	s.WriteInt32(5);
	s.WriteInt32(0);

	s.WriteInt16(0);

	s.WriteByte(5);
	s.WriteByte(61);
	s.WriteByte(228);
	s.WriteByte(81);

	s.WriteInt32(0);
	s.WritePos(0);
	client->Send(s._raw, s._size);
}
