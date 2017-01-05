#ifndef ABNORMALITY_MANAGER
#define ABNORMALITY_MANAGER

class Client; class Player; class Server;
class CombatManager
{
public:
	CombatManager();
	~CombatManager();

	const bool AddAbnormality(int id);
	const bool AddPassivity(int id);
	
	 
	void Action(Client* caller, Server* server);


};

#endif