#pragma once
#include "gameNode.h"
#include "Potion.h"
#include "Armor.h"
#include "Weapon.h"
#include "Gold.h"
#include "Accessory.h"

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
	vector<Potion*>					_vPotion;
	vector<Potion*>::iterator		_viPotion;

	vector<Armor*>					_vArmor;
	vector<Armor*>::iterator		_viArmor;

	vector<Weapon*>					_vWeapon;
	vector<Weapon*>::iterator		_viWeapon;

	vector<Gold*>					_vGold;
	vector<Gold*>::iterator			_viGold;

	vector<Accessory*>				_vAccessery;
	vector<Accessory*>::iterator	_viAccessery;




public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void deleteAll();
	void itemDraw();

	void dropPotion(const char* imageName, float x, float y, int frameX, int frameY);
	void dropArmor(const char* imageName, float x, float y, int frameX, int frameY);
	void dropWeapon(const char* imageName, float x, float y, int frameX, int frameY);
	void dropGold(const char* imageName, float x, float y, int frameX, int frameY);
	void dropAccessory(const char* imageName, float x, float y, int frameX, int frameY);

};

