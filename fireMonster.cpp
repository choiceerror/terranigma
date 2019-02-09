#include "stdafx.h"
#include "fireMonster.h"


fireMonster::fireMonster()
{
}


fireMonster::~fireMonster()
{
}

HRESULT fireMonster::init(string enemyName, const char * imageName, float x, float y, int idX, int idY, int hp)
{
	enemy::init(enemyName, imageName, x, y, idX, idY, hp);
	_enemy.name = enemyName;
	_enemy.currentHP = _enemy.maxHP = hp;

	_enemy.state = FIREMONSTER_STATE_IDLE;
	_enemy.direction = FIREMONSTER_DIRECTION_DOWN;

	int idleORmove[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleORmove", imageName, idleORmove, 4, 5, true);

	int dead[] = { 5, 6, 7, 8, 9, 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "dead", imageName, dead, 6, 4, false);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "idleORmove");
	_enemy.rangeRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth() * 6, _enemy.image->getFrameHeight() * 6);
	return S_OK;
}

void fireMonster::release()
{
}

void fireMonster::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);

	move();
	_enemy.rangeRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth() * 10, _enemy.image->getFrameHeight() * 6);
}

void fireMonster::render(float viewX, float viewY)
{
	Rectangle(getMemDC(), _enemy.rangeRc);
	_enemy.image->expandAniRenderCenter(getMemDC(), viewX, viewY, _enemy.motion, 2.f, 2.f);
}

void fireMonster::move()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_enemy.state = FIREMONSTER_STATE_MOVE;
		_enemy.direction = FIREMONSTER_DIRECTION_RIGHT;
	}

	//방향에 따라 프레임 동작
	switch (_enemy.state)
	{
	case FIREMONSTER_STATE_IDLE:
	case FIREMONSTER_STATE_MOVE:

		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "idleORmove");
		_enemy.motion->start();

		if (_enemy.state == FIREMONSTER_STATE_MOVE)
		{
			if (_enemy.direction == FIREMONSTER_DIRECTION_RIGHT)	   _enemy.x += _enemy.speed;
			else if (_enemy.direction == FIREMONSTER_DIRECTION_LEFT) _enemy.x -= _enemy.speed;
			else if (_enemy.direction == FIREMONSTER_DIRECTION_UP) _enemy.y -= _enemy.speed;
			else if (_enemy.direction == FIREMONSTER_DIRECTION_DOWN) _enemy.y += _enemy.speed;
		}

		break;
	case FIREMONSTER_STATE_DEAD:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "dead");
		_enemy.motion->start();
		
		break;
	}
}

//총알 카운트 발사할 함수
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
