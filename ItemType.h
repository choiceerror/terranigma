#pragma once

//아이템 종류
enum class ITEMTYPE
{
	NONE,
	WEAPON,
	ARMOR,
	ACCESSORY,
	GOLD,
	POTION
};

//무기 종류
enum class WEAPONTYPE
{
	NONE,
	ICE_SPEAR,
	IRON_SPEAR,
	FIRE_SPEAR
};

//포션 종류
enum class POTIONTYPE
{
	NONE,
	SMALL,
	MIDDLE,
	BIG
};

//방어구 종류
enum class ARMORTYPE
{
	NONE,
	ICE_ARMOR,
	HOOD,
	IRON_ARMOR
};

//악세서리 종류
enum class ACCESSORYTYPE
{
	NONE,
	RED_SCARF,
	TALISMAN,
	LEEF
};

