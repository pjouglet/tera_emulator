#ifndef ITEMENUM_H
#define ITEMENUM_H

enum ItemCategory : short
{
	combat = 1,
	magical,
	custormaize,
	pkitem,
	medal,
	service,
	earring,
	necklace,
	ring,
	skillbook,
	token,
	order,
	etc,
	petAdult,
	petOrb,
	dyeItem,
	dyeRaw,
	dyeRecipe,
	dual,
	lance,
	twohand,
	axe,
	circle,
	bow,
	staff,
	rod,
	blaster,
	gauntlet,
	shuriken,
	accessoryHair,
	weaponMaterial,
	armorMaterial,
	keyItem,
	generalMaterial,
	fiber,
	metal,
	alchemy,
	leather,
	alchemyMaterial,
	fireworkMaterial,
	weaponComponent,
	armorComponent,
	bodyMail,
	handMail,
	feetMail,
	bodyLeather,
	handLeather,
	feetLeather,
	bodyRobe,
	handRobe,
	feetRobe,
	recipe,
	quest,
	document,
	crestPoint,
	crest,
	charm,
	extractRecipe,
	accessoryFace,
	style_face,
	style_hair,
	style_dual,
	style_lance,
	style_twohand,
	style_axe,
	style_circle,
	style_bow,
	style_staff,
	style_rod,
	belt,
	brooch
};

enum ItemResourceType : byte
{
	small
};

enum ItemType : short
{
	DISPOSAL,
	CUSTOM,
	NO_COMBAT,
	CHANGE_NAME,
	EQUIP_ACCESSORY,
	SKILLBOOK,
	DUNGEON_COIN,
	CURSED_DREAM_PIECE,
	BLESSED_DREAM_PIECE,
	UNIDENTIFY_SCROLL,
	CURSE_REMOVE_SCROLL,
	IDENTIFY_SCROLL,
	CHANGE_COLOR_ITEM,
	MIX_DISPOSAL,
	CHANGE_RACE,
	CHANGE_GENDER,
	CHANGE_LOOKS,
	EQUIP_WEAPON,
	START_GUILD_WAR,
	GIVE_UP_GUILD_WAR,
	CHRONO_SCROLL,
	DUNGEON_RESET_SCROLL,
	RESET_SCROLL,
	IMMEDIATE,
	EQUIP_ARMOR_BODY,
	EQUIP_ARMOR_ARM,
	EQUIP_ARMOR_LEG,
	DOCUMENT,
	CREST_RESET,
	CREST_POINT,
	CREST,
	RECIPE,
	EQUIP_STYLE_ACCESSORY,
	EQUIP_STYLE_WEAPON,
	EQUIP_STYLE_BODY,
	EQUIP_STYLE_BACK,
};

enum ItemBoundType :byte
{
	BOUND_NONE,
	BOUND_EQUIP,
	BOUND_PICK_UP,
	BOUND_LOOT
};

enum ItemRareGrade : byte
{
	RARE_GRADE_NORMAL = 0,
	RARE_GRADE_UNCOMMON = 1,
	RARE_GRADE_RARE = 2,
	RARE_GRADE_SUPERIOR = 3
};

enum ItemGrade : byte
{
	GRADE_NORMAL = 0,
	GRADE_MASTERWORK = 1,
	GRADE_AWAKENED = 2
};

enum PROFILE_SLOT_TYPE : int
{
	PROFILE_WEAPON = 1,

	PROFILE_ARMOR = 3,
	PROFILE_GLOVES = 4,
	PROFILE_BOOTS = 5,
	PROFILE_EARRING_L = 6,
	PROFILE_EARRING_R = 7,
	PROFILE_RING_L = 8,
	PROFILE_RING_R = 9,
	PROFILE_NECKLACE = 10,

	
	PROFILE_BROOCH,
	PROFILE_INNERWARE,
	PROFILE_MASK,
	PROFILE_HEAD_ADRONMENT,

	PROFILE_SKIN_BODY,
	PROFILE_SKIN_WEAPON,
	PROFILE_SKIN_FACE,
	PROFILE_SKIN_BACK,
	PROFILE_SKIN_HEAD,

	PROFILE_BELT = 19,

	//PROFILE_WEAPON = 73,
	//PROFILE_ARMOR = 74,
	//PROFILE_GLOVES = 75,
	//PROFILE_BOOTS = 76,
	//PROFILE_RING_L = 77,
	//PROFILE_RING_R = 78,
	//PROFILE_EARRING_L = 79,
	//PROFILE_EARRING_R = 80,
	//PROFILE_NECKLACE = 81,
	//PROFILE_BELT = 82,
	//PROFILE_BROCH = 83,
	//PROFILE_INNERWARE = 84,
	//PROFILE_MASK = 86,
	//PROFILE_HEAD_ADRONMENT = 87,
	//
	//PROFILE_SKIN_BODY = 88,
	//PROFILE_SKIN_WEAPON = 89,
	//PROFILE_SKIN_FACE = 90,
	//PROFILE_SKIN_BACK = 91,
	//PROFILE_SKIN_HEAD = 91

};

enum EquipmentPart
{
	E_BELT,
	E_FINGER,
	E_FEET,
	E_HAND,
	E_BODY,
	E_UNDERWEAR,
	E_EAR,
	E_BROOCH,
	E_NECK,
	E_ACCESSORYFACE,
	E_ACCESSORYHAIR,
	E_STYLE_FACE,
	E_STYLE_HAIR,
	E_STYLE_WEAPON,
	E_STYLE_BODY,
	E_STYLE_BACK,
};

#endif