#include "XMLDocumentParser.h"
#include "ServerTimer.h"
#include "IAbnormality.h"
#include "Passivity.h"
#include "Area.h"
#include "WorldPosition.h"
#include "AbnormalitiesService.h"
#include "EquipmentSet.h"

#include <string>


const bool XMLDocumentParser::ParseAreaXMLDocument(const char * fileName, std::vector<Area*>& out_items)
{
	std::vector<XMLNode*> _mainNodes;
	byte result = ParseXMLDocument(_mainNodes, fileName);
	if (result == 0)
	{
		//std::cout << ">Read [" << _mainNodes[1]->childNodes.size() - 1 << "] XMLNodes\n>Parsing XMLNodes into Areas...\n";
	}
	else if (result == 1)
	{
		std::cout << "::Failed to open XMLDocument [File] [" << fileName << "]\n";
	}
	else if (result == 2)
	{
		std::cout << "::Nothing to read from [" << fileName << "]\n";
	}



	for (size_t i = 0; i < _mainNodes.size(); i++)
	{
		if (i == 1)
			BuildAreas(_mainNodes[i], out_items);

		if (_mainNodes[i])
		{
			delete _mainNodes[i];
			_mainNodes[i] = 0;
		}
	}
	_mainNodes.clear();
	return true;
}
const bool XMLDocumentParser::ParseItemsXMLDocument(const char* fileName, std::vector<IItem*>& out_items)
{
	std::vector<XMLNode*> _mainNodes;
	byte result = ParseXMLDocument(_mainNodes, fileName);
	if (result == 0)
	{
		std::cout << ">Read [" << _mainNodes[1]->childNodes.size() - 1 << "] XMLNodes\n>Parsing XMLNodes into Items...\n";
	}
	else if (result == 1)
	{
		std::cout << "::Failed to open XMLDocument [File] [" << fileName << "]\n";
	}
	else if (result == 2)
	{
		std::cout << "::Nothing to read from [" << fileName << "]\n";
	}



	InitItemsDictionary();
	for (size_t i = 0; i < _mainNodes.size(); i++)
	{

		if (i == 1)
		{
			BuildItems(_mainNodes[i], out_items);
		}

		if (_mainNodes[i])
		{
			delete _mainNodes[i];
			_mainNodes[i] = 0;
		}
	}
	std::cout << "\n\n";
	_mainNodes.clear();
	return true;

}
const bool XMLDocumentParser::ParseSkillXMLDocument(const char * fileName, std::vector<Skill*>& out_skills)
{
	std::vector<XMLNode*> _mainNodes;
	byte result = ParseXMLDocument(_mainNodes, fileName);
	if (result == 0)
	{
		std::cout << ">Read [" << _mainNodes[1]->childNodes.size() - 1 << "] XMLNodes\n>Parsing XMLNodes into Skills...\n";
	}
	else if (result == 1)
	{
		std::cout << "::Failed to open XMLDocument [File] [" << fileName << "]\n";
	}
	else if (result == 2)
	{
		std::cout << "::Nothing to read from [" << fileName << "]\n";
	}
	InitSkillsDictionary();



	for (size_t i = 0; i < _mainNodes.size(); i++)
	{

		if (i == 1)
		{
			BuildSkill(_mainNodes[i], out_skills);
		}

		if (_mainNodes[i])
		{
			delete _mainNodes[i];
			_mainNodes[i] = 0;
		}


	}
	std::cout << "\n\n";
	_mainNodes.clear();



	return true;
}
const bool XMLDocumentParser::ParseAbnormalityXMLDocument(const char * fileName, std::vector<IAbnormality*>& out_abnormalities)
{
	std::vector<XMLNode*> _mainNodes;
	byte result = ParseXMLDocument(_mainNodes, fileName);
	if (result == 0)
	{
		std::cout << ">Read [" << _mainNodes[1]->childNodes.size() - 1 << "] XMLNodes\n>Parsing XMLNodes into Abnormalities...\n";
	}
	else if (result == 1)
	{
		std::cout << "::Failed to open XMLDocument [File] [" << fileName << "]\n";
	}
	else if (result == 2)
	{
		std::cout << "::Nothing to read from [" << fileName << "]\n";
	}




	for (size_t i = 0; i < _mainNodes.size(); i++)
	{
		if (i == 1)
		{
			BuildAbnormality(_mainNodes[i], out_abnormalities);
		}

		if (_mainNodes[i])
		{
			delete _mainNodes[i];
			_mainNodes[i] = 0;
		}
	}
	std::cout << "\n\n";
	_mainNodes.clear();
	return true;
}
const bool XMLDocumentParser::ParsePassivityXMLDocument(const char * fileName, std::vector<Passivity*>& out_passivities)
{
	std::vector<XMLNode*> _mainNodes;
	byte result = ParseXMLDocument(_mainNodes, fileName);
	if (result == 0)
	{
		std::cout << ">Read [" << _mainNodes[1]->childNodes.size() - 1 << "] XMLNodes\n>Parsing XMLNodes into Passivities...\n";
	}
	else if (result == 1)
	{
		std::cout << "::Failed to open XMLDocument [File] [" << fileName << "]\n";
	}
	else if (result == 2)
	{
		std::cout << "::Nothing to read from [" << fileName << "]\n";
	}
	InitPassivityDictionary();



	for (size_t i = 0; i < _mainNodes.size(); i++)
	{
		if (i == 1)
		{
			BuildPassivity(_mainNodes[i], out_passivities);
		}

		if (_mainNodes[i])
		{
			delete _mainNodes[i];
			_mainNodes[i] = 0;
		}
	}
	std::cout << "\n\n";
	_mainNodes.clear();
	return true;
}
const bool XMLDocumentParser::ParseEquipmentSetXMLDocument(const char * fileName, std::map<int, EquipmentSetData*>& out_equipmentSets)
{
	std::vector<XMLNode*> _mainNodes;
	byte result = ParseXMLDocument(_mainNodes, fileName);
	if (result == 0)
	{
		std::cout << ">Read [" << _mainNodes[1]->childNodes.size() - 1 << "] XMLNodes\n>Parsing XMLNodes into EquipmentSetData...\n";
	}
	else if (result == 1)
	{
		std::cout << "::Failed to open XMLDocument [File] [" << fileName << "]\n";
		return false;
	}
	else if (result == 2)
	{
		std::cout << "::Nothing to read from [" << fileName << "]\n";
		return false;
	}

	if (_mainNodes.size() > 1)
		for (size_t i = 0; i < _mainNodes[1]->childNodes.size(); i++)
			BuildEquipmentSetData(_mainNodes[1]->childNodes[i], out_equipmentSets);

	else
		return false;
	std::cout << "::Parsed <<[" << out_equipmentSets.size() << "] equipmentSets\n\n";

	return true;
}
const byte XMLDocumentParser::ParseXMLDocument(std::vector<XMLNode*>& out_nodes, const char * fileName)
{
	std::ifstream file = std::ifstream(fileName, std::ifstream::ate);
	if (!file.is_open())
		return 1;
	unsigned int fileSize = file.tellg();
	file.seekg(std::ifstream::beg);

	char * buffer = new char[fileSize];
	file.read(buffer, fileSize);
	file.close();
	if (fileSize <= 80)
	{
		return 2; // nothing to read
	}

	XMLNode * newNode = nullptr;
	int mainCursor = 0;
	for (size_t i = 0; i < 2; i++)
	{
		newNode = new XMLNode();
		mainCursor += GetNode(buffer, mainCursor, newNode);
		if (newNode)
		{
			out_nodes.push_back(newNode);
		}
	}




	delete[] buffer;
	buffer = 0;
	return 0;
}
int XMLDocumentParser::GetNode(char* buffer, int mainCursor, XMLNode* outNode)
{
	int argumentCursor = 0, valueCursor = 0, nameCursor = 0; byte result = 0;
	short argumentNameSize = 0, argumentValueSize = 0, nameSize;
	std::string name = "";


#pragma region NAME
	while (1)
	{
		if (buffer[mainCursor] == '<')
		{
			mainCursor++;

			while (buffer[mainCursor] == ' ')
				mainCursor++; //remove whiteSpaces

			nameCursor = mainCursor;

			while (buffer[nameCursor] != ' ' && buffer[nameCursor] != '>')
				nameCursor++;
			nameSize = nameCursor - mainCursor;
			name = "";
			if (nameSize <= 0)
			{
#ifdef XML_DEBUG
				result = 3;
				std::cout << "::NAME SIZE IS [" << nameSize << "] LINE[" << __LINE__ << "] ->ERROR\n\n";
#endif
				break;
			}
			for (size_t i = 0; i < nameSize; i++)
			{
				name += buffer[mainCursor + i];
			}
			break;
		}
		mainCursor++;
	}

	mainCursor += nameSize;
#pragma endregion
	outNode->tagName = name;

	while (buffer[mainCursor] == ' ')
		mainCursor++; //remove whiteSpaces

	if (name[0] == '/')
		return mainCursor;

	//case <tagname> or <tagname/>
	if (buffer[mainCursor] == '/' && buffer[mainCursor + 1] == '>')
	{
		mainCursor += 2; //go past />
		return mainCursor;
	}
	else if (buffer[mainCursor] == '>')
	{
		XMLNode* childNode = nullptr;
		while (1)
		{
			childNode = new XMLNode();
			childNode->parentNode = outNode;
			mainCursor = GetNode(buffer, mainCursor, childNode);
			outNode->childNodes.push_back(childNode);
			std::string toCheckName = name;
			toCheckName.insert(toCheckName.begin(), '/');
			if (toCheckName == childNode->tagName)
			{
				break;
			}
		}
		return mainCursor;
	}

#pragma region ARGUMENTS
	while (1)
	{
		while (buffer[mainCursor] == ' ')
			mainCursor++; //remove whiteSpaces

		if (buffer[mainCursor] == '>') // node with no arguments
		{
			argumentCursor++; // go past >
			XMLNode* childNode = nullptr;
			while (1)
			{
				childNode = new XMLNode();
				childNode->parentNode = outNode;
				argumentCursor = GetNode(buffer, argumentCursor, childNode);
				outNode->childNodes.push_back(childNode);
				std::string toCheckName = name;
				toCheckName.insert(toCheckName.begin(), '/');
				if (toCheckName == childNode->tagName)
				{
					break;
				}
			}

			mainCursor = argumentCursor;
			break;
		}
		else if (buffer[mainCursor] == '/' && buffer[mainCursor] == '>')
		{
			break;// no arguemtns , node finished
		}

		while (buffer[mainCursor] == ' ')
			mainCursor++; //remove whiteSpaces

		XMLNodeArgument * newArg = new XMLNodeArgument();
		valueCursor = 0; argumentCursor = mainCursor;


		while (1)
		{
			if (buffer[argumentCursor] == '\"' && valueCursor == 0)
			{
				if (buffer[argumentCursor + 1] == '\"') //case argName=""
				{
					argumentCursor++;
					valueCursor = argumentCursor;
					argumentCursor++;
					break;
				}

				argumentCursor++;
				valueCursor = argumentCursor;

			}
			else if (buffer[argumentCursor] == '\"' && valueCursor != 0)
			{
				argumentCursor++;
				break;
			}

			argumentCursor++;
		}

		argumentValueSize = argumentCursor - valueCursor - 1;
		argumentNameSize = valueCursor - mainCursor - 2;
		for (size_t i = 0; i < argumentNameSize; i++)
		{
			newArg->argumentName += buffer[mainCursor + i];
		}
		for (size_t i = 0; i < argumentValueSize; i++)
		{
			newArg->argumentValue += buffer[valueCursor + i];
		}
		outNode->_arguments.push_back(newArg);

		while (buffer[argumentCursor] == ' ')
			argumentCursor++;

		if (buffer[argumentCursor] == '>')
		{
			argumentCursor++; // go past >
			XMLNode* childNode = nullptr;
			while (1)
			{
				childNode = new XMLNode();
				childNode->parentNode = outNode;
				argumentCursor = GetNode(buffer, argumentCursor, childNode);
				outNode->childNodes.push_back(childNode);
				std::string toCheckName = name;
				toCheckName.insert(toCheckName.begin(), '/');
				if (toCheckName == childNode->tagName)
				{
					break;
				}
			}

			mainCursor = argumentCursor;
			break;
		}
		else if (buffer[argumentCursor] == '/' && buffer[argumentCursor + 1] == '>')
		{
			//we dont have ChildNodes return size
			argumentCursor += 2; //go past />
			mainCursor = argumentCursor;
			return mainCursor;
		}
		else if (buffer[argumentCursor] == '?' && buffer[argumentCursor + 1] == '>')
		{
			//we dont have ChildNodes return size
			argumentCursor += 2; //go past />
			mainCursor = argumentCursor;
			return mainCursor;
		}
		mainCursor += argumentNameSize + argumentValueSize + 3;
	}
#pragma endregion
	return mainCursor;
}
const bool XMLDocumentParser::ParseRegionStrSheetXMLDocument(const char * fileName)
{
	std::vector<XMLNode*> out_nodes;
	ParseXMLDocument(out_nodes, fileName);

	for (size_t i = 0; i < out_nodes[1]->childNodes.size(); i++)
	{
		BuildRegionName(out_nodes[1]->childNodes[i]);
	}

	for (size_t i = 0; i < out_nodes.size(); i++)
	{
		delete out_nodes[i];
		out_nodes[i] = 0;
	}
	return true;
}

