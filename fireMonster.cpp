#include "stdafx.h"
#include "fireMonster.h"


fireMonster::fireMonster()
{
}


fireMonster::~fireMonster()
{
}

HRESULT fireMonster::init(string enemyName, const char * imageName, float x, float y, int idX, int idY)
{
	enemy::init(enemyName, imageName, x, y, idX, idY);
	_enemy.name = enemyName;

	_enemy.direction = FIREMONSTER_IDLE;

	int idle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idle", imageName, idle, 1, 3, true);

	int move[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "move", imageName, move, 4, 6, false);

	int dead[] = { 5, 6, 7, 8, 9, 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "dead", imageName, dead, 6, 4, false);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "move");

	return S_OK;
}

void fireMonster::release()
{
}

void fireMonster::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);

	_enemy.motion->start();
	KEYANIMANAGER->update();
	
	move();
}

void fireMonster::render(float viewX, float viewY)
{
	_enemy.image->aniRender(getMemDC(), viewX, viewY, _enemy.motion);
}

void fireMonster::move()
{
	
}
