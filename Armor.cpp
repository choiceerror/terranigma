#include "stdafx.h"
#include "Armor.h"


Armor::Armor()
{
}


Armor::~Armor()
{
}

HRESULT Armor::init(const char* imageName, float x, float y, int frameX, int frameY, int armorPoint)
{
	item::init(imageName, x, y, frameX, frameY);



	return S_OK;
}

void Armor::release()
{
}

void Armor::update()
{


}

void Armor::render(float cameraX, float cameraY)
{
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->x - cameraX, _item->y - cameraY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
