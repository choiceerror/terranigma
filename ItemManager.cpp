#include "stdafx.h"
#include "ItemManager.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init()
{
	IMAGEMANAGER->addFrameImage("item", "image/item.bmp", 286, 20, 14, 1, true, MAGENTA);




	return S_OK;
}

void ItemManager::release()
{
	deleteAll();
}

void ItemManager::update()
{




}

void ItemManager::render()
{
	itemDraw();


}

void ItemManager::deleteAll()
{
	for (_viArmor = _vArmor.begin(); _viArmor != _vArmor.end(); )
	{
		if (_viArmor != _vArmor.end())
		{
			SAFE_DELETE((*_viArmor));
		}
		else
		{
			++_viArmor;
		}
	}
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end();)
	{
		if (_viWeapon != _vWeapon.end())
		{
			SAFE_DELETE((*_viWeapon));

		}
		else
		{
			++_viWeapon;
		}
	}
	for (_viPotion = _vPotion.begin(); _viPotion != _vPotion.end();)
	{
		if (_viPotion != _vPotion.end())
		{
			SAFE_DELETE((*_viPotion));
		}
		else
		{
			++_viPotion;
		}
	}
	for (_viGold = _vGold.begin(); _viGold != _vGold.end();)
	{
		if (_viGold != _vGold.end())
		{
			SAFE_DELETE((*_viGold));
		}
		else
		{
			++_viGold;
		}
	}
	for (_viAccessery = _vAccessery.begin(); _viAccessery != _vAccessery.end();)
	{
		if (_viAccessery != _vAccessery.end())
		{
			SAFE_DELETE((*_viAccessery));
		}
		else
		{
			++_viAccessery;
		}
	}
}

void ItemManager::itemDraw()
{
	for (_viArmor = _vArmor.begin(); _viArmor != _vArmor.end(); ++_viArmor)
	{
		//(*_viArmor)->render(camera);
	}
	for (_viAccessery = _vAccessery.begin(); _viAccessery != _vAccessery.end(); ++_viAccessery)
	{
		//(*_viAccessery)->render(camera);
	}
	for (_viGold = _vGold.begin(); _viGold != _vGold.end(); ++_viGold)
	{
		//(*_viGold)->render(camera);
	}
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		//(*_viWeapon)->render(camera);
	}
	for (_viPotion = _vPotion.begin(); _viPotion != _vPotion.end(); ++_viPotion)
	{
		//(*_viPotion)->render(camera);
	}
}

void ItemManager::dropPotion(const char * imageName, float x, float y, int frameX, int frameY)
{
	Potion* potion;
	potion = new Potion;
	potion->init(imageName, x, y, frameX, frameY);
	_vPotion.push_back(potion);
}

void ItemManager::dropArmor(const char * imageName, float x, float y, int frameX, int frameY)
{
	Armor* armor;
	armor = new Armor;
	armor->init(imageName, x, y, frameX, frameY);
	_vArmor.push_back(armor);
}

void ItemManager::dropWeapon(const char * imageName, float x, float y, int frameX, int frameY)
{
	Weapon* weapon;
	weapon = new Weapon;
	weapon->init(imageName, x, y, frameX, frameY);
	_vWeapon.push_back(weapon);
}

void ItemManager::dropGold(const char * imageName, float x, float y, int frameX, int frameY)
{
	Gold* gold;
	gold = new Gold;
	gold->init(imageName, x, y, frameX, frameY);
	_vGold.push_back(gold);
}

void ItemManager::dropAccessory(const char * imageName, float x, float y, int frameX, int frameY)
{
	Accessory* accessory;
	accessory = new Accessory;
	accessory->init(imageName, x, y, frameX, frameY);
	_vAccessery.push_back(accessory);
}
