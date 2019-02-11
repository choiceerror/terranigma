#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_playerRc = RectMakeCenter(_x, _y, 100, 100);

	_fireMonsterBullet = new fireMonsterBullet;
	_fireMonsterBullet->init("fireMonster", WINSIZEX / 2, 10);
	_fireBulletSpeed = 5;

	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_fireMonsterBullet);
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		SAFE_DELETE((*_viBallMonster));
	}
	for (_viFireMonster = _vFireMonster.begin(); _viFireMonster != _vFireMonster.end(); _viFireMonster++)
	{
		SAFE_DELETE((*_viFireMonster));
	}
	for (_viKnightMonster = _vKnightMonster.begin(); _viKnightMonster != _vKnightMonster.end(); _viKnightMonster++)
	{
		SAFE_DELETE((*_viKnightMonster));
	}
}

void enemyManager::update()
{
	//업데이트 모음 함수
	updateCollection();

	//에너미 공격 플레이어 충돌함수
	enemyAttackPlayerCollision();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 3;
	}
	_playerRc = RectMakeCenter(_x, _y, 100, 100);

}

void enemyManager::render()
{
	Rectangle(getMemDC(), _playerRc);
	//렌더링 모음 함수
	enemyDraw();
}

//업데이트 모음
void enemyManager::updateCollection()
{
	//불몬스터 업데이트
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		(*_viBallMonster)->update(0, 0);
	}
	//파이어몬스터 업데이트
	for (_viFireMonster = _vFireMonster.begin(); _viFireMonster != _vFireMonster.end(); _viFireMonster++)
	{
		(*_viFireMonster)->update(0, 0);
	}
	//나이트몬스터 업데이트
	for (_viKnightMonster = _vKnightMonster.begin(); _viKnightMonster != _vKnightMonster.end(); _viKnightMonster++)
	{
		(*_viKnightMonster)->update(0, 0);
	}
	//파이어몬스터 총알 업데이트
	_fireMonsterBullet->update(0, 0);
}

//렌더링 모음
void enemyManager::enemyDraw()
{
	//볼몬스터 렌더링
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		(*_viBallMonster)->render((*_viBallMonster)->getViewX(), (*_viBallMonster)->getViewY());
	}
	//파이어몬스터 렌더링
	for (_viFireMonster = _vFireMonster.begin(); _viFireMonster != _vFireMonster.end(); _viFireMonster++)
	{
		(*_viFireMonster)->render((*_viFireMonster)->getViewX(), (*_viFireMonster)->getViewY());
	}
	//나이트몬스터 렌더링
	for (_viKnightMonster = _vKnightMonster.begin(); _viKnightMonster != _vKnightMonster.end(); _viKnightMonster++)
	{
		(*_viKnightMonster)->render((*_viKnightMonster)->getViewX(), (*_viKnightMonster)->getViewY());
	}
	//불몬스터 총알 렌더링
	for (int i = 0; i < _fireMonsterBullet->getVFireBullet().size(); i++)
	{
		_fireMonsterBullet->render(_fireMonsterBullet->getVFireBullet()[i].viewX, _fireMonsterBullet->getVFireBullet()[i].viewY);
	}
}

//에너미 셋팅
void enemyManager::setEnemy()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ballMonster* bm;
			bm = new ballMonster;

			bm->init("ball", "ballMonster", 500 + j * 100, 100 + i * 100, j, i, 100);
			_vBallMonster.push_back(bm);

			fireMonster* fm;
			fm = new fireMonster;

			fm->init("fire", "fireMonster", 100 + j * 100, 500 + i * 100, j, i, 200);
			_vFireMonster.push_back(fm);


		}
	}
	knightMonster* km;
	km = new knightMonster;

	km->init("knight", "knightMonster", 1000, 500, 0, 0, 300);
	_vKnightMonster.push_back(km);
}

