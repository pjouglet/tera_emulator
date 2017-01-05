#include "Listener.hpp"
#include "Server.hpp"


Listener::Listener(const char* ip, unsigned int port, unsigned int maxClients) :_port(port), _maxClients(maxClients)
{
	_ip = ip;
	_listen = false;
	_initialized = false;
	_listening = false;
}


Listener::~Listener()
{
	Stop();
}

const bool Listener::Initialize()
{

	_listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_listeningSocket == SOCKET_ERROR)
		return false;


	sockaddr_in sockData;
	sockData.sin_family = AF_INET;
	sockData.sin_addr.s_addr = inet_addr(_ip);
	sockData.sin_port = htons(_port);


	if (bind(_listeningSocket, (const sockaddr*)&sockData, sizeof sockaddr) != 0)
	{
		std::cout << "listener bind fail\n";
		closesocket(_listeningSocket);
		return false;
	}

	if (listen(_listeningSocket, SOMAXCONN) != 0)
	{
		std::cout << "listen  fail\n";
		closesocket(_listeningSocket);
		return false;
	}


	_initialized = true;
	return true;
}



const bool Listener::Start(Server* instance)
{
	if (_listen || _listening)
		return false;

	if (!IsValid())
	{
		if (!Initialize())
			return false;
	}

	_listen = true;
	_listenerThread = std::thread(Listen, this, instance);
	_listenerThread.detach();

	return true;
}

const bool Listener::Stop()
{
	if (!_listening)
		return false;

	_listen = false;
	shutdown(_listeningSocket, SD_BOTH);
	closesocket(_listeningSocket);

	int times = 0;
	while (_listening)
	{
		times++;
		if (times >= 500)
			break;
		continue;
	}
	
		
	

	return true;
}

const bool Listener::IsValid()
{
	return _initialized;
}

void Listener::Listen(Listener* linstance, Server* server)
{
	linstance->_listening = true;
	int length = sizeof(sockaddr);
	while (linstance->_listen)
	{
		SOCKET newConnection;
		sockaddr_in connectionData;

		newConnection = accept(linstance->_listeningSocket, (sockaddr*)&connectionData, &length);
		if (newConnection != INVALID_SOCKET)
		{
			Client* con = new Client(newConnection, connectionData, server);
			server->NewConnection(con);
		}
	}
	linstance->_listening = false;
	linstance->_initialized = false;
}
