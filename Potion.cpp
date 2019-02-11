#include "stdafx.h"
#include "Potion.h"


Potion::Potion()
{
}


Potion::~Potion()
{
}

HRESULT Potion::init(const char* imageName, float x, float y, int frameX, int frameY)
{
	item::init(imageName, x, y, frameX, frameY);

	if (frameX == 8)
	{
		_potionType = TagPotion::SMALL;
		_hpUpPoint = 4;
	}
	else if (frameX == 9)
	{
		_potionType = TagPotion::MIDDLE;
		_hpUpPoint = 8;
	}
	else if (frameX == 10)
	{
		_potionType = TagPotion::BIG;
		_hpUpPoint = 15;
	}

	return S_OK;
}

void Potion::release()
{
}

void Potion::update()
{
}

void Potion::render(float cameraX, float cameraY)
{
	_item->viewX = _item->x - cameraX;
	_item->viewY = _item->y - cameraY;
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->viewX, _item->viewY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
