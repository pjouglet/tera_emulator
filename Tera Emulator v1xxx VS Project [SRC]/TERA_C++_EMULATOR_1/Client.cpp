#include "Client.hpp"
#include "Server.hpp"
#include "Account.hpp"
#include "Player.hpp"
#include "PlayerService.h"
#include "Stream.h"
#include "TeraPacket.hpp"
#include "OpCodesEnum.h"
#include "OpCodes.hpp"
#include "SendPacket.h"
#include "Inventory.h"
#include "ItemEnum.h"
#include "EffectEngine.h"

#define DUMP_TRAFFIC 1

Client::Client(SOCKET socket, sockaddr_in sockData, Server * server) : Entity()
{
	_socket = socket;
	_sockData = sockData;
	_mainRun = _workRunnging = _mainRunnging = false;
	_session = 0;
	_connectionId = -1;
	_effectEngine = new EffectEngine(server, this);

	int val = 1;
	setsockopt(_socket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&val, sizeof val);

	_clientThread = std::thread(Run, this, server);
	_clientThread.detach();
}
Client::~Client()
{
	LogoutClient();
	if (_socket != INVALID_SOCKET && _socket != SOCKET_ERROR)
	{
		Close();
	}
	if (_session)
	{
		delete _session;
		_session = 0;
	}
}

void Client::Close()
{
	if (_mainRun)
		_mainRun = false;
	shutdown(_socket, SD_BOTH);
	closesocket(_socket);
	_socket == INVALID_SOCKET;
}
void Client::Run(Client * instance, Server* server)
{
	if (!instance->_effectEngine->Initialize())
		instance->Close();

	std::cout << "Client connected! ID[" << instance->_entityId << "]\n";
	int read = 0; bool err = true;
	srand(time((time_t)0));
	char
		clientKey1[128],
		clientKey2[128],
		serverKey1[128],
		serverKey2[128];

	char sInit[4];
	memset(sInit, 0, 4);
	sInit[0] = 1;

	memset(clientKey1, 0, 128); memset(clientKey2, 0, 128);
	for (int j = 0; j < 128; j++)
	{
		serverKey1[j] = rand() % 0xff;
		serverKey2[j] = rand() % 0xff;
	}

	read = send(instance->_socket, sInit, 4, 0);
	if (read != 0 && read != -1)
	{
		read = recv(instance->_socket, clientKey1, 128, 0);
		if (read != 0 && read != -1)
		{
			read = send(instance->_socket, serverKey1, 128, 0);
			if (read != 0 && read != -1)
			{
				read = recv(instance->_socket, clientKey2, 128, 0);
				if (read != 0 && read != -1)
				{
					read = send(instance->_socket, serverKey2, 128, 0);
					if (read != 0 && read != -1)
					{
						err = false;
					}
				}
			}
		}
	}

	if (!err)
	{
		instance->_mainRun = true;
		instance->_mainRunnging = true;
		instance->_session = new Crypt::Session((uint8_t*)clientKey1, (uint8_t*)clientKey2, (uint8_t*)serverKey1, (uint8_t*)serverKey2);

		instance->_workThread = std::thread(Action, instance, server);
		instance->_workThread.detach();

		Recevie(instance);
	}

	instance->_mainRun = false;
	int times = 0;
	while (instance->_workRunnging)
	{
		times++;
		Sleep(1);
	}
	Sleep(1);
	std::cout << "::Work thread closed! times[" << times << "]\n";
	instance->_mainRunnging = false;

	PlayerService::UpdateAccountData(instance->_account);
	WorldSystem::ExitWorld(instance);
	instance->LogoutClient();
	instance->Close();
	std::cout << ">Client disconnected! EntityID[" << instance->_entityId << "] err?[" << err << "]\n";
	server->RemoveConnection(instance);
}
void Client::Recevie(Client * instance)
{
	TeraPacket * _packet = new TeraPacket();
	Stream * processStream = nullptr;
	OpCode opCode;
	while (instance->_mainRun)
	{
		if ((processStream = _packet->GetPacket(instance->_socket, instance->_session, opCode)))
		{
			processStream->_pos = 4;
			instance->ProcessData(instance, processStream, opCode);

			delete processStream;
			processStream = nullptr;
		}
		else
			break;
	}

	if (_packet)
	{
		delete _packet;
		_packet = nullptr;
	}
	if (processStream)
	{
		delete processStream;
		processStream = nullptr;
}

}
const bool Client::ProcessData(Client *  instance, Stream * processStream, OpCode opCode)
{
#ifdef DUMP_TRAFFIC
	instance->Dump(processStream->_raw, processStream->_size, true);//logs hex text data to recvDump.txt
	std::cout << ">" << ServerUtils::HexString(processStream->_raw, processStream->_size) << std::endl;
#endif
	const SendPacket const* toSend = nullptr;
	if ((toSend = OpCodes::Get(opCode)))
		toSend->Process(opCode, processStream, instance);
	else
		std::cout << "No resolution was found for Client OpCode[" << opCode << "] OpCodes Resolutions need to be updated\n";

	return true;
}

