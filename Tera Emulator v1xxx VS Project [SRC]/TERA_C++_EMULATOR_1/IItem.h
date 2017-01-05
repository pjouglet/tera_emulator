#ifndef IITEM_H
#define IITEM_H
#include <string>
#include <vector>

#include "Crypt\data_type.hpp"
#include "PlayerEnums.h"
#include "ItemEnum.h"
#include "Entity.h"

class IItem : public Entity
{
public:
	IItem();
	~IItem();
	int operator ()(int);

	int
		_minAtk,
		_maxAtk,
		_impact,
		_def,
		_id,
		_sortingNumber,
		_itemLevel,
		_requiredLevel,
		_passivityLinkG,
		_maxStack,
		_rank,
		_coolTimeGroup,
		_slotLimit,
		_buyPrice,
		_sellPrice,
		_countOfSlot,
		_coolTime;


	EquipmentPart _part;
	ItemType _combatItemType;
	ItemCategory _category;
	ItemType _type;
	ItemType _requiredEquipmentType;
	ItemGrade _itemGrade;
	ItemRareGrade _rareGrade;
	ItemBoundType _bountType;

	float
		_masterpieceRate;

	byte
		_changeColorEnable,
		_changeLook,
		_tradable,
		_warehouseStoreable,
		_destroyable,
		_dismantlable,
		_sellable,
		_obtainable,
		_artisanable,
		_useOnlyByGender,
		_useOnlyTerritory,
		_useOnlyByRace,
		_hasBonus,
		_bankStorable,
		_guildBankStorable,
		_useOnlyByClass;

	std::string
		_linkMasterpieceEnchantId,
		_linkCrestId,
		_linkCustomizingId,
		_linkEnchantId,
		_linkEquipmentId,
		_linkLookInfoId,
		_linkPetAdultId,
		_linkPetOrbId,
		_linkMasterpiecePassivityCategoryId,
		_linkPassivityCategoryId,
		_linkPassivityId,
		_requiredClass,
		_name,
		_linkSkillId;


};
#endif
