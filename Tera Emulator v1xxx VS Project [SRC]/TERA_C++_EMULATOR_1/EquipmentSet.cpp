#include "EquipmentSet.h"
#include "XMLDocumentParser.h"

const bool EquipmentSet::LoadEquipmentSets(std::string fileName)
{
	if (!XMLDocumentParser::ParseEquipmentSetXMLDocument(fileName.c_str(), _equipmentSets))
	{
		for (auto i = _equipmentSets.begin(); i != _equipmentSets.end(); ++i)
		{
			if ((*i).second)
			{
				delete (*i).second;
				(*i).second = nullptr;
			}
		}
		return false;
	}
	return true;
}

EquipmentSetData * EquipmentSet::GetEquipmentSet(int equipmentSetId)
{
	return _equipmentSets[equipmentSetId];
}

const unsigned int EquipmentSet::GetCount()
{
	return _equipmentSets.size();
}

void EquipmentSet::Release()
{
	for (auto i = _equipmentSets.begin(); i != _equipmentSets.end(); ++i)
	{
		if ((*i).second)
		{
			for (size_t k = 0; k < (*i).second->_effects.size(); k++)
			{
				if ((*i).second->_effects[k])
				{
					(*i).second->_effects[k]->_passivities.clear();
					delete (*i).second->_effects[k];
					(*i).second->_effects[k] = nullptr;
				}
			}
			(*i).second->_effects.clear();

			for (size_t k = 0; k < (*i).second->_items.size(); k++)
			{
				if ((*i).second->_items[k])
				{
					(*i).second->_items[k]->itemsId.clear();
					delete (*i).second->_items[k];
					(*i).second->_items[k] = nullptr;
				}
			}
			(*i).second->_items.clear();

			delete (*i).second;
			(*i).second = nullptr;

		}
	}
	_equipmentSets.clear();
}

std::map<int, EquipmentSetData*>  EquipmentSet::_equipmentSets;

EquipmentSetData::EquipmentSetData()
{

}
EquipmentSetData::~EquipmentSetData()
{
	for (size_t i = 0; i < _items.size(); i++)
	{
		if (_items[i])
		{
			_items[i]->itemsId.clear();
			delete _items[i];
			_items[i] = nullptr;
		}
	}
	_items.clear();

	for (size_t i = 0; i < _effects.size(); i++)
	{
		if (_effects[i])
		{
			_effects[i]->_passivities.clear();
			delete _effects[i];
			_effects[i] = nullptr;
		}
	}
	_effects.clear();
}
