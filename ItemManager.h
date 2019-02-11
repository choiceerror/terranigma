#pragma once
#include "gameNode.h"
#include "Potion.h"
#include "Armor.h"
#include "Weapon.h"

enum ITEMTYPE
{
	NONE,
	ARMOR,
	WEAPON,
	GOLD,
	POTION
};

class ItemManager : public gameNode
{
private:
	vector<Potion*>				_vPotion;
	vector<Potion*>::iterator	_viPotion;

	vector<Armor*>				_vArmor;
	vector<Armor*>::iterator	_viArmor;

	vector<Weapon*>				_vWeapon;
	vector<Weapon*>::iterator	_viWeapon;


public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void deleteAll();
};

