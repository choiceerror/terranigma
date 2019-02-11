#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(const char* imageName, float x, float y, int frameX, int frameY)
{
	_item->imageName = imageName;
	_item->x = x;
	_item->y = y;
	_item->frameX = frameX;
	_item->frameY = frameY;
	_item->isLive = true;

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

