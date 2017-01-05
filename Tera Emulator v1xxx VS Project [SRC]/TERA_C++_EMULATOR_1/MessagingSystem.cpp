#include "MessagingSystem.h"
#include "Client.hpp"
#include "OpCodesEnum.h"
#include "Stream.h"
#include "BroadcastService.h"

MessagingSystem::MessagingSystem()
{
}


MessagingSystem::~MessagingSystem()
{
}

void MessagingSystem::SendSystemMessage(Client * client, std::string message)
{
	Stream s = Stream();

	s.WriteInt16(0);
	s.WriteInt16(S_SYSTEM_MESSAGE);
	s.WriteInt16(6);
	s.WriteString(message);

	s.WritePos(0);
	BroadcastSystem::Broadcast(client, &s, ME, 0);
}

void MessagingSystem::SendCustomSystemMessage(Client * client, std::string message)
{
}

