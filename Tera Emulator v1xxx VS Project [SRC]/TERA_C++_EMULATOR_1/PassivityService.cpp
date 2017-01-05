#include "PassivityService.h"
#include "XMLDocumentParser.h"
#include <sstream>
#include <fstream>
#include "Passivity.h"


void PassivityService::Release()
{
	for (size_t i = 0; i < _passivities.size(); i++)
	{
		if (_passivities[i])
		{
			delete _passivities[i];
			_passivities[i] = 0;
		}
	}
	_passivities.clear();
	//clean up
}

const bool PassivityService::LoadPassivities(const char * file)
{
	std::stringstream ss;
	ss << file << "\\info.txt" << '\0';
	std::fstream infoFile = std::fstream(ss.str());
	if (!infoFile.is_open())
		return false;

	int toReadFileCount = 0; std::string line;
	std::getline(infoFile, line); sscanf(line.c_str(), "count =%d", &toReadFileCount);
	if (toReadFileCount == 0)
		return false;

	for (size_t i = 0; i < toReadFileCount; i++)
	{
		ss.clear();
		ss.str("");
		ss << file << "//Passivity-" << i << ".xml" << '\0';
		std::cout << "Loading passivities from [Passivity-" << i << ".xml]\n";
		if (!XMLDocumentParser::ParsePassivityXMLDocument(ss.str().c_str(), _passivities))
			continue;

	}
	return true;
}

const unsigned int PassivityService::GetCount()
{
	return _passivities.size();
}
Passivity * PassivityService::ResolvePassivity(int id)
{
	for (size_t i = 0; i < _passivities.size(); i++)
	{
		if (_passivities[i] && _passivities[i]->_id == id)
			return _passivities[i];
	}
	return nullptr;
}
std::vector<Passivity*>	PassivityService::_passivities;