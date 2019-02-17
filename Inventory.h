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
	//각각 인벤토리
	WEAPONTYPE _weaponInv[16];
	ARMORTYPE _armorInv[16];
	ACCESSORYTYPE _accessoryInv[32];
	POTIONTYPE _potionInv[32];

	//현재 낀 아이템
	WEAPONTYPE _currentWeapon;
	ARMORTYPE _currentArmor;
	ACCESSORYTYPE _currentAccessory;

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

	void inventorySave();
	void inventoryLoad();

	void inventoryReBooting();

	//============================접근자 설정자============================

	//인벤토리 접근자
	WEAPONTYPE getWeaponInv(int i) { return _weaponInv[i]; }
	ARMORTYPE getArmorInv(int i) { return _armorInv[i]; }
	ACCESSORYTYPE getAccessoryInv(int i) { return _accessoryInv[i]; }
	POTIONTYPE getPotionInv(int i) { return _potionInv[i]; }

	//현재 착용 아이템 접근자 설정자
	WEAPONTYPE getCurrentWeapon() { return _currentWeapon; }
	void setCurrentWeapon(WEAPONTYPE currentWeapon) { _currentWeapon = currentWeapon; }
	ARMORTYPE getCurrentArmor() { return _currentArmor; }
	void setCurrentArmor(ARMORTYPE currentArmor) { _currentArmor = currentArmor; }
	ACCESSORYTYPE getCurrentAccessory() { return _currentAccessory; }
	void setCurrentAccessory(ACCESSORYTYPE currentAccessory) { _currentAccessory = currentAccessory; }

	//각 아이템 소지갯수 접근자
	int getWeaponCount() { return _weaponCount; }
	int getArmorCount() { return _armorCount; }
	int getAccessoryCount() { return _accessoryCount; }
	int getPotionCount() { return _potionCount; }

	//템프공간 설정자
	void pickUpWeapon(WEAPONTYPE weaponType) { _tempWeapon = weaponType; }
	void pickUpArmor(ARMORTYPE armorType) { _tempArmor = armorType; }
	void pickUpAccessory(ACCESSORYTYPE accessoryType) { _tempAccessory = accessoryType; }
	void pickUpPotion(POTIONTYPE potionType) { _tempPorion = potionType; }

};

