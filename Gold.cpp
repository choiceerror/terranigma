#include "stdafx.h"
#include "Gold.h"


Gold::Gold()
{
}


Gold::~Gold()
{
}

HRESULT Gold::init(const char* imageName, float x, float y, int frameX, int frameY)
{
	item::init(imageName, x, y, frameX, frameY);

	_goldNum = RND->getRandomInt(5, 15);

	return S_OK;
}

void Gold::release()
{
}

void Gold::update()
{
}

void Gold::render(float cameraX, float cameraY)
{
	_item->viewX = _item->x - cameraX;
	_item->viewY = _item->y - cameraY;
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->viewX, _item->viewY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
