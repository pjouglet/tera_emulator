#pragma once

#define XML_DEBUG 1

#include <string>
#include <vector>
#include <fstream>
#include "Crypt\data_type.hpp"
#include <map>
#include "ServerUtils.hpp"
#include "IItem.h"
#include "Skill.h"
#include "PlayerEnums.h"

class IAbnormality; class Passivity; class Area; class EquipmentSetData;
class XMLDocumentParser
{
public:
	class XMLNodeArgument
	{
	public:
		XMLNodeArgument();
		~XMLNodeArgument();
		std::string argumentName;
		std::string argumentValue;
		byte	consumed;
	};
	class XMLNode
	{
	public:
		XMLNode();
		~XMLNode();
		XMLNodeArgument * ConsumeArgument(const char * argumentName);
		std::vector<XMLNodeArgument * > _arguments;
		XMLNode* ConsumeChildNode(const char* tagName);

		std::string tagName;
		XMLNode* parentNode;
		std::vector< XMLNode*> childNodes;
		byte consumed;
	};
public:
	static const bool ParseAreaXMLDocument(const char* fileName, std::vector<Area*>& out_items);
	static const bool ParseItemsXMLDocument(const char* fileName, std::vector<IItem*>& out_items);
	static const bool ParseSkillXMLDocument(const char* fileName, std::vector<Skill*>& out_skills);
	static const bool ParseAbnormalityXMLDocument(const char* fileName, std::vector<IAbnormality*>& out_abnormalities);
	static const bool ParsePassivityXMLDocument(const char* fileName, std::vector<Passivity*>& out_passivities);
	static const bool ParseEquipmentSetXMLDocument(const char * fileName, std::map<int, EquipmentSetData*>& out_equipmentSets);
	static const bool ParseRegionStrSheetXMLDocument(const char* fileName);
private:
	static const byte ParseXMLDocument(std::vector<XMLNode*>& out_nodes, const char* fileName);
	static int GetNode(char* buffer, int mainCursor, XMLNode* outNode);


	static void BuildRegionName(XMLNode* node);

	static void BuildAreas(XMLNode* mainNode, std::vector<Area*>& out_areas);
	static void BuildItems(XMLNode* node, std::vector<IItem*> & out_items);
	static void BuildSkill(XMLNode* skillNode, std::vector<Skill*> &out_skills);
	static void BuildAbnormality(XMLNode * abNode, std::vector<IAbnormality*>& out_abnormalities);
	static void BuildPassivity(XMLNode *pasNode, std::vector<Passivity*>& out_passivities);
	static void BuildEquipmentSetData(XMLNode *eqNode, std::map<int, EquipmentSetData*>& out_equipmentSets);

	static void InitItemsDictionary();
	static void InitPassivityDictionary();
	static void InitSkillsDictionary();
	static std::map<std::string, ItemCategory> itemCategoryDictionary;
	static std::map<std::string, ItemType> itemTypeDictionary;
	static std::map<std::string, ItemBoundType> itemBoundTypeDictionary;
	static std::map<std::string, EquipmentPart> equipmentPartDictionary;

	static std::map<std::string, SkillType> skillTypeDictionary;
	static std::map<std::string, PushTarget> skillPushTargetDictionary;
	static std::map<std::string, TargetingAreaType> targetingAreaTypeDictionary;
	static std::map<std::string, TargetingType> targetingTypeDictionary;
	static std::map<std::string, TargetingMethod> targetingMethodDictionary;
	static std::map<std::string, AdjustTargetingPos> adjustTargetingPosDictionary;

	static std::map<std::string, MobSize> mobSizeDictionary;
	static std::map<int, std::string> regionsNames;
};

