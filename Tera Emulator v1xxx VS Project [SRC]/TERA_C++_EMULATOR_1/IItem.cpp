#include "IItem.h"



IItem::IItem() :Entity()
{
	_sellPrice = _id = _itemLevel = _requiredLevel = _maxStack = _rank = _coolTime = _coolTimeGroup = _slotLimit = _sortingNumber = _buyPrice = 0;
	_linkCrestId = _linkCustomizingId = _linkEnchantId = _linkEquipmentId = _linkLookInfoId = _linkMasterpieceEnchantId = _linkMasterpiecePassivityCategoryId = _linkPassivityCategoryId = _linkPassivityId = _linkPetAdultId
		= _linkPetOrbId = _linkSkillId = "";
}


IItem::~IItem()
{
	
}

int IItem::operator()(int)
{
	return _id;
}


