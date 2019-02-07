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
	_enemy.direction = BALLMONSTER_RIGHT_MOVE;

	int upIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upIdle", imageName, upIdle, 1, 5, true);

	int upMove[] = { 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upMove", imageName, upMove, 3, 5, true);

	int downIdle[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downIdle", imageName, downIdle, 1, 5, true);

	int downMove[] = { 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downMove", imageName, downMove, 3, 5, true);

	int rightIdle[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightIdle", imageName, rightIdle, 1, 5, true);

	int rightMove[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightMove", imageName, rightMove, 3, 5, true);

	int leftIdle[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftIdle", imageName, leftIdle, 1, 3, true);

	int leftMove[] = { 13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftMove", imageName, leftMove, 3, 3, true);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightMove");

	_directionTime = 3.0f;
	_directionWorldTime = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void ballMonster::release()
{
}

void ballMonster::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);
	move();
	
}

void ballMonster::render(float viewX, float viewY)
{
	Rectangle(getMemDC(), _enemy.rangeRc);
	Rectangle(getMemDC(), _enemy.rc);
	_enemy.image->expandAniRenderCenter(getMemDC(), viewX, viewY, _enemy.motion, 2.f , 2.f);
}

void ballMonster::move()
{
	if (_directionTime + _directionWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_rndDirection = RND->getInt(7);

		if (_rndDirection == 0)
		{
			_enemy.direction = BALLMONSTER_UP_IDLE;
		}
		else if (_rndDirection == 1)
		{
			_enemy.direction = BALLMONSTER_UP_MOVE;
		}
		else if (_rndDirection == 2)
		{
			_enemy.direction = BALLMONSTER_DOWN_IDLE;
		}
		else if (_rndDirection == 3)
		{
			_enemy.direction = BALLMONSTER_DOWN_MOVE;
		}
		else if (_rndDirection == 4)
		{
			_enemy.direction = BALLMONSTER_RIGHT_MOVE;
		}
		else if (_rndDirection == 5)
		{
			_enemy.direction = BALLMONSTER_LEFT_IDLE;
		}
		else if (_rndDirection == 6)
		{
			_enemy.direction = BALLMONSTER_LEFT_MOVE;
		}
		_directionWorldTime = TIMEMANAGER->getWorldTime();
	}

	//방향에 따라 프레임 동작
	switch (_enemy.direction)
	{
	case BALLMONSTER_UP_IDLE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "upIdle");
		_enemy.motion->start();
		break;
	case BALLMONSTER_UP_MOVE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "upMove");
		_enemy.motion->start();
		_enemy.y -= _enemy.speed;
		break;
	case BALLMONSTER_DOWN_IDLE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downIdle");
		_enemy.motion->start();
		break;
	case BALLMONSTER_DOWN_MOVE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downMove");
		_enemy.motion->start();
		_enemy.y += _enemy.speed;
		break;
	case BALLMONSTER_RIGHT_IDLE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightIdle");
		_enemy.motion->start();
		break;
	case BALLMONSTER_RIGHT_MOVE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightMove");
		_enemy.motion->start();
		_enemy.x += _enemy.speed;
		break;
	case BALLMONSTER_LEFT_IDLE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "leftIdle");
		_enemy.motion->start();
		break;
	case BALLMONSTER_LEFT_MOVE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "leftMove");
		_enemy.motion->start();
		_enemy.x -= _enemy.speed;
		break;
	
	}

}
