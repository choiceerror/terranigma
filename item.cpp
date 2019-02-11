#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
	IMAGEMANAGER->addFrameImage("item", "image/item.bmp", 220, 20, 11, 1, true, MAGENTA);

	return S_OK;
}

void item::release()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		SAFE_DELETE((*_viItem));
	}
}

void item::update()
{
}

void item::render()
{


}

void item::dropItem(const char* imageName, float x, float y, int frameX, int frameY)
{
	tagItem* item = new tagItem;
	ZeroMemory(&item, sizeof(tagItem*));
	item->imageName = imageName;
	IMAGEMANAGER->findImage(item->imageName);
	item->x = x;
	item->y = y;
	item->frameX = frameX;
	item->frameY = frameY;
	
	if (item->frameX == 0 || item->frameX >= 11)
	{
		item->itemType = NONE;
	}
	if (item->frameX >= 1 && item->frameX <= 3)
	{
		item->itemType = ARMOR;
	}
	else if (item->frameX >= 4 && item->frameX <= 6)
	{
		item->itemType = WEAPON;
	}
	else if (item->frameX >= 8 && item->frameX <= 10)
	{
		item->itemType = POTION;
	}
	else if (item->frameX == 7)
	{
		item->itemType = GOLD;
	}
	
	_vItem.push_back(item);
}
