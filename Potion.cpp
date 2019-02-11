#include "stdafx.h"
#include "Potion.h"


Potion::Potion()
{
}


Potion::~Potion()
{
}

HRESULT Potion::init(const char* imageName, float x, float y, int frameX, int frameY,int hpUpPoint)
{
	item::init(imageName, x, y, frameX, frameY);

	_hpUpPoint = hpUpPoint;

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
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->x - cameraX, _item->y - cameraY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
