#include "stdafx.h"
#include "ballMonster.h"


ballMonster::ballMonster()
{
}


ballMonster::~ballMonster()
{
}

HRESULT ballMonster::init(string enemyName, const char * imageName, float x, float y, int idX, int idY)
{
	enemy::init(enemyName, imageName, x, y, idX, idY);

	_enemy.name = enemyName;
	_enemy.direction = BALLMONSTER_DOWN_IDLE; //처음은 아래 가만히있는상태로

	int upIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upIdle", imageName, upIdle, 1, 3, true);

	int upMove[] = { 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upMove", imageName, upMove, 3, 3, true);

	int downIdle[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downIdle", imageName, downIdle, 1, 3, true);

	int downMove[] = { 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downMove", imageName, downMove, 3, 3, true);

	int rightIdle[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightIdle", imageName, rightIdle, 1, 3, true);

	int rightMove[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightMove", imageName, rightMove, 3, 3, true);

	int leftIdle[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftIdle", imageName, leftIdle, 1, 3, true);

	int leftMove[] = { 13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftMove", imageName, leftMove, 3, 3, true);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightMove");
	return S_OK;
}

void ballMonster::release()
{
}

void ballMonster::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);
	move();
	KEYANIMANAGER->update();
	
}

void ballMonster::render(float viewX, float viewY)
{
	_enemy.image->aniRender(getMemDC(), viewX, viewY, _enemy.motion);
	//Rectangle(getMemDC(), _enemy.rc);
}

void ballMonster::move()
{
	_enemy.x += 1;
	_enemy.motion->start();
}
