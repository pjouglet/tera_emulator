#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mutex>

#include "socket.hpp"

#include "Listener.hpp"
#include "Client.hpp"

#include "mysql\MySqlDriver.h"

#define SERVER_ID  4012
#define SERVER_CLIENTS_DISCONNECTION_TIMEOUT 1000
#define SERVER_NAME "Planet Gazah"

class Server
{
	friend int main();
private:
	struct Config
	{
		std::string ip;
		unsigned int port;
		unsigned int maxClients;
		bool isValid;
		bool autoStart;
		bool debugInfo;

		std::string mysqlHostAddress;
		std::string mysqlUsername;
		std::string mysqlPassword;
		std::string database;
	};

	friend class Listener;
	friend class Client;
public:
	Server();
	~Server();

public:
	const bool Initialize();

	const bool Run();
	const bool Shutdown();

private:
	void NewConnection(Client* connection);
	void RemoveConnection(Client* connection);
	unsigned int _connectedClients;
private:
	Config LoadConfigFromFile(const char* file);
private:
	bool _started;
	WSADATA _wsaData;
	MySqlDriver * _mysqlDriver;
	Listener * _listener;
	
	std::vector<Client*> _clients;
	std::mutex _serverMutex;

public:
	static  Config _serverConfig;

};

#endif
