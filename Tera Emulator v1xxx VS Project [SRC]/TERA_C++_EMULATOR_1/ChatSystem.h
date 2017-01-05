#pragma once

#include <mutex>
#include <vector>

class Client; class Player; class Account;
class ChatSystem
{
public:
	ChatSystem();
	~ChatSystem();


	static void SendChatSettings(Client* c);
};

