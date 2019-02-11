#include "stdafx.h"
#include "Accessory.h"


Accessory::Accessory()
{
}


Accessory::~Accessory()
{
}

HRESULT Accessory::init(const char * imageName, float x, float y, int frameX, int frameY)
{
	item::init(imageName, x, y, frameX, frameY);

	if (frameX == 11)
	{
		_accessoryType = TagAccessory::RED_SCARF;
		_accesseryArmorPoint = 10;
	}
	else if (frameX == 12)
	{
		_accessoryType = TagAccessory::TALISMAN;
		_accesseryArmorPoint = 5;
	}
	else if (frameX == 13)
	{
		_accessoryType = TagAccessory::LEEF;
		_accesseryArmorPoint = 3;
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
	_item->viewX = _item->x - cameraX;
	_item->viewY = _item->y - cameraY;
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->viewX, _item->viewY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
