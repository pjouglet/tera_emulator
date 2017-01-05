#include "RShowItemToolTipEx.h"
#include "Inventory.h"
#include "Passivity.h"
#include "IItem.h"

RShowItemToolTipEx::RShowItemToolTipEx() : SendPacket(C_SHOW_ITEM_TOOLTIP_EX)
{
}

void RShowItemToolTipEx::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player * p = caller->GetSelectedPlayer();
	if (!p || !p->_inventory)
		return;
	Inventory * inv = p->_inventory;

	short nameOffset = data->ReadInt16();
	short unk = data->ReadInt16();
	short unk2 = data->ReadInt16();

	long long itemUID = data->ReadInt32();

	data->_pos = nameOffset;
	std::string userName = data->ReadUTF16StringBigEdianToASCII();

	InventorySlot * slot = (*inv)[itemUID];
	if (!slot)
		return;

	data->Clear();
	data->WriteInt16(0);
	data->WriteInt16(S_SHOW_ITEM_TOOLTIP);

	data->WriteInt16(slot->_info->_hasCrystals);
	short crystalsOffset = data->NextPos();

	data->WriteInt16(slot->_info->_passivities.size());
	short passivitiesOffset = data->NextPos();

	short crafterOffset = data->NextPos();
	short soulbindOffset = data->NextPos();

	data->WriteInt32(50); //unk
	data->WriteInt64(itemUID);
	data->WriteInt32(slot->_info->_itemId);
	data->WriteInt64(itemUID);

	data->WriteInt32(p->_lobbyId);
	data->WriteInt32(23);
	data->WriteInt32(slot->_id);

	data->WriteInt32(9); //unk
	data->WriteInt32(23); //unk
	data->WriteInt32(slot->_info->_stackCount); //unk
	data->WriteInt32(slot->_info->_enchantLevel); //enchant

	data->WriteInt32(1); //unk

	data->WriteByte(slot->_info->_isBinded ? 1 : 0);

	data->WriteByte(1);
	data->WriteByte(1);
	data->WriteByte(1);
	data->WriteInt32(3434); //unk
	data->WriteFloat(23); //unk

	data->WriteInt32(12);
	data->WriteInt32(13);
	data->WriteInt32(14);
	data->WriteInt32(15);
	data->WriteInt32(16);
	data->WriteInt32(17);
	data->WriteInt32(18);
	data->WriteInt32(19);
	data->WriteInt32(10);
	
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	data->WriteInt32(1);
	
	data->WriteInt32(1);
	data->WriteInt32(1);

	data->WriteInt32(5511);
	data->WriteInt32(5511);
	data->WriteInt32(5511);
	data->WriteInt32(5511);
	data->WriteInt32(5511);
	data->WriteInt32(5511);//31

	
	

	data->WriteByte(3);

	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE
	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE
	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE
	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE
	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE
	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE
	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE
	data->WriteInt64(0xFEFEFEFEFEFEFEFE);			 //0xFEFEFEFEFEFEFEFE

	data->WriteInt32(slot->_info->_isEnigmatic); //enigmatic
	data->WriteByte(slot->_info->_isMasterworked); //masterworked?
	
	data->WriteFloat(565656);
	
	data->WriteByte(1); //comapre stats

	data->WriteInt32(1000);     //attack base range 2
	data->WriteInt32(1001);	    //total when equiped base defense
	data->WriteInt32(1002);	    //total when equiped base impact
	data->WriteInt32(1003);	    //total when equiped base balance

	data->WriteFloat(1004);	    //total when equiped base crifactor
	data->WriteFloat(1005);	    //total when equiped base crit resist factor
	data->WriteFloat(1006);	    //total when equiped base crit power

	data->WriteInt32(1007);	    //total when equiped base impact factor
	data->WriteInt32(1008);	    //total when equiped base balance factor
	data->WriteInt32(1009);	    //total when equiped base attackSpeed
	data->WriteInt32(1010);	    //total when equiped base movementSpeed

	data->WriteFloat(1011);	    //total when equiped base weakening effect (green)
	data->WriteFloat(1012);	    //total when equiped base periodic damage (purple)
	data->WriteFloat(1013);	    //total when equiped base stun resist

	data->WriteInt32(1021);  //attack add range 2
	data->WriteInt32(1022);   //additional defense
	data->WriteInt32(1023);   //additional impact
	data->WriteInt32(1024);   //additional balance

	data->WriteFloat(1025);	  //additional crifactor
	data->WriteFloat(1026);	  //additional crit resist factor
	data->WriteFloat(1027);	  //additional crit power 

	data->WriteInt32(1028);	  //additional impact factor
	data->WriteInt32(1029);	  //additional balance factor
	data->WriteInt32(1031);	  //additional attack speed
	data->WriteInt32(1032);	  //additional movement speed

	data->WriteFloat(1033);	  //additional weakening (green)
	data->WriteFloat(1034);	  //additional periodic (purple)
	data->WriteFloat(1035);	  //additional stun

	data->WriteInt32(1036); //attack base range 1
	data->WriteInt32(1037); //attack additional range 1
	
	data->WriteInt32(0);
	data->WriteInt32(0); //add ilv + base ilv??

	data->WriteByte(0);
	data->WriteByte(0);
	data->WriteByte(0);
	data->WriteByte(0);
	
	data->WriteInt64(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);

	data->WriteInt32(slot->_info->_item->_itemLevel/ 65);	  //ilv?
	data->WriteInt32(p->_inventory->_itemLevel);	  //ilv?
	data->WriteInt32(p->_inventory->_profileItemLevel);	  //ilv?

	data->WriteInt32(0);

	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt64(0);
	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt32(45);//feedstock count

	data->WriteInt32(0); 
	data->WriteInt32(0);
	data->WriteInt32(0);

	data->WriteInt32(0);
	data->WriteInt32(0);
	data->WriteInt16(0);

	data->WritePos(crafterOffset);
	data->WriteInt16(0);

	data->WritePos(soulbindOffset);
	data->WriteInt16(0);

	for (byte i = 0; i < slot->_info->_hasCrystals; i++)
	{
		data->WritePos(crystalsOffset);
		data->WriteInt16(data->_pos);
		crystalsOffset = data->NextPos();
		data->WriteInt32(slot->_info->_crystals[i]);
	}

	for (size_t i = 0; i < slot->_info->_passivities.size(); i++)
	{
		data->WritePos(passivitiesOffset);
		data->WriteInt16(data->_pos);
		passivitiesOffset = data->NextPos();

		data->WriteInt32(slot->_info->_passivities[i]->_id);
	}

	data->WritePos(0);
	caller->Send(data);
}
