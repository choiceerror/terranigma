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
	_enemy.image->setAlpahBlend(true);

	int upIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upIdle", imageName, upIdle, 1, MOVEFPS, true);

	int upMove[] = { 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upMove", imageName, upMove, 3, MOVEFPS, true);

	int downIdle[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downIdle", imageName, downIdle, 1, MOVEFPS, true);

	int downMove[] = { 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downMove", imageName, downMove, 3, MOVEFPS, true);

	int rightIdle[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightIdle", imageName, rightIdle, 1, MOVEFPS, true);

	int rightMove[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightMove", imageName, rightMove, 3, MOVEFPS, true);

	int leftIdle[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftIdle", imageName, leftIdle, 1, MOVEFPS, true);

	int leftMove[] = { 13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftMove", imageName, leftMove, 3, MOVEFPS, true);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightMove");
	_isOne = false;

	return S_OK;
}

void ballMonster::release()
{
}

void ballMonster::update()
{
	enemy::update();
	move();
	//한번만 공격하기위함.
	if (_enemy.isAttack == true && _enemy.isOneTime == false)
	{
		//공격시간 갱신
		_enemy.attackWorldTime = TIMEMANAGER->getWorldTime();
		_enemy.isOneTime = true;  //한번만 시간갱신을 받기위함.
	}

	//공격상태가 아니라면
	if (!_enemy.isAttack)
	{
		_enemy.isOneTime = false; 
	}

	//알파값조정
	if (_enemy.isHit == true)
	{
		_enemy.alphaValue -= 20;

		if (_enemy.alphaValue <= 80)
		{
			_enemy.isHit = false;
			_enemy.alphaValue = 255;
		}
	}
	_enemy.rangeRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth() * 15, _enemy.image->getFrameHeight() * 15);
}

void ballMonster::render(float cameraX, float cameraY)
{
	//Rectangle(getMemDC(), _enemy.rangeRc);
	//Rectangle(getMemDC(), _enemy.rc);
	_enemy.viewX = _enemy.x - cameraX;
	_enemy.viewY = _enemy.y - cameraY;
	_enemy.image->alphaAniRenderCenter(getMemDC(), _enemy.viewX, _enemy.viewY, _enemy.motion, _enemy.alphaValue);
	//_enemy.image->expandAniRenderCenter(getMemDC(), _enemy.viewX, _enemy.viewY, _enemy.motion, 2.f , 2.f);

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
		if (_directionTime + _directionWorldTime <= TIMEMANAGER->getWorldTime() && _enemy.isAttack == false)
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
		case BALLMONSTER_STATE_ATTACK:
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
