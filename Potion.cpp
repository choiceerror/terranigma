#include "stdafx.h"
#include "Potion.h"


Potion::Potion()
{
}


Potion::~Potion()
{
}

HRESULT Potion::init(const char* imageName, float x, float y, POTIONTYPE potionType)
{
	item::init(imageName, x, y);
	_item.itemType = ITEMTYPE::POTION;
	_potionType = potionType;

	if (_potionType == POTIONTYPE::SMALL)
	{
		_item.frameX = 8;
		_item.frameY = 0;
		_hpUpPoint = 4;
	}
	else if (_potionType == POTIONTYPE::MIDDLE)
	{
		_item.frameX = 9;
		_item.frameY = 0;
		_hpUpPoint = 8;
	}
	else if (_potionType == POTIONTYPE::BIG)
	{
		_item.frameX = 10;
		_item.frameY = 0;
		_hpUpPoint = 15;
	}
	else
	{
		return E_FAIL;
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
	_item.viewX = _item.x - cameraX;
	_item.viewY = _item.y - cameraY;
	_item.rc = RectMake(_item.x, _item.y, _item.image->getFrameWidth(), _item.image->getFrameHeight());
	IMAGEMANAGER->expandRender(_item.imageName, getMemDC(), _item.viewX, _item.viewY, _item.frameX, _item.frameY, 3.0f, 3.0f);
}
