#ifndef PASSIVITY_SERVICE_H
#define PASSIVITY_SERVICE_H

#include <vector>

class Passivity;
class PassivityService
{
public:
	static void Release();

	static const bool LoadPassivities(const char* fileName);
	static const unsigned int GetCount();
	static Passivity* ResolvePassivity(int id);
private:
	static std::vector<Passivity*> _passivities;


};

#endif