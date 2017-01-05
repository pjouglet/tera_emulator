#pragma once

#include "Player.hpp"

#include <vector>

class Client; class Account; class IItem;

class InventoryService
{
public:
	static const bool LoadItems(const char* file = "data//items.bin");

	
	static void ResolveInventory(std::vector<int> & _ids, std::vector<IItem*> & out_items);
	static IItem * ResolveItem(int id);
	static void Release();
	
	static std::vector<IItem*> _items;
};
			
//  0304CEBE 06003B00 7C62AC0F 00800000
//  00000000 00000000 00010028 00000001
//  00000001 00000000 00000000 00000000
//  00000000 00000000 0000003B 00DC0000
//  000000DA 00112700 00D3B581 31000000
//  00015037 00000000 00010000 00000000
//  00010000 00000000 001E0000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000005 00000005 00000005
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  FFFFFFFF 00000000 00000000 DC007D01
//  00000000 7B019C3A 0000D4B5 81310000
//  00000150 37000000 00000300 00000000
//  00000100 00000000 00001E00 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 01000000 01000000
//  01000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00FFFFFF FF000000 00000000 007D011E
//  02000000 001C029D 3A0000D5 B5813100
//  00000001 50370000 00000004 00000000
//  00000001 00000000 0000001E 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00010000 00010000
//  00010000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  0000FFFF FFFF0000 00000000 00001E02
//  BF020000 0000BD02 9E3A0000 D6B58131
//  00000000 01503700 00000000 05000000
//  00000000 01000000 00000000 1E000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000100 00000100
//  00000100 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  000000FF FFFFFF00 00000000 000000BF
//  02600300 0000005E 03701700 00D7B581
//  31000000 00015037 00000000 00280000
//  00000000 00140000 00000000 001E0000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 FFFFFFFF 00000000 00000000
//  60030000 00000000 FF038017 0000D8B5
//  81310000 00000150 37000000 00002900
//  00000000 00001400 00000000 00001E00
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00000000 00000000 00000000
//  00000000 00FFFFFF FF000000 00000000
//  000000

