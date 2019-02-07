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

	int idleORmove[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleORmove", imageName, idleORmove, 4, 3, true);

	int dead[] = { 5, 6, 7, 8, 9, 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "dead", imageName, dead, 6, 4, false);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "idleORmove");
	return S_OK;
}

void fireMonster::release()
{
}

void fireMonster::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);

	move();
}

void fireMonster::render(float viewX, float viewY)
{
	_enemy.image->aniRender(getMemDC(), viewX, viewY, _enemy.motion);
}

void fireMonster::move()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_enemy.direction = FIREMONSTER_DEAD;
	}
	else if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_enemy.direction = FIREMONSTER_RIGHT_MOVE;
	}
	
	//방향에 따라 프레임 동작
	switch (_enemy.direction)
	{
	case FIREMONSTER_IDLE:
	case FIREMONSTER_LEFT_MOVE:
	case FIREMONSTER_RIGHT_MOVE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "idleORmove");
		_enemy.motion->start();

		if(_enemy.direction == FIREMONSTER_RIGHT_MOVE)	   _enemy.x += _enemy.speed;
		else if(_enemy.direction == FIREMONSTER_LEFT_MOVE) _enemy.x -= _enemy.speed;

		break;
	case FIREMONSTER_DEAD:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "dead");
		_enemy.motion->start();
		
		break;
	}
}

bool fireMonster::fireBulletCountFire()
{
	_fireCount++;

	if (_fireCount % 30 == 0)
	{
		_fireCount = 0;
		return true;
	}
	return false;
}
