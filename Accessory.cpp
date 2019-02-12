#include "stdafx.h"
#include "Accessory.h"


Accessory::Accessory()
{
}


Accessory::~Accessory()
{
}

HRESULT Accessory::init(const char* imageName, float x, float y, ACCESSORYTYPE accessoryType)
{
	item::init(imageName, x, y);
	_item.itemType = ITEMTYPE::ACCESSORY;
	_accessoryType = accessoryType;

	if (_accessoryType == ACCESSORYTYPE::RED_SCARF)
	{
		_item.frameX = 11;
		_item.frameY = 0;
		_accesseryArmorPoint = 10;
	}
	else if (_accessoryType == ACCESSORYTYPE::TALISMAN)
	{
		_item.frameX = 12;
		_item.frameY = 0;
		_accesseryArmorPoint = 5;
	}
	else if (_accessoryType == ACCESSORYTYPE::LEEF)
	{
		_item.frameX = 13;
		_item.frameY = 0;
		_accesseryArmorPoint = 3;
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

void Accessory::release()
{
}

void Accessory::update()
{
}

void Accessory::render(float cameraX, float cameraY)
{
	_item.viewX = _item.x - cameraX;
	_item.viewY = _item.y - cameraY;
	_item.rc = RectMake(_item.x, _item.y, _item.image->getFrameWidth(), _item.image->getFrameHeight());
	IMAGEMANAGER->expandRender(_item.imageName, getMemDC(), _item.viewX, _item.viewY, _item.frameX, _item.frameY, 3.0f, 3.0f);
}
