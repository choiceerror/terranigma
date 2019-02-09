#include "stdafx.h"
#include "ballMonster.h"


ballMonster::ballMonster()
{
}


ballMonster::~ballMonster()
{
}

HRESULT ballMonster::init(string enemyName, const char * imageName, float x, float y, int idX, int idY, int hp)
{
	enemy::init(enemyName, imageName, x, y, idX, idY, hp);

	_enemy.name = enemyName;
	_enemy.currentHP = _enemy.maxHP = hp;
	_enemy.state = BALLMONSTER_STATE_IDLE;
	_enemy.direction = BALLMONSTER_DIRECTION_DOWN;

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

	return S_OK;
}

void ballMonster::release()
{
}

void ballMonster::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);
	move();
	_enemy.rangeRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth() * 20, _enemy.image->getFrameHeight() * 20);
}

void ballMonster::render(float viewX, float viewY)
{
	//Rectangle(getMemDC(), _enemy.rangeRc);
	//Rectangle(getMemDC(), _enemy.rc);
	_enemy.image->expandAniRenderCenter(getMemDC(), viewX, viewY, _enemy.motion, 2.f , 2.f);
}

void ballMonster::move()
{

	if (_enemy.moveType == BASIC_MOVE_TYPE)
	{
		//상태에 따라 프레임 동작
		switch (_enemy.state)
		{
		case BALLMONSTER_STATE_IDLE:
			if(_enemy.direction == BALLMONSTER_DIRECTION_UP)		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "upIdle");
			else if(_enemy.direction == BALLMONSTER_DIRECTION_DOWN)	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downIdle");
			else if(_enemy.direction == BALLMONSTER_DIRECTION_RIGHT)_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightIdle");
			else if(_enemy.direction == BALLMONSTER_DIRECTION_LEFT) _enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "leftIdle");
			_enemy.motion->start();
			break;
		case BALLMONSTER_STATE_MOVE:
			if (_enemy.direction == BALLMONSTER_DIRECTION_UP)
			{
				_enemy.moveAngle = PI / 2;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "upMove");
			}
			else if (_enemy.direction == BALLMONSTER_DIRECTION_DOWN)
			{
				_enemy.moveAngle = PI / 180 * 270;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downMove");
			}
			else if (_enemy.direction == BALLMONSTER_DIRECTION_RIGHT)
			{
				_enemy.moveAngle = PI2;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightMove");
			}
			else if (_enemy.direction == BALLMONSTER_DIRECTION_LEFT)
			{
				_enemy.moveAngle = PI;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "leftMove");
			}
			_enemy.motion->start();

			_enemy.x += cosf(_enemy.moveAngle) * _enemy.speed;
			_enemy.y += -sinf(_enemy.moveAngle) * _enemy.speed;
			break;
		}
		//몬스터들은 랜덤으로 움직인다.
		if (_directionTime + _directionWorldTime <= TIMEMANAGER->getWorldTime())
		{
			_rndDirection = RND->getInt(4);
			_rndState = RND->getInt(2);

			if (_rndDirection == 0)
			{
				_enemy.direction = BALLMONSTER_DIRECTION_DOWN;

				if (_rndState == 0)	_enemy.state = BALLMONSTER_STATE_IDLE;
				else _enemy.state = BALLMONSTER_STATE_MOVE;
			}
			else if (_rndDirection == 1)
			{
				_enemy.direction = BALLMONSTER_DIRECTION_UP;

				if (_rndState == 0)	_enemy.state = BALLMONSTER_STATE_IDLE;
				else _enemy.state = BALLMONSTER_STATE_MOVE;
			}
			else if (_rndDirection == 2)
			{
				_enemy.direction = BALLMONSTER_DIRECTION_RIGHT;

				if (_rndState == 0)	_enemy.state = BALLMONSTER_STATE_IDLE;
				else _enemy.state = BALLMONSTER_STATE_MOVE;
			}
			else if (_rndDirection == 3)
			{
				_enemy.direction = BALLMONSTER_DIRECTION_LEFT;

				if (_rndState == 0)	_enemy.state = BALLMONSTER_STATE_IDLE;
				else _enemy.state = BALLMONSTER_STATE_MOVE;
			}
			_directionWorldTime = TIMEMANAGER->getWorldTime();
		}
	}
	else if (_enemy.moveType == FOLLOW_MOVE_TYPE)
	{
		switch (_enemy.state)
		{
		case BALLMONSTER_STATE_MOVE:
			if (_enemy.direction == BALLMONSTER_DIRECTION_UP)
			{
				_enemy.moveAngle = PI / 2;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "upMove");
			}
			else if (_enemy.direction == BALLMONSTER_DIRECTION_DOWN)
			{
				_enemy.moveAngle = (PI / 180) * 270;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downMove");
			}
			else if (_enemy.direction == BALLMONSTER_DIRECTION_RIGHT)
			{
				_enemy.moveAngle = PI2;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightMove");
			}
			else if (_enemy.direction == BALLMONSTER_DIRECTION_LEFT)
			{
				_enemy.moveAngle = PI;
				_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "leftMove");
			}
			_enemy.motion->start();

			_enemy.x += cosf(_enemy.moveAngle) * _enemy.speed;
			_enemy.y += -sinf(_enemy.moveAngle) * _enemy.speed;
			break;
		}
	}

}
