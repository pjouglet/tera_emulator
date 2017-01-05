#ifndef INVENTORY_H
#define INVENTORY_H

#ifndef byte
#define byte unsigned char
#endif

#include <vector>
#include <mutex>
#include "InventorySlot.h"

#ifndef INVENTORY_MAX_ROWS
#define INVENTORY_MAX_ROWS 9
#endif

#ifndef INVENTORY_START_SLOT_COUNT
#define INVENTORY_START_SLOT_COUNT (int)(5 * 8)
#endif

class IItem; class Player; class Client; class Stream;

class Inventory
{
	friend class PlayerService;
public:
	Inventory(Player * owner);
	~Inventory();

	const bool Initialize(short slotCount = INVENTORY_START_SLOT_COUNT, int maxPlayerGold = -1);


	const bool ExpandInventory(byte rowCount);
	const bool ClearInventory(Client * caller);

	Stream* GetItemsRAW();

	const bool AddGold(long long gold);
	const bool TakeGold(long long gold);
	const bool IsFull();
	void ClearGold();
	void Sort();
	

	InventorySlot* operator[] (int i);
	InventorySlot* operator[] (long long i);
	void operator <<(int itemId);

	void SendInventory(Client * client, byte show,bool broadcast = true);
	
	static void  BuildItemInfoEx(InventorySlot * slot,int itemId);
	static void GetStarterInventory(Player* p);

	unsigned short
		_slotCount,
		_equipedItemsCount,
		_itemCount;

	unsigned int
		_profileItemLevel,
		_itemLevel;

	unsigned long long
		_gold,
		_maxGold;

	void Lock();
	void Unlock();
	void RecalculateLevels();
private:
	void RedoSlotsIds();


	std::mutex _invLock;
	Player * _owner;
	std::vector<InventorySlot*> _slots;
};

#endif
