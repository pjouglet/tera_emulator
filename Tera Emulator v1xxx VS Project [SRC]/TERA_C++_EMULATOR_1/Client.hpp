#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <fstream>
#include <random>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <mutex>
#include <concurrent_queue.h>

#include "socket.hpp"
#include "TeraPacket.hpp"
#include "Entity.h"

class Account;
class Player;
class Server;
class Stream;
class Area;
class EffectEngine; enum OpCode;
class Client : public Entity
{
	friend class WorldObject;
	friend class Creature;
	friend class PlayerService;
	friend class WorldSystem;
	friend class BroadcastSystem;
	friend class SendPacket;
	friend class Server;
public:
	Client(SOCKET socket, sockaddr_in sockData, Server* server);
	~Client();

	void Close();
	const bool Send(byte* data, unsigned int length);
	const bool Send(Stream * s);
	const bool IsVisibleClient(Client * c);
	void RemoveVisibleClient(Client * c);
	void AddVisibleClient(Client* c);
	void ClearVisibleClients();
	void Disappear();
	const bool HasSelectedPlayer();
	void Dump(byte* data, unsigned int length, bool recv);
	void SendToVisibleClients(Stream* data);
	
	void LoginClient(Account *  account);
	void LogoutClient();
	const bool IsLoggedIn();
	Account* GetAccount();
	Player *GetSelectedPlayer();
private:
	static void Run(Client * instance, Server* server);
	static void Recevie(Client * instance);
	static const bool ProcessData(Client * instance, Stream * processStream,OpCode opCode);
	static void Action(Client* instance, Server * server);

private:
	Account* _account;
	bool 
		_playerLocked,
		_workRunnging,
		_mainRunnging,
		_loggedIn,
		_mainRun,
		_opened;

	std::thread _clientThread;
	std::thread _workThread;
	std::mutex _sendMutex;
	std::mutex _recvMutex;
	std::mutex _visibleListMutex;
	std::condition_variable _canWork;



	Crypt::Session *_session;
	EffectEngine * _effectEngine;

	std::fstream _file;
	SOCKET _socket;
	sockaddr_in _sockData;

	int _connectionId;

	std::vector<Client*> _visibleClients;
};





#endif