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
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "idleORmove", imageName, idleORmove, 4, MOVEFPS, true);

	int dead[] = { 5, 6, 7, 8, 9, 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "dead", imageName, dead, 6, 4, false);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "idleORmove");
	
	return S_OK;
}

void fireMonster::release()
{
}

void fireMonster::update()
{
	enemy::update();

	move();

	//알파값조정
	if (_enemy.isHit == true)
	{
		_enemy.alphaValue -= 10;

		if (_enemy.alphaValue <= 80)
		{
			_enemy.isHit = false;
			_enemy.alphaValue = 255;
		}
	}
	_enemy.rangeRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth() * 15, _enemy.image->getFrameHeight() * 8);
}

void fireMonster::render(float cameraX, float cameraY)
{
	//Rectangle(getMemDC(), _enemy.rc);
	//Rectangle(getMemDC(), _enemy.rangeRc);
	_enemy.viewX = _enemy.x - cameraX;
	_enemy.viewY = _enemy.y - cameraY;
	//_enemy.image->expandAniRenderCenter(getMemDC(), _enemy.viewX, _enemy.viewY, _enemy.motion, 2.f, 2.f);
	_enemy.image->alphaAniRenderCenter(getMemDC(), _enemy.viewX, _enemy.viewY, _enemy.motion, _enemy.alphaValue);
}

void fireMonster::move()
{
	//상태에 따라 프레임 동작
	if (_enemy.moveType == BASIC_MOVE_TYPE)
	{
		switch (_enemy.state)
		{
		case FIREMONSTER_STATE_IDLE:
		case FIREMONSTER_STATE_MOVE:

			if (_enemy.state == FIREMONSTER_STATE_MOVE)
			{
				if (_enemy.direction == FIREMONSTER_DIRECTION_RIGHT)
				{
					_enemy.moveAngle = PI2;
					_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
				}
				else if (_enemy.direction == FIREMONSTER_DIRECTION_LEFT)
				{
					_enemy.moveAngle = PI;
					_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
				}
				else if (_enemy.direction == FIREMONSTER_DIRECTION_UP)
				{
					_enemy.moveAngle = PI / 2;
					_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
				}
				else if (_enemy.direction == FIREMONSTER_DIRECTION_DOWN)
				{
					_enemy.moveAngle = (PI / 180) * 270;
					_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
				}

				_enemy.x += cosf(_enemy.moveAngle) * _enemy.speed;
				_enemy.y += -sinf(_enemy.moveAngle) * _enemy.speed;
			}
			_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "idleORmove");
			_enemy.motion->start();
			break;
		}

		//몬스터들은 랜덤으로 움직인다.
		if (_directionTime + _enemy.directionWorldTime <= TIMEMANAGER->getWorldTime())
		{
			_rndDirection[FIREMONSTER] = RND->getInt(4);
			_rndState[FIREMONSTER] = RND->getInt(2);

			if (_rndDirection[FIREMONSTER] == 0)
			{
				_enemy.direction = FIREMONSTER_DIRECTION_DOWN;
			}
			else if (_rndDirection[FIREMONSTER] == 1)
			{
				_enemy.direction = FIREMONSTER_DIRECTION_UP;
			}
			else if (_rndDirection[FIREMONSTER] == 2)
			{
				_enemy.direction = FIREMONSTER_DIRECTION_RIGHT;
			}
			else if (_rndDirection[FIREMONSTER] == 3)
			{
				_enemy.direction = FIREMONSTER_DIRECTION_LEFT;
			}
			if (_rndState[FIREMONSTER] == 0)	_enemy.state = FIREMONSTER_STATE_IDLE;
			else _enemy.state = FIREMONSTER_STATE_MOVE;
			_enemy.directionWorldTime = TIMEMANAGER->getWorldTime(); //시간갱신
		}
	}
	else if (_enemy.moveType == FOLLOW_MOVE_TYPE)
	{
		switch (_enemy.state)
		{
		case FIREMONSTER_STATE_MOVE:

			if (_enemy.direction == FIREMONSTER_DIRECTION_RIGHT)
			{
				_enemy.moveAngle = PI2;
				_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
			}
			else if (_enemy.direction == FIREMONSTER_DIRECTION_LEFT)
			{
				_enemy.moveAngle = PI;
				_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
			}
			else if (_enemy.direction == FIREMONSTER_DIRECTION_UP)
			{
				_enemy.moveAngle = PI / 2;
				_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
			}
			else if (_enemy.direction == FIREMONSTER_DIRECTION_DOWN)
			{
				_enemy.moveAngle = (PI / 180) * 270;
				_enemy.tileCollisionRc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
			}

			_enemy.x += cosf(_enemy.moveAngle) * _enemy.speed;
			_enemy.y += -sinf(_enemy.moveAngle) * _enemy.speed;
			
			_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "idleORmove");
			_enemy.motion->start();

			break;
		case FIREMONSTER_STATE_DEAD:
			_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "dead");
			_enemy.motion->start();
			break;
		}
	}
}

//총알 카운트 발사할 함수
bool fireMonster::fireBulletCountFire()
{
	_fireCount++;

	if (_fireCount % 100 == 0)
	{
		_fireCount = 0;
		return true;
	}
	return false;
}
