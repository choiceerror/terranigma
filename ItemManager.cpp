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
	IMAGEMANAGER->addFrameImage("item", "image/item.bmp", 220, 20, 11, 1, true, MAGENTA);




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
}
