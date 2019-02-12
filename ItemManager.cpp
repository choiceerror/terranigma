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
	//아이템 조건 제거
	itemRemove();



}

void ItemManager::render(float cameraX, float cameraY)
{
	itemDraw(cameraX, cameraY);


}

//릴리즈용 제거함수
void ItemManager::deleteAll()
{
	//릴리즈때 벡터 다 제거
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

void ItemManager::itemDraw(float cameraX, float cameraY)
{
	for (_viArmor = _vArmor.begin(); _viArmor != _vArmor.end(); ++_viArmor)
	{
		(*_viArmor)->render(cameraX, cameraY);
	}
	for (_viAccessery = _vAccessery.begin(); _viAccessery != _vAccessery.end(); ++_viAccessery)
	{
		(*_viAccessery)->render(cameraX, cameraY);
	}
	for (_viGold = _vGold.begin(); _viGold != _vGold.end(); ++_viGold)
	{
		(*_viGold)->render(cameraX, cameraY);
	}
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		(*_viWeapon)->render(cameraX, cameraY);
	}
	for (_viPotion = _vPotion.begin(); _viPotion != _vPotion.end(); ++_viPotion)
	{
		(*_viPotion)->render(cameraX, cameraY);
	}
}

void ItemManager::dropPotion(float x, float y, POTIONTYPE potionType)
{
	Potion* potion;
	potion = new Potion;
	potion->init("item", x, y, potionType);
	_vPotion.push_back(potion);
}

void ItemManager::dropArmor(float x, float y, ARMORTYPE armorType)
{
	Armor* armor;
	armor = new Armor;
	armor->init("item", x, y, armorType);
	_vArmor.push_back(armor);
}

void ItemManager::dropWeapon(float x, float y, WEAPONTYPE weaponType)
{
	Weapon* weapon;
	weapon = new Weapon;
	weapon->init("item", x, y, weaponType);
	_vWeapon.push_back(weapon);
}

void ItemManager::dropGold(float x, float y)
{
	Gold* gold;
	gold = new Gold;
	gold->init("item", x, y);
	_vGold.push_back(gold);
}

void ItemManager::dropAccessory(float x, float y, ACCESSORYTYPE accessoryType)
{
	Accessory* accessory;
	accessory = new Accessory;
	accessory->init("item", x, y, accessoryType);
	_vAccessery.push_back(accessory);
}

void ItemManager::itemRemove()
{
	//아이템 isLive 불값이 False가 되면 사라지는 함수

	//무기
	for (int i = 0; i < _vWeapon.size();)
	{
		if (_vWeapon[i]->getItemIsLive() == false)
		{
			_vWeapon.erase(_vWeapon.begin() + i);
		}
		else
		{
			i++;
		}
	}

	//방어구
	for (int i = 0; i < _vArmor.size();)
	{
		if (_vArmor[i]->getItemIsLive() == false)
		{
			_vArmor.erase(_vArmor.begin() + i);
		}
		else
		{
			i++;
		}
	}

	//악세서리
	for (int i = 0; i < _vAccessery.size();)
	{
		if (_vAccessery[i]->getItemIsLive() == false)
		{
			_vAccessery.erase(_vAccessery.begin() + i);
		}
		else
		{
			i++;
		}
	}

	//물약
	for (int i = 0; i < _vPotion.size();)
	{
		if (_vPotion[i]->getItemIsLive() == false)
		{
			_vPotion.erase(_vPotion.begin() + i);
		}
		else
		{
			i++;
		}
	}

	//골드
	for (int i = 0; i < _vGold.size();)
	{
		if (_vGold[i]->getItemIsLive() == false)
		{
			_vGold.erase(_vGold.begin() + i);
		}
		else
		{
			i++;
		}
	}

}