//에너미 공격들이 플레이어 충돌할 함수
void enemyManager::enemyAttackPlayerCollision()
{
	//플레이어 렉트 임시용으로 만들어 충돌 실험용 공몬스터
	for (int i = 0; i < _vBallMonster.size(); i++)
	{
		//몬스터와 플레이어간의 거리를 구해줌.
		_vBallMonster[i]->setTargetDistance(getDistance(_vBallMonster[i]->getX(), _vBallMonster[i]->getY(), _x, _y));
		RECT temp;
		if (IntersectRect(&temp, &_vBallMonster[i]->getRangeRect(), &_playerRc))
		{
			_vBallMonster[i]->setMoveType(FOLLOW_MOVE_TYPE); //충돌하면 따라가는 타입으로
			_vBallMonster[i]->setState(BALLMONSTER_STATE_MOVE); //그리고 계속움직임.
			_vBallMonster[i]->setTargetAngle(getAngle(_vBallMonster[i]->getX(), _vBallMonster[i]->getY(), _x, _y)); //몬스터와 플레이어간의 각도 구해줌.
			switch (_vBallMonster[i]->getState())
			{
			case BALLMONSTER_STATE_IDLE:
			case BALLMONSTER_STATE_MOVE:

				if (_vBallMonster[i]->getIsAttack() == false)
				{
					//오른쪽각도 충돌범위일때만 오른쪽으로 쫓아오게
					if ((_vBallMonster[i]->getTargetAngle() < (PI / 180) * 25 && _vBallMonster[i]->getTargetAngle() > 0) ||
						(_vBallMonster[i]->getTargetAngle() > (PI / 180) * 335 && _vBallMonster[i]->getTargetAngle() < PI2))
					{
						_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_RIGHT);
					}
					//위에각도 충돌범위일때만 위에 쫓아오게
					else if (_vBallMonster[i]->getTargetAngle() > (PI / 180) * 65 && _vBallMonster[i]->getTargetAngle() < (PI / 180) * 115)
					{
						_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_UP);
					}
					//왼쪽각도
					else if (_vBallMonster[i]->getTargetAngle() > (PI / 180) * 155 && _vBallMonster[i]->getTargetAngle() < (PI / 180) * 205)
					{
						_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_LEFT);
					}
					//아래각도
					else if (_vBallMonster[i]->getTargetAngle() > (PI / 180) * 245 && _vBallMonster[i]->getTargetAngle() < (PI / 180) * 295)
					{
						_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_DOWN);
					}
				}
				break;
			}
		}
		//거리가 멀어지면 다시 기본움직임타입으로
		else if (_vBallMonster[i]->getTargetDistance() > 480 && _vBallMonster[i]->getIsAttack() == false)
		{
			_vBallMonster[i]->setMoveType(BASIC_MOVE_TYPE);
		}

		//거리가 가까워지면 공격하고 시간텀마다 공격하기 위함.
		if (_vBallMonster[i]->getTargetDistance() < 300 && 1.5f + _vBallMonster[i]->getWorldTime() <= TIMEMANAGER->getWorldTime())
		{
			_vBallMonster[i]->setIsAttack(true);
		}

		//공격상태라면
		if (_vBallMonster[i]->getIsAttack() == true)
		{
			// 0.5초전에 공격각도 잡기위함
			if (0.5f + _vBallMonster[i]->getAttackWorldTime() >= TIMEMANAGER->getWorldTime())
			{
				_vBallMonster[i]->setAttackAngle(getAngle(_vBallMonster[i]->getX(), _vBallMonster[i]->getY(), _x, _y));
				//여기는 처음에 스피드 0이랑 프레임속도 빠르게 해서 공격을 준비함.
				_vBallMonster[i]->getMotion()->setFPS(30);
				_vBallMonster[i]->setSpeed(0);
			}
			// 1초에서 1.5초 사이에 가속도주면서 공격각도로 공격
			else if (1.0f + _vBallMonster[i]->getAttackWorldTime() <= TIMEMANAGER->getWorldTime() && 1.5f + _vBallMonster[i]->getAttackWorldTime() > TIMEMANAGER->getWorldTime())
			{
				_vBallMonster[i]->setSpeed(_vBallMonster[i]->getSpeed() + 0.3f);
				_vBallMonster[i]->setX(_vBallMonster[i]->getX() + cosf(_vBallMonster[i]->getAttackAngle()) * _vBallMonster[i]->getSpeed());
				_vBallMonster[i]->setY(_vBallMonster[i]->getY() + -sinf(_vBallMonster[i]->getAttackAngle()) * _vBallMonster[i]->getSpeed());
			}

			//1.5초에서 2초사이엔 스피드와 프레임 원래대로 돌려줌.
			else if (1.5f + _vBallMonster[i]->getAttackWorldTime() <= TIMEMANAGER->getWorldTime() && 2.0f + _vBallMonster[i]->getAttackWorldTime() > TIMEMANAGER->getWorldTime())
			{
				_vBallMonster[i]->setSpeed(1.0f);
				_vBallMonster[i]->getMotion()->setFPS(5);
			}

			//2초가 지나면 공격끔.
			else if (2.0f + _vBallMonster[i]->getAttackWorldTime() <= TIMEMANAGER->getWorldTime())
			{
				_vBallMonster[i]->setMoveType(BASIC_MOVE_TYPE);
				_vBallMonster[i]->setAttackWorldTime(TIMEMANAGER->getWorldTime());
				_vBallMonster[i]->setWorldTime(TIMEMANAGER->getWorldTime());
				_vBallMonster[i]->setIsAttack(false);
			}
		}

		//부딪혀도 다꺼줌.
		if (IntersectRect(&temp, &_vBallMonster[i]->getRect(), &_playerRc))
		{
			_vBallMonster[i]->getMotion()->setFPS(5);
			_vBallMonster[i]->setWorldTime(TIMEMANAGER->getWorldTime());
			_vBallMonster[i]->setAttackWorldTime(TIMEMANAGER->getWorldTime());
			_vBallMonster[i]->setIsAttack(false);
			_vBallMonster[i]->setSpeed(1.0f);
			_vBallMonster[i]->setMoveType(BASIC_MOVE_TYPE);
		}
	}

	//불몬스터
	for (int i = 0; i < _vFireMonster.size(); i++)
	{
		RECT temp;
		//거리 구해주고
		_vFireMonster[i]->setTargetDistance(getDistance(_vFireMonster[i]->getX(), _vFireMonster[i]->getY(), _x, _y));

		if (IntersectRect(&temp, &_vFireMonster[i]->getRangeRect(), &_playerRc))
		{
			//각도 구해줌
			_vFireMonster[i]->setTargetAngle(getAngle(_vFireMonster[i]->getX(), _vFireMonster[i]->getY(), _x, _y));
			_vFireMonster[i]->setMoveType(FOLLOW_MOVE_TYPE);
			_vFireMonster[i]->setState(FIREMONSTER_STATE_MOVE);
			switch (_vFireMonster[i]->getState())
			{
			case FIREMONSTER_STATE_IDLE:
			case FIREMONSTER_STATE_MOVE:
				if ((_vFireMonster[i]->getTargetAngle() < (PI / 180) * 25 && _vFireMonster[i]->getTargetAngle() > 0) ||
					(_vFireMonster[i]->getTargetAngle() > (PI / 180) * 335 && _vFireMonster[i]->getTargetAngle() < PI2))
				{
					_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_RIGHT);
				}
				else if (_vFireMonster[i]->getTargetAngle() > (PI / 180) * 65 && _vFireMonster[i]->getTargetAngle() < (PI / 180) * 115)
				{
					_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_UP);
				}
				else if (_vFireMonster[i]->getTargetAngle() > (PI / 180) * 155 && _vFireMonster[i]->getTargetAngle() < (PI / 180) * 205)
				{
					_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_LEFT);
				}
				else if (_vFireMonster[i]->getTargetAngle() > (PI / 180) * 245 && _vFireMonster[i]->getTargetAngle() < (PI / 180) * 295)
				{
					_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_DOWN);
				}
				//거리가 가까워지면 공격
				if (_vFireMonster[i]->getTargetDistance() < 400)
				{
					fireMonsterBulletFire(i); //불총알 발사
				}
				break;
			}
		}
		else if (_vFireMonster[i]->getTargetDistance() > 500)
		{
			_vFireMonster[i]->setMoveType(BASIC_MOVE_TYPE);
		}

	}

	//기사 몬스터
	for (int i = 0; i < _vKnightMonster.size(); i++)
	{
		RECT temp;
		//기사와 플레이어간의 거리 구해줌.
		_vKnightMonster[i]->setTargetDistance(getDistance(_vKnightMonster[i]->getX(), _vKnightMonster[i]->getY(), _x, _y));
		//판정렉트와 충돌하면
		if (IntersectRect(&temp, &_vKnightMonster[i]->getRangeRect(), &_playerRc))
		{
			//기사와 플레이어간의 각도 구해줌.
			_vKnightMonster[i]->setTargetAngle(getAngle(_vKnightMonster[i]->getX(), _vKnightMonster[i]->getY(), _x, _y));
			_vKnightMonster[i]->setMoveType(FOLLOW_MOVE_TYPE); //따라가는 타입으로.
			switch (_vKnightMonster[i]->getState())
			{
			case KNIGHTMONSTER_STATE_IDLE:
			case KNIGHTMONSTER_STATE_MOVE:

				if ((_vKnightMonster[i]->getTargetAngle() < (PI / 180) * 25 && _vKnightMonster[i]->getTargetAngle() > 0) ||
					(_vKnightMonster[i]->getTargetAngle() > (PI / 180) * 335 && _vKnightMonster[i]->getTargetAngle() < PI2))
				{
					_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_RIGHT);
				}
				else if (_vKnightMonster[i]->getTargetAngle() > (PI / 180) * 65 && _vKnightMonster[i]->getTargetAngle() < (PI / 180) * 115)
				{
					_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_UP);
				}
				else if (_vKnightMonster[i]->getTargetAngle() > (PI / 180) * 155 && _vKnightMonster[i]->getTargetAngle() < (PI / 180) * 205)
				{
					_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_LEFT);
				}
				else if (_vKnightMonster[i]->getTargetAngle() > (PI / 180) * 245 && _vKnightMonster[i]->getTargetAngle() < (PI / 180) * 295)
				{
					_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_DOWN);
				}

				//거리가 가까워지면 공격
				if (_vKnightMonster[i]->getTargetDistance() < 150)
				{
					_vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_ATTACK);
				}
				else _vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_MOVE); //거리가 좀멀어지면 움직여라.

				break;
			}
		}
		//일정거리 지나면 다시 기본움직임 타입으로
		else if (_vKnightMonster[i]->getTargetDistance() > 500)
		{
			_vKnightMonster[i]->setMoveType(BASIC_MOVE_TYPE);
		}
	}
}

//불총알 발사
void enemyManager::fireMonsterBulletFire(int i)
{
	//파이어 몬스터가 쏜 총알의 카운트 발사가 true라면
	if (_vFireMonster[i]->fireBulletCountFire() == true)
	{
		RECT fireRc; //불몬스터 렉트
		fireRc = _vFireMonster[i]->getRect();

		//불몬스터가 총알을 방향별로 쏘게함.
		for (int i = 0; i < 4; i++)
		{
			_fireMonsterBullet->fire(fireRc.left + (fireRc.right - fireRc.left) / 2, fireRc.top + (fireRc.bottom - fireRc.top) / 2, PI + i * (PI / 2), _fireBulletSpeed);
		}
	}

	//파이어몬스터 총알 충돌
	for (int i = 0; i < _fireMonsterBullet->getVFireBullet().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_fireMonsterBullet->getVFireBullet()[i].rc, &_playerRc))
		{
			(*_fireMonsterBullet->setVFireBullet())[i].isCollision = true;
		}
	}
}

//에너미들이 죽을함수
void enemyManager::enemyDead()
{
}

//에너미들이 죽은다음 리스폰할 함수
void enemyManager::enemyRespon()
{
}
