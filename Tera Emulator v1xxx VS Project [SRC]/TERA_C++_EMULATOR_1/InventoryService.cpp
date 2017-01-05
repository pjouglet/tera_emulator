#include "InventoryService.h"
#include "Client.hpp"
#include "Account.hpp"
#include "Stream.h"
#include "IItem.h"
#include "OpCodesEnum.h"

#include "XMLDocumentParser.h"

#include <fstream>

const bool InventoryService::LoadItems(const char * path)
{
	std::stringstream ss; std::string line; int readType = 1;

	ss << path << "//info.txt";
	std::ifstream file = std::ifstream(ss.str());
	if (!file.is_open())
		return false;
	std::getline(file, line);
	int fileCount = 0;
	sscanf(line.c_str(), "Count = %d", &fileCount);

	

	file.close();
	int itemCountNow = 0; int itemCountOld = 0;
	for (size_t i = 0; i < fileCount; i++)
	{
		itemCountOld = _items.size();
		ss.clear(); ss.str("");
		ss << path << "//ItemData-" << i << ".xml" << '\0'; 
		std::cout << ">Loading [ItemData-" << i << ".xml]...\n";
		if (!XMLDocumentParser::ParseItemsXMLDocument(ss.str().c_str(), _items))
			continue; 
		itemCountNow = _items.size();
	}

	if (!XMLDocumentParser::ParseItemsXMLDocument(".//data//ItemData//ItemData-test.xml", _items))
		return false;

	return true;
}

//Player::PlayerWarehouse * InventoryService::GetStartWarehouse(PlayerClass pClass)
//{
//	Player::PlayerWarehouse * out = new Player::PlayerWarehouse;
//	ZeroMemory(out, sizeof Player::PlayerWarehouse);
//
//	if (pClass == PlayerClass::WARRIOR || pClass == PlayerClass::ARCHER || pClass == PlayerClass::SLAYER || pClass == PlayerClass::REAPER)
//	{
//		out->armor = 15004;
//		out->boots = 15006;
//		out->gloves = 15005;
//		out->weapon = 0;
//	}
//	else if (pClass == PlayerClass::BERSERKER || pClass == PlayerClass::LANCER || pClass == PlayerClass::GUNNER || pClass == PlayerClass::BRAWLER)
//	{
//		out->armor = 15001;
//		out->boots = 15003;
//		out->gloves = 15002;
//		out->weapon = 0;
//	}
//	else if (pClass == PlayerClass::SORCERER || pClass == PlayerClass::PRIEST || pClass == PlayerClass::MYSTIC || pClass == PlayerClass::NINJA)
//	{
//		out->armor = 15007;
//		out->boots = 15009;
//		out->gloves = 15008;
//		out->weapon = 0;
//	}
//
//	switch (pClass)
//	{
//	case PlayerClass::WARRIOR:
//		out->weapon = 10001;
//		break;
//	case PlayerClass::BERSERKER:
//		out->weapon = 10004;
//		break;
//	case PlayerClass::BRAWLER:
//		out->weapon = 82005;
//		break;
//	case PlayerClass::GUNNER:
//		out->weapon = 55005;
//		break;
//	case PlayerClass::PRIEST:
//		out->weapon = 10007;
//		break;
//	case PlayerClass::MYSTIC:
//		out->weapon = 10008;
//		break;
//	case PlayerClass::NINJA:
//		out->weapon = 58171;
//		break;
//	case PlayerClass::LANCER:
//		out->weapon = 10002;
//		break;
//	case PlayerClass::SLAYER:
//		out->weapon = 10003;
//		break;
//	case PlayerClass::SORCERER:
//		out->weapon = 10005;
//		break;
//	case PlayerClass::ARCHER:
//		out->weapon = 10006;
//		break;
//	case PlayerClass::REAPER:
//		out->weapon = 80396;
//		break;
//	}
//
//	return out;
//}


IItem * InventoryService::ResolveItem(int id)
{
	IItem* out = nullptr;

	for (size_t i = 0; i < _items.size(); i++)
	{
		if (_items[i] && _items[i]->_id == id)
		{
			out = _items[i];
			break;
		}
	}

	return out;
}

void InventoryService::Release()
{
	for (size_t i = 0; i < _items.size(); i++)
	{
		if (_items[i])
		{
			delete _items[i];
			_items[i] = 0;
		}
	}
	_items.clear();
}

void InventoryService::ResolveInventory(std::vector<int>& ids, std::vector<IItem*>& out_items)
{
	for (size_t i = 0; i < ids.size(); i++)
	{
		IItem * j = 0;
		if (j = ResolveItem(ids[i]))
		{
			
		}
	}

}

std::vector<IItem*> InventoryService::_items;
