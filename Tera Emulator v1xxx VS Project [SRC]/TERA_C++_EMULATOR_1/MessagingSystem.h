#pragma once
#include <string>

class Client;
class MessagingSystem
{
public:
	MessagingSystem();
	~MessagingSystem();


	static void SendSystemMessage(Client * client, std::string message);
	static void SendCustomSystemMessage(Client * client, std::string message);
};

