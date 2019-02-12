#include "stdafx.h"
#include "Gold.h"


Gold::Gold()
{
}


Gold::~Gold()
{
}

HRESULT Gold::init(const char* imageName, float x, float y)
{
	item::init(imageName, x, y);
	_item.itemType = ITEMTYPE::GOLD;
	_item.frameX = 7;
	_item.frameY = 0;
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
	_item.viewX = _item.x - cameraX;
	_item.viewY = _item.y - cameraY;
	_item.rc = RectMake(_item.x, _item.y, _item.image->getFrameWidth(), _item.image->getFrameHeight());
	IMAGEMANAGER->expandRender(_item.imageName, getMemDC(), _item.viewX, _item.viewY, _item.frameX, _item.frameY, 3.0f, 3.0f);
}
