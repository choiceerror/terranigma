#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

HRESULT Weapon::init(const char* imageName, float x, float y, int frameX, int frameY)
{
	item::init(imageName, x, y, frameX, frameY);

	if (frameX == 4)
	{
		_weaponType = TagWeapon::ICE_SPEAR;
		_damagePoint = 10;
	}
	else if (frameX == 5)
	{
		_weaponType = TagWeapon::IRON_SPEAR;
		_damagePoint = 5;
	}
	else if (frameX == 6)
	{
		_weaponType = TagWeapon::FIRE_SPEAR;
		_damagePoint = 12;
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
	_item->viewX = _item->x - cameraX;
	_item->viewY = _item->y - cameraY;
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->viewX, _item->viewY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
