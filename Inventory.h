#pragma once
#include "gameNode.h"
#include "Weapon.h"
#include "Accessory.h"
#include "Armor.h"
#include "Potion.h"

#define WEAPON_MAX_ARR 16
#define ARMOR_MAX_ARR 16
#define ACCESSORY_MAX_ARR 32
#define POTION_MAX_ARR 32


class Inventory : public gameNode
{
private:
	WEAPONTYPE _weaponInv[16];
	ARMORTYPE _armorInv[16];
	ACCESSORYTYPE _accessoryInv[32];
	POTIONTYPE _potionInv[32];

	//아이템을 먹을시 여기에 값이 들어가게함
	WEAPONTYPE _tempWeapon;
	ARMORTYPE _tempArmor;
	ACCESSORYTYPE _tempAccessory;
	POTIONTYPE _tempPorion;

	//아이템 각각 소지 갯수
	int _weaponCount;
	int _accessoryCount;
	int _armorCount;
	int _potionCount;


public:
	Inventory();
	~Inventory();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void inventoryReset();
	void itemMove();
	void itemCount();

};

