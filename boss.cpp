#include "stdafx.h"
#include "boss.h"


boss::boss()
{
}


boss::~boss()
{
}

HRESULT boss::init(string enemyName, const char * imageName, float x, float y, int idX, int idY)
{
	enemy::init(enemyName, imageName, x, y, idX, idY);
	_enemy.name = enemyName;

	int move[] = {0, 1, 2, 3};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "move", imageName, move, 4, 4, true);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "move");

	return S_OK;
}

void boss::release()
{
}

void boss::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);
}

void boss::render(float viewX, float viewY)
{
	_enemy.image->aniRender(getMemDC(), viewX, viewY, _enemy.motion);
}
