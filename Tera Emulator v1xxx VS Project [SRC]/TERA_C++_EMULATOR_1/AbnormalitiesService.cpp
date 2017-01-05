#include "AbnormalitiesService.h"
#include "EffectService.h"
#include "IAbnormality.h"
#include "Stream.h"
#include "XMLDocumentParser.h"

const bool AbnormalitiesService::LoadAbnormalities(const char * file)
{
	std::string line = file;
	line += "//info.txt";
	std::ifstream infoFile = std::ifstream(line);
	if (!infoFile.is_open())
		return false;
	int toReadCount = 0;
	line.clear();
	std::getline(infoFile, line);
	sscanf(line.c_str(), "count =%d", &toReadCount);
	infoFile.close();

	std::stringstream ss;

	for (size_t i = 0; i < toReadCount; i++)
	{
		ss.clear(); ss.str("");
		ss << file << "//Abnormality-" << i << ".xml";
		std::cout << "Loading abnormalities from [Abnormality-" << i << ".xml]\n";
		if (!XMLDocumentParser::ParseAbnormalityXMLDocument(ss.str().c_str(), _abnormalities))
			continue;
	}

	return true;
}

void AbnormalitiesService::Release()
{
	for (size_t i = 0; i < _abnormalities.size(); i++)
	{
		if (_abnormalities[i])
		{
			delete _abnormalities[i];
			_abnormalities[i] = 0;
		}
	}
}

unsigned int AbnormalitiesService::GetCount()
{
	return _abnormalities.size();
}

IAbnormality * AbnormalitiesService::ResolveAbnormality(int id)
{
	for (size_t i = 0; i < _abnormalities.size(); i++)
	{
		if (_abnormalities[i] && _abnormalities[i]->_id == id)
			return _abnormalities[i];
	}
	return nullptr;
}

std::vector <IAbnormality *> AbnormalitiesService::_abnormalities;