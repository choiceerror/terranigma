#include "stdafx.h"
#include "Armor.h"


Armor::Armor()
{
}


Armor::~Armor()
{
}

HRESULT Armor::init(const char* imageName, float x, float y, int frameX, int frameY)
{
	item::init(imageName, x, y, frameX, frameY);

	if (frameX == 1)
	{
		_armorType = TagArmor::ICE_ARMOR;
		_armorPoint = 8;
	}
	else if (frameX == 2)
	{
		_armorType = TagArmor::HOOD;
		_armorPoint = 5;
	}
	else if (frameX == 3)
	{
		_armorType = TagArmor::IRON_ARMOR;
		_armorPoint = 15;
	}

	return S_OK;
}

void Armor::release()
{
}

void Armor::update()
{


}

void Armor::render(float cameraX, float cameraY)
{
	_item->viewX = _item->x - cameraX;
	_item->viewY = _item->y - cameraY;
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->viewX, _item->viewY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