void XMLDocumentParser::BuildRegionName(XMLNode * node)
{
	XMLNodeArgument  *arg = nullptr;
	int id = 0; std::string name = "";
	for (size_t i = 0; i < node->_arguments.size(); i++)
	{
		arg = node->ConsumeArgument("id");
		if (arg)
			id = atoi(arg->argumentValue.c_str());
		else
			continue;

		arg = node->ConsumeArgument("string");
		if (arg)
			name = arg->argumentValue;
		else
			continue;

		regionsNames.insert(std::pair<int, std::string>(id, name));
	}
}
void XMLDocumentParser::BuildAreas(XMLNode * mainNode, std::vector<Area*>& out_areas)
{
	XMLNodeArgument* arg = nullptr;
	Area* area = new Area();
	AreaSection* newSection = nullptr; AreaSection* subSection = nullptr;
	XMLNode* subNode = nullptr;

	for (size_t i = 0; i < mainNode->_arguments.size(); i++)
	{
		if ((arg = mainNode->ConsumeArgument("continentId")))
		{
			area->_continentId = atoi(arg->argumentValue.c_str());
		}
		else if ((arg = mainNode->ConsumeArgument("nameId")))
		{
			area->_name = regionsNames[atoi(arg->argumentValue.c_str())];
		}
		else if ((arg = mainNode->ConsumeArgument("ride")))
		{
			area->_ride = arg->argumentValue == "True" ? true : false;
		}
		else if ((arg = mainNode->ConsumeArgument("worldMapGuardId")))
		{
			area->_worldMapGuardId = atoi(arg->argumentValue.c_str());
		}
		else if ((arg = mainNode->ConsumeArgument("worldMapWorldId")))
		{
			area->_worldMapWorldId = atoi(arg->argumentValue.c_str());
		}
	}

	for (size_t i = 0; i < mainNode->childNodes.size(); i++)
	{
		if (!mainNode->childNodes[i] || mainNode->childNodes[i]->tagName != "Section")
			continue;
		subNode = mainNode->childNodes[i];
		newSection = new AreaSection();
		memset(newSection, 0, sizeof(AreaSection));

		for (size_t j = 0; j < subNode->_arguments.size(); j++)
		{
			if ((arg = subNode->ConsumeArgument("huntingZoneId")))
			{
				newSection->huntingZoneId = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("priority")))
			{
				newSection->priority = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("ignoreObstacleShortTel")))
			{
				newSection->ignoreObstacleShortTel = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("pk")))
			{
				newSection->pk = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("ride")))
			{
				newSection->ride = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("vender")))
			{
				newSection->vender = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("addMaxZ")))
			{
				newSection->addMaxZ = atof(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("subtractMinZ")))
			{
				newSection->subtractMinZ = atof(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("campId")))
			{
				newSection->campId = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("floor")))
			{
				newSection->floor = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("restBonus")))
			{
				newSection->restExpBonus = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("worldMapSectionId")))
			{
				newSection->worldMapSectionId = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("nameId")))
			{
				newSection->nameId = atoi(arg->argumentValue.c_str());
				newSection->name = regionsNames[atoi(arg->argumentValue.c_str())];
			}

		}

		XMLNode* subSubNode = nullptr;
		for (size_t i = 0; i < subNode->childNodes.size(); i++)
		{
			subSubNode = subNode->childNodes[i];
			if (subSubNode && subSubNode->tagName == "Fence")
			{
				for (size_t i = 0; i < subSubNode->_arguments.size(); i++)
				{
					if ((arg = subSubNode->ConsumeArgument("pos")))
					{
						Fence* newFence = new Fence;
						memset(newFence, 0, sizeof Fence);
						sscanf(arg->argumentValue.c_str(), "%f,%f,%f", &newFence->x, &newFence->y, &newFence->z);
						newSection->_fences.push_back(newFence);
					}
				}
			}
			else if (subSubNode && subSubNode->tagName == "Section")
			{
				subSection = new AreaSection;
				memset(subSection, 0, sizeof AreaSection);
				for (size_t j = 0; j < subSubNode->_arguments.size(); j++)
				{
					if ((arg = subSubNode->ConsumeArgument("huntingZoneId")))
					{
						subSection->huntingZoneId = atoi(arg->argumentValue.c_str());
					}
					else if ((arg = subSubNode->ConsumeArgument("priority")))
					{
						subSection->priority = atoi(arg->argumentValue.c_str());
					}
					else if ((arg = subSubNode->ConsumeArgument("ignoreObstacleShortTel")))
					{
						subSection->ignoreObstacleShortTel = arg->argumentValue == "True" ? true : false;
					}
					else if ((arg = subSubNode->ConsumeArgument("pk")))
					{
						subSection->pk = arg->argumentValue == "True" ? true : false;
					}
					else if ((arg = subSubNode->ConsumeArgument("ride")))
					{
						subSection->ride = arg->argumentValue == "True" ? true : false;
					}
					else if ((arg = subSubNode->ConsumeArgument("vender")))
					{
						subSection->vender = arg->argumentValue == "True" ? true : false;
					}
					else if ((arg = subSubNode->ConsumeArgument("addMaxZ")))
					{
						subSection->addMaxZ = atof(arg->argumentValue.c_str());
					}
					else if ((arg = subSubNode->ConsumeArgument("subtractMinZ")))
					{
						subSection->subtractMinZ = atof(arg->argumentValue.c_str());
					}
					else if ((arg = subSubNode->ConsumeArgument("campId")))
					{
						subSection->campId = atoi(arg->argumentValue.c_str());
					}
					else if ((arg = subSubNode->ConsumeArgument("floor")))
					{
						subSection->floor = atoi(arg->argumentValue.c_str());
					}
					else if ((arg = subSubNode->ConsumeArgument("restBonus")))
					{
						subSection->restExpBonus = arg->argumentValue == "True" ? true : false;
					}
					else if ((arg = subSubNode->ConsumeArgument("worldMapSectionId")))
					{
						subSection->worldMapSectionId = atoi(arg->argumentValue.c_str());
					}
					else if ((arg = subSubNode->ConsumeArgument("nameId")))
					{
						subSection->nameId = atoi(arg->argumentValue.c_str());
						subSection->name = regionsNames[atoi(arg->argumentValue.c_str())];
					}

				}
				area->_sections.push_back(subSection);
			}
		}
		area->_sections.push_back(newSection);
	}
	/*for (size_t i = 0; i < subNode->childNodes.size(); i++)
	{
		if (!subNode->childNodes[i] || subNode->childNodes[i]->tagName != "Section")
			continue;

		subNode = subNode->childNodes[i];
		newSection = new AreaSection();
		memset(newSection, 0, sizeof(AreaSection));

		for (size_t j = 0; j < subNode->_arguments.size(); j++)
		{
			if ((arg = subNode->ConsumeArgument("huntingZoneId")))
			{
				newSection->huntingZoneId = atoi(arg->argumentName.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("priority")))
			{
				newSection->priority = atoi(arg->argumentName.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("ignoreObstacleShortTel")))
			{
				newSection->ignoreObstacleShortTel = arg->argumentName == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("pk")))
			{
				newSection->pk = arg->argumentName == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("ride")))
			{
				newSection->ride = arg->argumentName == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("vender")))
			{
				newSection->vender = arg->argumentName == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("addMaxZ")))
			{
				newSection->addMaxZ = atof(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("subtractMinZ")))
			{
				newSection->subtractMinZ = atof(arg->argumentValue.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("campId")))
			{
				newSection->campId = atoi(arg->argumentName.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("floor")))
			{
				newSection->floor = atoi(arg->argumentName.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("restBonus")))
			{
				newSection->restExpBonus = arg->argumentName == "True" ? true : false;
			}
			else if ((arg = subNode->ConsumeArgument("worldMapSectionId")))
			{
				newSection->worldMapSectionId = atoi(arg->argumentName.c_str());
			}
			else if ((arg = subNode->ConsumeArgument("nameId")))
			{
				newSection->name = regionsNames[atoi(arg->argumentValue.c_str())];
			}


		}
		area->_sections.push_back(newSection);
	}
	}
*/

	area->Initialize();
	out_areas.push_back(area);


}
void XMLDocumentParser::BuildItems(XMLNode * mainnode, std::vector<IItem*>& out_items)
{
	int parsedPerSecond = 0;
	short parsingSpeed = 0;
	long long time = ServerTimer::GetCurrentUTC();
	long long time2 = 0;
	XMLNode* node = nullptr;
	XMLNodeArgument* arg = nullptr;
	IItem* out = nullptr;
	for (size_t j = 0; j < mainnode->childNodes.size() - 1; j++)
	{

		if ((time2 = ServerTimer::GetCurrentUTC()) - time > 1)
		{
			time = time2;
			parsingSpeed = parsedPerSecond;
			parsedPerSecond = 0;
		}
		std::cout << "::Parsed <<[" << j << "] items. Parsing speed ~[" << parsingSpeed / 2 << "] Items per second." << "\r" << std::flush;

		out = new IItem();
		node = mainnode->childNodes[j];
		for (size_t i = 0; i < node->_arguments.size(); i++)
		{
			if ((arg = node->ConsumeArgument("id")))
			{
				out->_id = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("name")))
			{
				out->_name == arg->argumentValue.c_str();
			}
			else if ((arg = node->ConsumeArgument("coolTime")))
			{
				out->_coolTime = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("category")))
			{
				out->_category = itemCategoryDictionary[arg->argumentValue];
			}
			else if ((arg = node->ConsumeArgument("level")))
			{
				out->_itemLevel = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("rank")))
			{
				out->_rank = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("maxStack")))
			{
				out->_maxStack = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("rareGrade")))
			{
				out->_rareGrade = (ItemRareGrade)atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("requiredEquipmentType")))
			{
				out->_requiredEquipmentType = itemTypeDictionary[arg->argumentValue];
			}
			else if ((arg = node->ConsumeArgument("combatItemType")))
			{
				out->_type = itemTypeDictionary[arg->argumentValue];
			}
			else if ((arg = node->ConsumeArgument("requiredLevel")))
			{
				out->_requiredLevel = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("artisanable")))
			{
				out->_artisanable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("dismantlable")))
			{
				out->_dismantlable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("extractLook")))
			{
				//todo
			}
			else if ((arg = node->ConsumeArgument("guildWarehouseStorable")))
			{
				out->_guildBankStorable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("masterpieceRate")))
			{
				out->_masterpieceRate = atof((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("obtainable")))
			{
				out->_obtainable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("sellPrice")))
			{
				out->_sellPrice = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("slotLimit")))
			{
				out->_slotLimit = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("sortingNumber")))
			{
				out->_sortingNumber = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("storeSellable")))
			{
				out->_sellable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("tradable")))
			{
				out->_tradable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("unidentifiedItemGrade")))
			{
				out->_itemGrade = (ItemGrade)atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = node->ConsumeArgument("useOnlyTerritory")))
			{
				out->_useOnlyTerritory = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("warehouseStorable")))
			{
				out->_warehouseStoreable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("changeColorEnable")))
			{
				out->_changeColorEnable = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = node->ConsumeArgument("boundType")))
			{
				out->_bountType = itemBoundTypeDictionary[(const char*)arg->argumentValue.c_str()];
			}
			else if ((arg = node->ConsumeArgument("requiredClass")))
			{
				out->_requiredClass = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkMasterpiecePassivityCategoryId")))
			{
				out->_linkMasterpiecePassivityCategoryId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkPassivityCategoryId")))
			{
				out->_linkPassivityCategoryId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkPassivityId")))
			{
				out->_linkPassivityId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkCrestId")))
			{
				out->_linkCrestId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkCustomizingId")))
			{
				out->_linkCustomizingId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkEquipmentId")))
			{
				out->_linkEquipmentId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkLookInfoId")))
			{
				out->_linkLookInfoId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkPetAdultId")))
			{
				out->_linkPetAdultId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkPetOrbId")))
			{
				out->_linkPetOrbId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkSkillId")))
			{
				out->_linkSkillId = arg->argumentValue;
			}
			else if ((arg = node->ConsumeArgument("linkEnchantId")))
			{
				out->_linkEnchantId = arg->argumentValue;

			}
			else if ((arg = node->ConsumeArgument("changeLook")))
			{
				out->_changeLook = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}



		}
		out_items.push_back(out);
		parsedPerSecond++;
	}

}
void XMLDocumentParser::BuildSkill(XMLNode * node, std::vector<Skill*> &out_skills  /*not finished*/)
{
	int parsedPerSecond = 0;
	short parsingSpeed = 0;
	long long time = ServerTimer::GetCurrentUTC();
	long long time2 = 0;
	Skill * out = nullptr;
	XMLNodeArgument * arg = nullptr;
	for (size_t i = 0; i < node->childNodes.size(); i++)
	{
		
		if ((time2 = ServerTimer::GetCurrentUTC()) - time > 1)
		{
			time = time2;
			parsingSpeed = parsedPerSecond;
			parsedPerSecond = 0;
		}
		std::cout << "::Parsed <<[" << i << "] skills. Parsing speed ~[" << parsingSpeed / 2 << "] Skills per second." << "\r" << std::flush;
		
		out = new Skill();
		XMLNode* skillNode = node->childNodes[i];
		for (size_t j = 0; j < skillNode->_arguments.size(); j++)
		{
			if ((arg = skillNode->ConsumeArgument("id")))
			{
				out->_id = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = skillNode->ConsumeArgument("name")))
			{
				out->_name = arg->argumentValue;
			}
			else if ((arg = skillNode->ConsumeArgument("type")))
			{
				out->_type = skillTypeDictionary[arg->argumentValue];
			}
			else if ((arg = skillNode->ConsumeArgument("category")))
			{
				out->_category = arg->argumentValue;
			}
			else if ((arg = skillNode->ConsumeArgument("templateId")))
			{
				out->_templateId = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = skillNode->ConsumeArgument("nextSkill")))
			{
				out->_nextSkill = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = skillNode->ConsumeArgument("timeRate")))
			{
				out->_timeRate = atof(arg->argumentValue.c_str());
			}
			else if ((arg = skillNode->ConsumeArgument("attackRange")))
			{
				out->_attackRange = atof(arg->argumentValue.c_str());
			}
			else if ((arg = skillNode->ConsumeArgument("attackRangeMax")))
			{
				out->_attackRangeMax = atof(arg->argumentValue.c_str());
			}
			else if ((arg = skillNode->ConsumeArgument("autoUse")))
			{
				out->_autoUse = arg->argumentValue == "Ture" ? 1 : 0;
			}
			else if ((arg = skillNode->ConsumeArgument("changeDirToCenter")))
			{
				out->_changeDirToChanter = arg->argumentValue == "Ture" ? 1 : 0;
			}
			else if ((arg = skillNode->ConsumeArgument("needWeapon")))
			{
				out->_needWeapon = arg->argumentValue == "Ture" ? 1 : 0;
			}
			else if ((arg = skillNode->ConsumeArgument("pushtarget")))
			{
				out->_pushtarget = skillPushTargetDictionary[arg->argumentValue];
			}
			else if ((arg = skillNode->ConsumeArgument("totalAtk")))
			{
				out->_totalAttack = atof(arg->argumentValue.c_str());
			}
		}

		XMLNode * subNode = nullptr;
		for (size_t j = 0; j < skillNode->childNodes.size(); j++)
		{
			if ((subNode = skillNode->childNodes[j]))
			{
				if (subNode->tagName == "Property")
				{

				}
				else if (subNode->tagName == "Bullet")
				{

				}
				else if (subNode->tagName == "Action")
				{

				}
				else if (subNode->tagName == "TargetingList")
				{
					if ((arg = subNode->ConsumeArgument("adjustTargetingPos")))
					{
						out->_adjustTargetingPos = adjustTargetingPosDictionary[arg->argumentValue];
					}

					for (size_t x = 0; x < subNode->childNodes.size(); x++)
					{
						XMLNode* targetingNode = nullptr;
						if ((targetingNode = subNode->childNodes[x]) && targetingNode->tagName == "Targeting")
						{
							Targeting * newTargeting = new Targeting();

							for (size_t y = 0; y < targetingNode->_arguments.size(); y++)
							{
								if ((arg = targetingNode->ConsumeArgument("id")))
								{
									newTargeting->id = atoi(arg->argumentValue.c_str());
								}
								else if ((arg = targetingNode->ConsumeArgument("type")))
								{
									newTargeting->type = targetingTypeDictionary[arg->argumentValue];
								}
								else if ((arg = targetingNode->ConsumeArgument("time")))
								{
									newTargeting->time = atoi(arg->argumentValue.c_str());
								}
								else if ((arg = targetingNode->ConsumeArgument("mothod")))
								{
									newTargeting->method = targetingMethodDictionary[arg->argumentValue];
								}
								else if ((arg = targetingNode->ConsumeArgument("endTime")))
								{
									newTargeting->endTime = atoi(arg->argumentValue.c_str());
								}
								else if ((arg = targetingNode->ConsumeArgument("startTime")))
								{
									newTargeting->startTime = atoi(arg->argumentValue.c_str());
								}
								else if ((arg = targetingNode->ConsumeArgument("interval")))
								{
									newTargeting->interval = atoi(arg->argumentValue.c_str());
								}
								else if ((arg = targetingNode->ConsumeArgument("until")))
								{
									newTargeting->until = atoi(arg->argumentValue.c_str());
								}
							}

							if (targetingNode->childNodes.size() > 0 && targetingNode->childNodes[0]->tagName == "AreaList")
								for (size_t k = 0; k < targetingNode->childNodes[0]->childNodes.size(); k++)
								{
									TargetingArea * newTargetingArea = new TargetingArea;
									memset(newTargetingArea, 0, sizeof TargetingArea);

									for (size_t g = 0; g < targetingNode->childNodes[0]->childNodes[k]->_arguments.size(); g++)
									{
										if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("rotateAngle")))
										{
											newTargetingArea->rotateAngle = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("type")))
										{
											newTargetingArea->type = targetingAreaTypeDictionary[arg->argumentValue];
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("maxHeight")))
										{
											newTargetingArea->maxHeight = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("maxCount")))
										{
											newTargetingArea->maxCount = atoi(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("maxRadius")))
										{
											newTargetingArea->maxRadius = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("offsetDistance")))
										{
											newTargetingArea->offsetDistance = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("pierceDepth")))
										{
											newTargetingArea->pierceDepth = atoi(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("minHeight")))
										{
											newTargetingArea->minHeight = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("rangeAngle")))
										{
											newTargetingArea->rangeAngle = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("crosshairRadius")))
										{
											newTargetingArea->crosshairRadius = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("minRadius")))
										{
											newTargetingArea->minRadius = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("offsetAngle")))
										{
											newTargetingArea->offsetAngle = atof(arg->argumentValue.c_str());
										}
										else if ((arg = targetingNode->childNodes[0]->childNodes[k]->ConsumeArgument("crosshairRadius2")))
										{
											newTargetingArea->crosshairRadius2 = atof(arg->argumentValue.c_str());
										}

									}

									for (size_t g = 0; g < targetingNode->childNodes[0]->childNodes[k]->childNodes.size(); g++)
									{
										XMLNode* areaSubNode = nullptr;

										if ((areaSubNode = targetingNode->childNodes[0]->childNodes[k]->childNodes[g]))
										{
											if (areaSubNode->tagName == "Effect")
											{
												newTargetingArea->effect = AreaEffect();
												for (size_t f = 0; f < areaSubNode->_arguments.size(); f++)
												{
													if ((arg = areaSubNode->ConsumeArgument("atk")))
													{
														newTargetingArea->effect.atk = atoi(arg->argumentValue.c_str());
													}
												}

												for (size_t f = 0; f < areaSubNode->childNodes.size(); f++)
												{
													if (areaSubNode->childNodes[f]->tagName == "HpDiff")
													{
														if ((arg = areaSubNode->childNodes[f]->ConsumeArgument("value")))
															newTargetingArea->effect.hpDIff = atoi(arg->argumentValue.c_str());
													}
													else if (areaSubNode->childNodes[f]->tagName == "MpDiff")
													{
														if ((arg = areaSubNode->childNodes[f]->ConsumeArgument("value")))
															newTargetingArea->effect.mpDiff = atoi(arg->argumentValue.c_str());
													}
													else if (areaSubNode->childNodes[f]->tagName == "AbnormalityOnCommon")
													{
														std::string chuck = "";
														if ((arg = areaSubNode->childNodes[f]->ConsumeArgument("id")))
														{
															for (size_t v = 0; v < arg->argumentValue.size(); v++)
															{
																if (arg->argumentValue[v] == ';')
																{
																	IAbnormality* ab = AbnormalitiesService::ResolveAbnormality(atoi(chuck.c_str()));
																	if (ab)
																		newTargetingArea->effect.abnormalityOnCommon.push_back(ab);
																	chuck.clear();
																	continue;
																}
																chuck += arg->argumentValue[v];
															}

														}
													}
													else if (areaSubNode->childNodes[f]->tagName == "AbnormalityOnPvp")
													{
														std::string chuck = "";
														if ((arg = areaSubNode->childNodes[f]->ConsumeArgument("id")))
														{
															for (size_t v = 0; v < arg->argumentValue.size(); v++)
															{
																if (arg->argumentValue[v] == ';')
																{
																	IAbnormality* ab = AbnormalitiesService::ResolveAbnormality(atoi(chuck.c_str()));
																	if (ab)
																		newTargetingArea->effect.abnormalityOnPvP.push_back(ab);
																	chuck.clear();
																	continue;
																}
																chuck += arg->argumentValue[v];
															}

														}
													}

												}
											}
											else if (areaSubNode->tagName == "Reaction")
											{
												for (size_t f = 0; f < areaSubNode->_arguments.size(); f++)
												{
													if ((arg = areaSubNode->ConsumeArgument("basicRate")))
													{
														newTargetingArea->rectionBasicRate = atof(arg->argumentValue.c_str());
													}
													else if ((arg = areaSubNode->ConsumeArgument("miniRate")))
													{
														newTargetingArea->rectionMiniRate = atof(arg->argumentValue.c_str());
													}
												}
											}
											else if (areaSubNode->tagName == "HitEffect")
											{
												//need?
											}
										}
									}
								}
							else if (targetingNode->childNodes.size() > 1 && targetingNode->childNodes[1]->tagName == "Cost")
							{
								if ((arg = targetingNode->childNodes[1]->ConsumeArgument("hp")))
								{
									newTargeting->cost.HP = atoi(arg->argumentValue.c_str());
								}
								if ((arg = targetingNode->childNodes[1]->ConsumeArgument("mp")))
								{
									newTargeting->cost.MP = atoi(arg->argumentValue.c_str());
								}
							}
						}
					}
				}
				else if (subNode->tagName == "Defence")
				{

				}
				else if (subNode->tagName == "Drain")
				{

				}
				else if (subNode->tagName == "Precondition")
				{
					for (size_t x = 0; x < subNode->_arguments.size(); x++)
					{
						if ((arg = subNode->ConsumeArgument("coolTime")))
						{
							out->_precondition.coolTime = atoi(arg->argumentValue.c_str());
						}
						else if ((arg = subNode->ConsumeArgument("modeChangeMethod")))
						{
							out->_precondition.modeChangeMethod = atoi(arg->argumentValue.c_str());
						}
						else if ((arg = subNode->ConsumeArgument("modeNo")))
						{
							out->_precondition.modeNo = atoi(arg->argumentValue.c_str());
						}
					}
					for (size_t x = 0; x < subNode->childNodes.size(); x++)
					{
						if (subNode->childNodes[x]->tagName == "Cost")
						{
							if ((arg = subNode->childNodes[x]->ConsumeArgument("hp")))
							{
								out->_precondition.cost.HP = atoi(arg->argumentValue.c_str());
							}
							if ((arg = subNode->childNodes[x]->ConsumeArgument("mp")))
							{
								out->_precondition.cost.MP = atoi(arg->argumentValue.c_str());
							}
						}
						else if (subNode->childNodes[x]->tagName == "ExclusiveAbnormality")
						{
							//todo check for args..
						}
					}
				}
				else if (subNode->tagName == "Projectile")
				{

				}


			}
		}





		out_skills.push_back(out);
		parsedPerSecond++;
	}

} 
void XMLDocumentParser::BuildAbnormality(XMLNode * mainNode, std::vector<IAbnormality*>& out_abnormalities)
{
	int parsedPerSecond = 0;
	short parsingSpeed = 0;
	long long time = ServerTimer::GetCurrentUTC();
	long long time2 = 0;
	IAbnormality * out_ab = nullptr;
	XMLNodeArgument* arg = nullptr;
	XMLNode* abNode = nullptr;
	for (size_t j = 0; j < mainNode->childNodes.size(); j++)
	{
		if ((time2 = ServerTimer::GetCurrentUTC()) - time > 1)
		{
			time = time2;
			parsingSpeed = parsedPerSecond;
			parsedPerSecond = 0;
		}
		std::cout << "::Parsed <<[" << j << "] abnormalities. Parsing speed ~[" << parsingSpeed / 2 << "] Abnormalities per second." << "\r" << std::flush;
		abNode = mainNode->childNodes[j];
		XMLNodeArgument* arg = nullptr;
		out_ab = new IAbnormality();
		for (size_t i = 0; i < abNode->_arguments.size(); i++)
		{
			if ((arg = abNode->ConsumeArgument("id")))
			{
				out_ab->_id = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = abNode->ConsumeArgument("bySkillCategory")))
			{
				out_ab->_bySkillCategory = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = abNode->ConsumeArgument("infinity")))
			{
				out_ab->_infinity = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = abNode->ConsumeArgument("isBuff")))
			{
				out_ab->_isBuff = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = abNode->ConsumeArgument("isHideOnRefresh")))
			{
				out_ab->_isHideOnRefresh = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = abNode->ConsumeArgument("isShow")))
			{
				out_ab->_isShow = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = abNode->ConsumeArgument("kind")))
			{
				out_ab->_kind = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = abNode->ConsumeArgument("level")))
			{
				out_ab->_level = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = abNode->ConsumeArgument("notCareDeath")))
			{
				out_ab->_notCareDeth = arg->argumentValue == "True" ? true : false;
			}
			else if ((arg = abNode->ConsumeArgument("priority")))
			{
				out_ab->_priority = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = abNode->ConsumeArgument("property")))
			{
				out_ab->_property = atoi(arg->argumentValue.c_str());
			}
			else if ((arg = abNode->ConsumeArgument("time")))
			{
				out_ab->_time = atoi(arg->argumentValue.c_str());
			}

			for (size_t i = 0; i < abNode->childNodes.size(); i++)
			{
				XMLNode * childNode = abNode->ConsumeChildNode("AbnormalityEffect");
				if (childNode)
				{
					XMLNodeArgument* arg1 = nullptr;
					AbnormalityEffect * new_effect = new AbnormalityEffect();
					for (size_t j = 0; j < childNode->_arguments.size(); j++)
					{
						if ((arg1 = childNode->ConsumeArgument("type")))
						{
							new_effect->_type = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("tickInterval")))
						{
							new_effect->_tickInterval = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("value")))
						{
							new_effect->_value = atof(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("tickInterval")))
						{
							new_effect->_tickInterval = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("isEnemyCheck")))
						{
							new_effect->_isEnemyCheck = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("method")))
						{
							new_effect->_method = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("appearEffectId")))
						{
							new_effect->_appearEffectId = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("attackEffectId")))
						{
							new_effect->_attackEffectId = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("overlayEffectId")))
						{
							new_effect->_overlayEffectId = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("damageEffectId")))
						{
							new_effect->_damageEffectId = atoi(arg1->argumentValue.c_str());
						}
						else if ((arg1 = childNode->ConsumeArgument("dissappearEffectId")))
						{
							new_effect->_dissappearEffectId = atoi(arg1->argumentValue.c_str());
						}


						//this it for now
					}

					out_ab->_effects.push_back(new_effect);
				}
			}
		}

		out_abnormalities.push_back(out_ab);
		parsedPerSecond++;
	}


}
void XMLDocumentParser::BuildPassivity(XMLNode * mainNode, std::vector<Passivity*>& out_passivities)
{
	int parsedPerSecond = 0;
	short parsingSpeed = 0;
	long long time = ServerTimer::GetCurrentUTC();
	long long time2 = 0;
	int seconds = 0;
	Passivity* out_p = nullptr;
	XMLNodeArgument* arg = nullptr;
	XMLNode* pasNode = nullptr;
	for (size_t j = 0; j < mainNode->childNodes.size(); j++)
	{
		if ((time2 = ServerTimer::GetCurrentUTC()) - time > 1)
		{
			time = time2;
			parsingSpeed = parsedPerSecond;
			parsedPerSecond = 0;
			seconds += 2;
		}
		std::cout << "::Parsed <<[" << j << "] passivities. Parsing speed ~[" << parsingSpeed / 2 << "] Passivities per second." << "\r" << std::flush;
		pasNode = mainNode->childNodes[j];
		out_p = new Passivity();
		for (size_t i = 0; i < pasNode->_arguments.size(); i++)
		{
			if ((arg = pasNode->ConsumeArgument("id")))
			{
				out_p->_id = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("prob")))
			{
				out_p->_probability = atof((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("type")))
			{
				out_p->_type = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("value")))
			{
				out_p->_value = atof((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("judgmentOnce")))
			{
				out_p->_judgmentOnce = ((const char*)arg->argumentValue.c_str()) == "True" ? 1 : 0;
			}
			else if ((arg = pasNode->ConsumeArgument("kind")))
			{
				out_p->_kind = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("mobSize")))
			{
				out_p->_mobSize = mobSizeDictionary[(const char*)arg->argumentValue.c_str()];
			}
			else if ((arg = pasNode->ConsumeArgument("method")))
			{
				out_p->_method = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("tickInterval")))
			{
				out_p->_tickInterval = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("condition")))
			{
				out_p->_condition = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("abnormalityCategory")))
			{
				out_p->_abnormalityCategory = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("abnormalityKind")))
			{
				out_p->_abnormalityKind = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("conditionValue")))
			{
				out_p->_conditionValue = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("conditionCategory")))
			{
				out_p->_conditionCategory = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("prevPassivityId")))
			{
				out_p->_prevPassivityId = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("passivityChangeId")))
			{
				out_p->_passivityChangeId = atoi((const char*)arg->argumentValue.c_str());
			}
			else if ((arg = pasNode->ConsumeArgument("passivityChangeTime")))
			{
				out_p->_passivityChangeTime = atoi((const char*)arg->argumentValue.c_str());
			}
		}
		out_passivities.push_back(out_p);
		parsedPerSecond++;
	}
}
void XMLDocumentParser::BuildEquipmentSetData(XMLNode * eqNode, std::map<int, EquipmentSetData*>& out_equipmentSets)
{
	XMLNodeArgument* arg = nullptr;
	XMLNode* subNode = nullptr;
	int equipmentSetId = 0;
	EquipmentSetData * newData = new EquipmentSetData;
	memset(newData, 0, sizeof EquipmentSetData);

	if ((arg = eqNode->ConsumeArgument("id")))
	{
		equipmentSetId = atoi(arg->argumentValue.c_str());
	}

	for (size_t i = 0; i < eqNode->childNodes.size(); i++)
	{
		if ((subNode = eqNode->childNodes[i]) && subNode->tagName == "Effect")
		{
			EquipmentSetEffect* newEff = new EquipmentSetEffect;
			memset(newEff, 0, sizeof EquipmentSetEffect);
			for (size_t l = 0; l < subNode->_arguments.size(); l++)
			{
				if ((arg = subNode->ConsumeArgument("countOfEquipment")))
				{
					newEff->countOfEquipment = atoi(arg->argumentValue.c_str());
				}
				else if ((arg = subNode->ConsumeArgument("passiveList")))
				{
					std::string chuck;
					for (size_t k = 0; k < arg->argumentValue.size(); k++)
					{
						if (arg->argumentValue[k] == ',')
						{
							newEff->_passivities.push_back(atoi(chuck.c_str()));
							continue;
						}
						else if (k == arg->argumentValue.size() - 1)
						{
							newEff->_passivities.push_back(atoi(chuck.c_str()));
							chuck = "";
							break;
						}
						chuck += arg->argumentValue[k];
					}
				}
			}
			newData->_effects.push_back(newEff);
		}
		else if ((subNode = eqNode->childNodes[i]) && subNode->tagName == "ItemList")
		{
			for (size_t k = 0; k < subNode->childNodes.size(); k++)
			{
				if (subNode->childNodes[k] && subNode->childNodes[k]->tagName == "Item")
				{
					EquipmentSetItem* newItem = new EquipmentSetItem;
					memset(newItem, 0, sizeof EquipmentSetItem);
					for (size_t l = 0; l < subNode->childNodes[k]->_arguments.size(); l++)
					{
						if ((arg = subNode->childNodes[k]->ConsumeArgument("id")))
						{
							std::string chuck;
							for (size_t k = 0; k < arg->argumentValue.size(); k++)
							{
								if (arg->argumentValue[k] == ';')
								{
									newItem->itemsId.push_back(atoi(chuck.c_str()));
									continue;
								}
								else if (k == arg->argumentValue.size() - 1)
								{
									newItem->itemsId.push_back(atoi(chuck.c_str()));
									chuck = "";
									break;
								}
								chuck += arg->argumentValue[k];
							}
						}

						else if ((arg = subNode->childNodes[k]->ConsumeArgument("equipPos")))
						{
							newItem->slotId = atoi(arg->argumentValue.c_str());
						}

						else if ((arg = subNode->childNodes[k]->ConsumeArgument("itemDelegatorName")))
						{
							//need?
						}
					}

					newData->_items.push_back(newItem);
				}
			}
		}
	}
	if (newData)
		out_equipmentSets.insert(std::pair<int, EquipmentSetData*>(equipmentSetId, newData));
}

