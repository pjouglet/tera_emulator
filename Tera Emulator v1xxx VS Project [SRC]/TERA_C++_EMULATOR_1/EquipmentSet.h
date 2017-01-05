#pragma once

#include <map>
#include <vector>

struct EquipmentSetEffect
{
	int countOfEquipment;
	std::vector<int> _passivities;
};
struct EquipmentSetItem
{
	int slotId;
	std::vector<int> itemsId;
};

class EquipmentSetData
{
public:
	EquipmentSetData();
	~EquipmentSetData();


	std::vector<EquipmentSetEffect*> _effects;
	std::vector<EquipmentSetItem *> _items;
};

class EquipmentSet
{
public:
	static const bool LoadEquipmentSets(std::string fileName);

	static EquipmentSetData* GetEquipmentSet(int equipmentSetId);
	static const unsigned int GetCount();
	static void Release();
private:
	static std::map<int, EquipmentSetData*> _equipmentSets;
};

