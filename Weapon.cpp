#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

HRESULT Weapon::init(const char* imageName, float x, float y, int frameX, int frameY, int damagePoint)
{
	item::init(imageName, x, y, frameX, frameY);



	return S_OK;
}

void Weapon::release()
{
}

void Weapon::update()
{


}

void Weapon::render(float cameraX, float cameraY)
{
	IMAGEMANAGER->expandRender(_item->imageName, getMemDC(), _item->x - cameraX, _item->y - cameraY, _item->frameX, _item->frameY, 1.0f, 1.0f);
}
