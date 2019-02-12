#include "stdafx.h"
#include "Armor.h"


Armor::Armor()
{
}


Armor::~Armor()
{
}

HRESULT Armor::init(const char* imageName, float x, float y, ARMORTYPE armorType)
{
	item::init(imageName, x, y);
	_item.itemType = ITEMTYPE::ARMOR;
	_armorType = armorType;

	if (_armorType == ARMORTYPE::ICE_ARMOR)
	{
		_item.frameX = 1;
		_item.frameY = 0;
		_armorPoint = 8;
	}
	else if (_armorType == ARMORTYPE::HOOD)
	{
		_item.frameX = 2;
		_item.frameY = 0;
		_armorPoint = 5;
	}
	else if (_armorType == ARMORTYPE::IRON_ARMOR)
	{
		_item.frameX = 3;
		_item.frameY = 0;
		_armorPoint = 15;
	}
	else
	{
		return E_FAIL;
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
	_item.viewX = _item.x - cameraX;
	_item.viewY = _item.y - cameraY;
	_item.rc = RectMake(_item.x, _item.y, _item.image->getFrameWidth(), _item.image->getFrameHeight());
	IMAGEMANAGER->expandRender(_item.imageName, getMemDC(), _item.viewX, _item.viewY, _item.frameX, _item.frameY, 3.0f, 3.0f);
}