std::map<std::string, ItemCategory> XMLDocumentParser::itemCategoryDictionary;
std::map<std::string, ItemType>  XMLDocumentParser::itemTypeDictionary;
std::map<std::string, ItemBoundType>  XMLDocumentParser::itemBoundTypeDictionary;
std::map<std::string, EquipmentPart> XMLDocumentParser::equipmentPartDictionary;

std::map<std::string, SkillType> XMLDocumentParser::skillTypeDictionary;
std::map<std::string, PushTarget>	XMLDocumentParser::skillPushTargetDictionary;
std::map<std::string, TargetingAreaType>  XMLDocumentParser::targetingAreaTypeDictionary;
std::map<std::string, TargetingMethod>  XMLDocumentParser::targetingMethodDictionary;
std::map<std::string, TargetingType> XMLDocumentParser::targetingTypeDictionary;
std::map<std::string, AdjustTargetingPos> XMLDocumentParser::adjustTargetingPosDictionary;

std::map<std::string, MobSize> XMLDocumentParser::mobSizeDictionary;
std::map<int, std::string>  XMLDocumentParser::regionsNames;

void XMLDocumentParser::InitItemsDictionary()
{
	itemBoundTypeDictionary.insert(std::pair<std::string, ItemBoundType>("None", BOUND_NONE));
	itemBoundTypeDictionary.insert(std::pair<std::string, ItemBoundType>("Equip", BOUND_EQUIP));
	itemBoundTypeDictionary.insert(std::pair<std::string, ItemBoundType>("Pickup", BOUND_PICK_UP));
	itemBoundTypeDictionary.insert(std::pair<std::string, ItemBoundType>("Loot", BOUND_LOOT));


	itemTypeDictionary.insert(std::pair<std::string, ItemType>("DISPOSAL", ItemType::DISPOSAL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CUSTOM", ItemType::CUSTOM));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("NO_COMBAT", ItemType::NO_COMBAT));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CHANGE_NAME", ItemType::CHANGE_NAME));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_ACCESSORY", ItemType::EQUIP_ACCESSORY));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("SKILLBOOK", ItemType::SKILLBOOK));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("DUNGEON_COIN", ItemType::DUNGEON_COIN));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CURSED_DREAM_PIECE", ItemType::CURSED_DREAM_PIECE));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("BLESSED_DREAM_PIECE", ItemType::BLESSED_DREAM_PIECE));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("UNIDENTIFY_SCROLL", ItemType::UNIDENTIFY_SCROLL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CURSE_REMOVE_SCROLL", ItemType::CURSE_REMOVE_SCROLL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("IDENTIFY_SCROLL", ItemType::IDENTIFY_SCROLL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CHANGE_COLOR_ITEM", ItemType::CHANGE_COLOR_ITEM));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("MIX_DISPOSAL", ItemType::MIX_DISPOSAL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CHANGE_RACE", ItemType::CHANGE_RACE));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CHANGE_GENDER", ItemType::CHANGE_GENDER));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CHANGE_LOOKS", ItemType::CHANGE_LOOKS));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_WEAPON", ItemType::EQUIP_WEAPON));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("START_GUILD_WAR", ItemType::START_GUILD_WAR));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("GIVE_UP_GUILD_WAR", ItemType::GIVE_UP_GUILD_WAR));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CHRONO_SCROLL", ItemType::CHRONO_SCROLL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("DUNGEON_RESET_SCROLL", ItemType::DUNGEON_RESET_SCROLL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("RESET_SCROLL", ItemType::RESET_SCROLL));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("IMMEDIATE", ItemType::IMMEDIATE));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_ARMOR_BODY", ItemType::EQUIP_ARMOR_BODY));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_ARMOR_ARM", ItemType::EQUIP_ARMOR_ARM));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_ARMOR_LEG", ItemType::EQUIP_ARMOR_LEG));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("DOCUMENT", ItemType::DOCUMENT));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CREST_RESET", ItemType::CREST_RESET));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CREST_POINT", ItemType::CREST_POINT));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("CREST", ItemType::CREST));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("RECIPE", ItemType::RECIPE));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_STYLE_ACCESSORY", ItemType::EQUIP_STYLE_ACCESSORY));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_STYLE_WEAPON", ItemType::EQUIP_STYLE_WEAPON));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_STYLE_BACK", ItemType::EQUIP_STYLE_BACK));
	itemTypeDictionary.insert(std::pair<std::string, ItemType>("EQUIP_STYLE_BODY", ItemType::EQUIP_STYLE_BODY));
	//todo add ItemType to dictionary

	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("comabt", combat));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("magical", magical));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("custormaize", custormaize));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("pkitem", pkitem));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("medal", medal));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("service", service));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("earring", earring));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("necklace", necklace));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("ring", ring));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("skillbook", skillbook));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("token", token));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("order", order));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("etc", etc));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("petAdult", petAdult));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("petOrb", petOrb));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("dyeItem", dyeItem));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("dyeRaw", dyeRaw));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("dyeRecipe", dyeRecipe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("dual", dual));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("lance", lance));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("twohand", twohand));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("axe", axe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("circle", circle));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("bow", bow));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("staff", staff));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("rod", rod));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("gauntlet", gauntlet));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("shuriken", shuriken));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("blaster", blaster));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("accessoryHair", accessoryHair));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("weaponMaterial", weaponMaterial));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("armorMaterial", armorMaterial));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("keyItem", keyItem));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("generalMaterial", generalMaterial));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("fiber", fiber));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("metal", metal));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("alchemy", alchemy));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("leather", leather));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("alchemyMaterial", alchemyMaterial));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("fireworkMaterial", fireworkMaterial));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("weaponComponent", weaponComponent));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("armorComponent", armorComponent));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("bodyMail", bodyMail));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("handMail", handMail));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("feetMail", feetMail));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("bodyLeather", bodyLeather));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("handLeather", handLeather));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("feetLeather", feetLeather));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("bodyRobe", bodyRobe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("handRobe", handRobe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("feetRobe", feetRobe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("recipe", recipe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("quest", quest));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("document", document));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("crestPoint", crestPoint));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("crest", crest));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("charm", charm));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("extractRecipe", extractRecipe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("accessoryFace", accessoryFace));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_face", style_face));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_hair", style_hair));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_dual", style_dual));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_lance", style_lance));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_twohand", style_twohand));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_axe", style_axe));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_circle", style_circle));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_bow", style_bow));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_staff", style_staff));
	itemCategoryDictionary.insert(std::pair<std::string, ItemCategory>("style_rod", style_rod));


	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("BELT", E_BELT));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("FINGER", E_FINGER));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("FEET", E_FEET));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("HAND", E_HAND));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("BODY", E_BODY));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("UNDERWEAR", E_UNDERWEAR));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("EAR", E_EAR));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("BROOCH", E_BROOCH));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("NECK", E_NECK));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("ACCESSORYFACE", E_ACCESSORYFACE));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("ACCESSORYHAIR", E_ACCESSORYHAIR));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("STYLE_FACE", E_STYLE_FACE));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("STYLE_BODY", E_STYLE_BODY));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("STYLE_WEAPON", E_STYLE_WEAPON));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("STYLE_BACK", E_STYLE_BACK));
	equipmentPartDictionary.insert(std::pair<std::string, EquipmentPart>("STYLE_HAIR", E_STYLE_HAIR));
}