void Client::Action(Client * instance, Server * server)
{
	ServerTimer::ServerTime sTime = ServerTimer::ServerTime(0.0f, 0.0f);
	float frequencySeconds = 0.0f;

	LARGE_INTEGER i;
	LONGLONG start;
	QueryPerformanceFrequency(&i);
	frequencySeconds = (float)(i.QuadPart);
	QueryPerformanceCounter(&i);
	start = i.QuadPart;

	instance->_workRunnging = true;
	while (instance->_mainRun)
	{
		QueryPerformanceCounter(&i);
		sTime.elapsedTime = (float)(i.QuadPart - start) / frequencySeconds;
		start = i.QuadPart;
		sTime.totalTime += sTime.elapsedTime;
		instance->_effectEngine->Action(&sTime);
		Sleep(1);
	}

	instance->_workRunnging = false;
}

const bool Client::IsVisibleClient(Client * c)
{
	std::lock_guard<std::mutex> lock(_visibleListMutex);
	for (size_t i = 0; i < _visibleClients.size(); i++)
	{
		if (_visibleClients[i] == c)
			return true;
	}
	return false;
}
void Client::RemoveVisibleClient(Client * c)
{
	std::lock_guard<std::mutex> lock(_visibleListMutex);
	for (size_t i = 0; i < _visibleClients.size(); i++)
	{
		if (_visibleClients[i] == c)
		{
			Player * p = c->GetSelectedPlayer();
			if (p)
				BroadcastSystem::BroadcastDespawnPlayer(this, p->_entityId, p->_subId);
			
			_visibleClients.erase(_visibleClients.begin() + i);
			break;
		}
	}

}
void Client::AddVisibleClient(Client * c)
{
	if (!c || !c->HasSelectedPlayer())
		return;
	BroadcastSystem::BroadcastSpawnPlayer(this, c);


	std::lock_guard<std::mutex> lock(_visibleListMutex);
	_visibleClients.push_back(c);
}
void Client::ClearVisibleClients()
{
	std::lock_guard<std::mutex> lock(_visibleListMutex);
	for (size_t i = 0; i < _visibleClients.size(); i++)
	{
		if (_visibleClients[i])
		{
			_visibleClients[i]->RemoveVisibleClient(this);
			RemoveVisibleClient(_visibleClients[i]);
		}
	}
	_visibleClients.clear();
}
void Client::Disappear()
{
	for (size_t i = 0; i < _visibleClients.size(); i++)
	{
		if (_visibleClients[i])
			_visibleClients[i]->RemoveVisibleClient(this);
	}
}
const bool Client::HasSelectedPlayer()
{
	return IsLoggedIn() && _account->GetSelectedPlayer();
}

const bool Client::Send(byte * data, unsigned int length)
{
#ifdef DUMP_TRAFFIC
	Dump(data, length, false); //logs hex text data to sendDump.txt
	std::cout << "<" << ServerUtils::HexString(data, length) << std::endl;
#endif
	_sendMutex.lock();
	_session->Encrypt(data, length);
	_sendMutex.unlock();

	int ret = send(_socket, (const char*)data, length, 0);
	return (ret == SOCKET_ERROR) ? false : true;
}
const bool Client::Send(Stream * s)
{
	return Send(s->_raw, s->_size);
}

void Client::Dump(byte* data, unsigned int length, bool recv)
{
	if (recv)
	{

		std::fstream f = std::fstream("C://recvDump.txt", std::ios::app);

		f << "Dump opcode:" << ServerUtils::HexString(&data[2], 2) << "]\n";
		f << ServerUtils::HexString(data, length);
		f << "\n\n";
		f.close();

	}
	else
	{
		std::fstream f = std::fstream("C://sendDump.txt", std::ios::app);

		f << "Dump opcode:" << ServerUtils::HexString(&data[2], 2) << "]\n";
		f << ServerUtils::HexString(data, length);
		f << "\n\n";
		f.close();

	}
}

void Client::SendToVisibleClients(Stream * data)
{
	std::lock_guard<std::mutex> lock(_visibleListMutex);
	for (size_t i = 0; i < _visibleClients.size(); i++)
	{
		if (_visibleClients[i])
			_visibleClients[i]->Send(data);
	}
}

void Client::LoginClient(Account * account)
{
	if (_loggedIn || account->_owner)
		return;
	_loggedIn = true;
	_account = account;
	_account->_owner = this;
}

void Client::LogoutClient()
{
	if (!_loggedIn)
		return;
	_loggedIn = false;
	_account->_owner = nullptr;
	_account = 0;
}

const bool Client::IsLoggedIn()
{
	return _loggedIn && _account;
}

Account * Client::GetAccount()
{
	return _account;
}

Player * Client::GetSelectedPlayer()
{
	if (!_loggedIn)
		return nullptr;
	return _account->GetSelectedPlayer();
}


