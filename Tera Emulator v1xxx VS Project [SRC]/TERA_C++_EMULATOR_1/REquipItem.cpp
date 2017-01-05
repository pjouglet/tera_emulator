#include "REquipItem.h"
#include "Inventory.h"
#include "InventorySlot.h"
#include "IItem.h"
#include "ItemEnum.h"
#include "MessagingSystem.h"
#include "StatsService.h"


REquipItem::REquipItem() : SendPacket(C_EQUIP_ITEM)
{

}
void REquipItem::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;

	int playerEntityId = data->ReadInt32();
	int playerSubId = data->ReadInt32();

	int slotId = data->ReadInt32();

	p->_inventory->Lock();
	InventorySlot *  slot = (*p->_inventory)[slotId];
	if (slot && slot->_isEmpty == 0)
	{
		if (slot->_info->_isBinded == 1 && slot->_info->_binderEntityId != p->_entityId)
		{
			MessagingSystem::SendSystemMessage(caller, "That item is not bound to you!");
			return;
		}

		//add level restriction and more

		ItemType type = slot->_info->_item->_type;
		switch (type)
		{

		case EQUIP_ACCESSORY:
			if (slot->_info->_item->_category == necklace)
			{
				(*(*p->_inventory)[PROFILE_NECKLACE]) ^ slot;
			}
			else if (slot->_info->_item->_category == earring)
			{
				if ((*p->_inventory)[PROFILE_EARRING_L]->_isEmpty == 1)
				{
					(*(*p->_inventory)[PROFILE_EARRING_L]) ^ slot;
				}
				else if ((*p->_inventory)[PROFILE_EARRING_R]->_isEmpty == 1)
				{
					(*(*p->_inventory)[PROFILE_EARRING_R]) ^ slot;
				}
				else
				{
					(*(*p->_inventory)[PROFILE_EARRING_L]) ^ slot;
				}
			}
			else if (slot->_info->_item->_category == ring)
			{
				if ((*p->_inventory)[PROFILE_RING_L]->_isEmpty == 1)
				{
					(*(*p->_inventory)[PROFILE_RING_L]) ^ slot;
				}
				else if ((*p->_inventory)[PROFILE_RING_R]->_isEmpty == 1)
				{
					(*(*p->_inventory)[PROFILE_RING_R]) ^ slot;
				}
				else
				{
					(*(*p->_inventory)[PROFILE_RING_L]) ^ slot;
				}
			}
			else if (slot->_info->_item->_category == brooch)
			{
				(*(*p->_inventory)[PROFILE_BROOCH]) ^ slot;
			}
			else if (slot->_info->_item->_category == belt)
			{
				(*(*p->_inventory)[PROFILE_BELT]) ^ slot;
			}
			break;
		case EQUIP_WEAPON:
			(*(*p->_inventory)[PROFILE_WEAPON]) ^ slot;
			MessagingSystem::SendSystemMessage(caller, "Switched");
			break;
		case EQUIP_ARMOR_BODY:
			(*(*p->_inventory)[PROFILE_ARMOR]) ^ slot;
			break;
		case EQUIP_ARMOR_ARM:
			(*(*p->_inventory)[PROFILE_GLOVES]) ^ slot;
			break;
		case EQUIP_ARMOR_LEG:
			(*(*p->_inventory)[PROFILE_BOOTS]) ^ slot;
			break;
		case EQUIP_STYLE_ACCESSORY:
			if (slot->_info->_item->_category == style_face)
			{
				(*(*p->_inventory)[PROFILE_SKIN_FACE]) ^ slot;
			}
			else if (slot->_info->_item->_category == style_hair)
			{
				(*(*p->_inventory)[PROFILE_SKIN_HEAD]) ^ slot;
			}
			break;
		case EQUIP_STYLE_WEAPON:
			(*(*p->_inventory)[PROFILE_SKIN_WEAPON]) ^ slot;
			break;
		case EQUIP_STYLE_BODY:
			(*(*p->_inventory)[PROFILE_SKIN_BODY]) ^ slot;
			break;
		case EQUIP_STYLE_BACK:
			(*(*p->_inventory)[PROFILE_SKIN_BACK]) ^ slot;
			break;
		default:
			break;
		}

	

	}

	p->_inventory->RecalculateLevels();
	p->_stats.Refresh();
	p->_inventory->Unlock();

	p->_inventory->SendInventory(caller, 0);

	StatsService::SendPlayerStats(caller);
	PlayerService::SendExternalChange(caller);
}