void XMLDocumentParser::InitPassivityDictionary()
{
	mobSizeDictionary.insert(std::pair<std::string, MobSize>("Small", Small));
	mobSizeDictionary.insert(std::pair<std::string, MobSize>("Medium", Medium));
	mobSizeDictionary.insert(std::pair<std::string, MobSize>("Large", Large));
	mobSizeDictionary.insert(std::pair<std::string, MobSize>("All", All));
	mobSizeDictionary.insert(std::pair<std::string, MobSize>("Player", TPlayer));
	//all
}

void XMLDocumentParser::InitSkillsDictionary()
{
	skillPushTargetDictionary.insert(std::pair<std::string, PushTarget>("Pass", PushTarget::Pass));
	skillPushTargetDictionary.insert(std::pair<std::string, PushTarget>("Stop", PushTarget::Stop));
	skillPushTargetDictionary.insert(std::pair<std::string, PushTarget>("Push", PushTarget::Push));

	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Normal", SkillType::Normal));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Instance", SkillType::Instance));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("MovingSkill", SkillType::MovingSkill));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("MovingCharge", SkillType::MovingCharge));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Projectile", SkillType::Projectile));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Evade", SkillType::Evade));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Combo", SkillType::Combo));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("ComboInstance", SkillType::ComboInstance));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("NoTimeline", SkillType::NoTimeline));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Stand", SkillType::Stand));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Switch", SkillType::Switch));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Defence", SkillType::Defence));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Firewood", SkillType::Firewood));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Summon", SkillType::Summon));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Gamble", SkillType::Gamble));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Charm", SkillType::Charm));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Rebirth", SkillType::Rebirth));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Eventseed", SkillType::Eventseed));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("CommanderNormal", SkillType::CommanderNormal));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("CommanderScan", SkillType::CommanderScan));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Mount", SkillType::Mount));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Drain", SkillType::Drain));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("DrainBack", SkillType::DrainBack));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Userslug", SkillType::Userslug));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("ShortTel", SkillType::ShortTel));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Capture", SkillType::Capture));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Connect", SkillType::Connect));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("Dash", SkillType::Dash));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("CatchBack", SkillType::CatchBack));
	skillTypeDictionary.insert(std::pair<std::string, SkillType>("ChaseEffect", SkillType::ChaseEffect));

	adjustTargetingPosDictionary.insert(std::pair < std::string, AdjustTargetingPos>("notUse", notUse));
}

