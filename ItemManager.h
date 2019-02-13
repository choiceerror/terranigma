#pragma once
#include "gameNode.h"
#include "Potion.h"
#include "Armor.h"
#include "Weapon.h"
#include "Gold.h"
#include "Accessory.h"


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
	void render(float cameraX = 0.f, float cameraY = 0.f);

	void deleteAll();
	void itemDraw(float cameraX,float cameraY);

	//각각 그릴때
	void weaponDraw(float cameraX = 0, float cameraY = 0);
	void armorDraw(float cameraX = 0, float cameraY = 0);
	void accessoryDraw(float cameraX = 0, float cameraY = 0);
	void potionDraw(float cameraX = 0, float cameraY = 0);

	void dropPotion(float x, float y, POTIONTYPE potionType);
	void dropArmor(float x, float y, ARMORTYPE armorType);
	void dropWeapon(float x, float y, WEAPONTYPE weaponType);
	void dropGold(float x, float y);
	void dropAccessory(float x, float y, ACCESSORYTYPE accessoryType);

	void itemRemove();

	//=================접근자 설정자=================
	vector<Potion*> getVPotion() { return _vPotion; }
	vector<Potion*>* setVPotion() { return &_vPotion; }

	vector<Weapon*> getVWeapon() { return _vWeapon; }
	vector<Weapon*>* setVWeapon() { return &_vWeapon; }

	vector<Armor*> getVArmor() { return _vArmor; }
	vector<Armor*>* setVArmor() { return &_vArmor; }

	vector<Accessory*> getVAccessory() { return _vAccessery; }
	vector<Accessory*>* setVAccessory() { return &_vAccessery; }

	vector<Gold*> getVGlod() { return _vGold; }
	vector<Gold*>* setVGlod() { return &_vGold; }

};

