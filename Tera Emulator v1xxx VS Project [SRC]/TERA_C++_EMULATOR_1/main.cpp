#include <iostream>
#include <string>

#include "Server.hpp"
#include "EntityService.h"
#include "WorldSystem.h"
#include <algorithm>

#ifndef SERVER_VERSION
#define SERVER_VERSION 1050
#endif

int main() {

	SetConsoleTitle(L"Tera Emulator v1050 Beta");
	HANDLE _handler = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dc = COORD();
	dc.X = 200;
	dc.Y = 1000;
	SetConsoleScreenBufferSize(_handler, dc);

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetConsoleTextAttribute(_handler, 0x0C);
	
	EntityService::Initialize();
	Server *_server = new Server();

	bool run = true; bool started = false;
	if (!_server->Initialize())
	{
		std::cout << ">Initialization Error!\n\n";
		run = false;
	}

	if (_server->_serverConfig.autoStart)
		started = true;
	std::string line;
	while (run)
	{
		std::cin >> line;
		if (line == "./start")
		{
			if (!_server->Run())
				std::cout << ">Server working!\n";
			else
				started = true;
		}
		else  if (line == "./stop")
		{
			if (_server->Shutdown())
				std::cout << ">Server Shutdown!\n\n";
			else
				std::cout << ">Server is down!\n";

			started = false;
		}
		else if (line == "./asc")
		{
			if (!started)
			{
				std::string area = "";
				std::cout << "::Enter ContinentId:";
				std::cin >> area;
				int continentId = -1;
				sscanf(area.c_str(), "%d", &continentId);
				if (continentId > -1)
				{
					int j = -1;
					for (size_t i = 0; i < WorldSystem::_worldConfig.toStartAreas.size(); i++)
					{
						if (WorldSystem::_worldConfig.toStartAreas[i] == continentId)
						{
							j = i;
							break;
						}
					}
					if (j == -1)
					{
						WorldSystem::_worldConfig.toStartAreas.push_back(continentId);
						std::cout << "::GOOD\n";
					}
					else
					{
						std::cout << "::FAILED, CONTINENT ALREADY IN TO-START-LIST\n";
					}
				}
				else
					std::cout << "::FAILED\n";
			}
			else
				std::cout << "::NOT WHILE RUNNING\n";

		}
		else if (line == "./inf")
		{
			if (started)
			{
				std::cout << "::CONENCTED CLIENTS[" << _server->_clients.size() << "]\n::ACTIVE AREAS[" << WorldSystem::_worldConfig.toStartAreas.size() << "]\n";
			}
			else
				std::cout << "::SERVER STATUS[" << started << "]\n";
		}
		else if (line == "./cls")
		{
			system("cls");
			std::cout << "::SERVER STATUS[" << started << "]\n";
		}
		else if (line == "./close")
		{
			std::cout << "::Enter EntityId:";
			int id = -1;
			line = "";
			std::cin >> line;
			id = atoi(line.c_str());
			if (id > 0)
			{
				Entity* entity = EntityService::GetEntity(id);
				Client* client = (Client*)entity;
				if (client)
				{
					client->Close();
				}
				else
					std::cout << "::BAD\n";
			}
		}
		else if (line == "./exit")
		{
			std::cout << "::You shure you want to exit server? [y/Y|n/N]:";
			std::string result = "";
			std::cin >> result;
			std::transform(result.begin(), result.end(), result.begin(), ::tolower);
			if (result == "y")
			{
				break;
			}
			else if (result == "n")
			{
				//need?
			}
			else
			{
				std::cout << "::BAD\n";
			}
		
		}
	}

	delete _server;
	_server = 0;

	system("pause");

	return 0;
}