XMLDocumentParser::XMLNode::XMLNode()
{
	parentNode = 0;
	consumed = 0;
}

XMLDocumentParser::XMLNode::~XMLNode()
{
	//clean arguments
	for (size_t i = 0; i < _arguments.size(); i++)
	{
		if (_arguments[i])
		{
			delete _arguments[i];
			_arguments[i] = 0;
		}
	}
	_arguments.clear();

	//clean childNodes
	for (size_t i = 0; i < childNodes.size(); i++)
	{
		if (childNodes[i])
		{
			delete childNodes[i];
			childNodes[i] = 0;
		}
	}
	childNodes.clear();

	parentNode = 0;
}

XMLDocumentParser::XMLNodeArgument * XMLDocumentParser::XMLNode::ConsumeArgument(const char * argumentName)
{
	XMLNodeArgument * out = nullptr;

	for (size_t i = 0; i < _arguments.size(); i++)
	{
		if (_arguments[i] && _arguments[i]->argumentName == argumentName && (_arguments[i]->consumed == 0x00))
		{
			_arguments[i]->consumed = 0x01;
			out = _arguments[i];
			break;
		}
	}

	return out;
}

XMLDocumentParser::XMLNode * XMLDocumentParser::XMLNode::ConsumeChildNode(const char * tagName)
{
	XMLNode *  out = nullptr;

	for (size_t i = 0; i < childNodes.size(); i++)
	{
		if (childNodes[i] && childNodes[i]->tagName == tagName && consumed == 0)
		{
			childNodes[i]->consumed = 1;
			out = childNodes[i];
			break;
		}
	}

	return out;
}


XMLDocumentParser::XMLNodeArgument::XMLNodeArgument()
{
	argumentName = argumentValue = "";
	consumed = 0;
}

XMLDocumentParser::XMLNodeArgument::~XMLNodeArgument()
{
	argumentName.clear();
	argumentValue.clear();
}
