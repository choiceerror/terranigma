#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

HRESULT Weapon::init(const char* imageName, float x, float y, WEAPONTYPE weaponType)
{
	item::init(imageName, x, y);
	_item.itemType = ITEMTYPE::WEAPON;
	_weaponType = weaponType;

	if (_weaponType == WEAPONTYPE::ICE_SPEAR)
	{
		_item.frameX = 4;
		_item.frameY = 0;
		_damagePoint = 10;
	}
	else if (_weaponType == WEAPONTYPE::IRON_SPEAR)
	{
		_item.frameX = 5;
		_item.frameY = 0;
		_damagePoint = 5;
	}
	else if (_weaponType == WEAPONTYPE::FIRE_SPEAR)
	{
		_item.frameX = 6;
		_item.frameY = 0;
		_damagePoint = 12;
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

void Weapon::release()
{
}

void Weapon::update()
{


}

void Weapon::render(float cameraX, float cameraY)
{
	_item.viewX = _item.x - cameraX;
	_item.viewY = _item.y - cameraY;
	_item.rc = RectMake(_item.x, _item.y, _item.image->getFrameWidth(), _item.image->getFrameHeight());
	IMAGEMANAGER->expandRender(_item.imageName, getMemDC(), _item.viewX, _item.viewY, _item.frameX, _item.frameY, 2.8f, 2.8f);
}
