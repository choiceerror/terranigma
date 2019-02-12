#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(const char* imageName, float x, float y)
{
	_item.imageName = imageName;
	_item.image = IMAGEMANAGER->findImage(_item.imageName);
	_item.x = x;
	_item.y = y;
	_item.viewX = x;
	_item.viewY = y;
	_item.isLive = true;
	_item.rc = RectMake(x, y, _item.image->getFrameWidth(), _item.image->getFrameHeight());

	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{

}

