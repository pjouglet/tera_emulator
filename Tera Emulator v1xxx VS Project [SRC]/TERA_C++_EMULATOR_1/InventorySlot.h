#ifndef INVENTORY_SLOT_H
#define INVENTORY_SLOT_H

#include <vector>

#ifndef byte
#define byte unsigned char
#endif

class IItem; class Player; class SLOT_INFO;
class InventorySlot
{
public:
	InventorySlot(int id);
	~InventorySlot();
	int
		_id;
	byte
		_isEmpty;

	SLOT_INFO * _info;

	const bool ClearSlot();
	const bool operator << (IItem * item); //insert item intoSlot
	const bool operator << (SLOT_INFO * info);
	const bool operator >> (InventorySlot * slot);
	const bool operator ^ (InventorySlot * slot);// interchange
	operator int();
};

class Passivity;
class SLOT_INFO
{
public:
	SLOT_INFO();
	SLOT_INFO(int itemid, int stackCount, int* crystals, byte crystalCount, IItem* item, byte enchantLevel, int binderEI, int crafterEI);

	void Clear();

	int
		_itemId,
		_stackCount,
		_crystals[4],
		_binderEntityId,
		_crafterEntityId;

	IItem *
		_item;

	byte
		_hasCrystals,
		_isBinded,
		_enchantLevel,
		_isMasterworked,
		_isEnigmatic,
		_isAwakened,
		_isCrafted;

	std::vector<Passivity*> _passivities;
};



#endif