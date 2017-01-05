#ifndef AB_SERVICE_H
#define AB_SERVICE_H

#include <fstream>
#include <vector>
#include <mutex>

class IAbnormality; 
class AbnormalitiesService
{
public:

	static const bool LoadAbnormalities(const char * file);

	static void Release();
	static unsigned int GetCount();
	static IAbnormality * ResolveAbnormality(int id);

	
private:
	static std::vector <IAbnormality *> _abnormalities;


};

#endif