#include "stdafx.h"
#include "enemyManager.h"


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
	_fireMonsterBullet->init("fireMonster", WINSIZEX, 10);

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

	//불총알 발사함수
	fireMonsterBulletFire();

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
	//렌더링 모음 함수
	enemyDraw();
	//불몬스터 총알 렌더링
	for (int i = 0; i < _fireMonsterBullet->getVFireBullet().size(); i++)
	{
		_fireMonsterBullet->render(_fireMonsterBullet->getVFireBullet()[i].viewX, _fireMonsterBullet->getVFireBullet()[i].viewY);
	}
	char str[128];

	
	sprintf_s(str, "angle : %f", (_vBallMonster.back()->getTargetDistance()));
	TextOut(getMemDC(), 300, 100, str, strlen(str));

	Rectangle(getMemDC(), _playerRc);
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

//불총알 발사
void enemyManager::fireMonsterBulletFire()
{
	for (_viFireMonster = _vFireMonster.begin(); _viFireMonster != _vFireMonster.end(); _viFireMonster++)
	{
		//파이어 몬스터가 쏜 총알의 카운트 발사가 true라면
		if ((*_viFireMonster)->fireBulletCountFire() == true)
		{
			RECT fireRc; //불몬스터 렉트
			fireRc = (*_viFireMonster)->getRect();

			//불몬스터로부터 불총알 발사
			_fireMonsterBullet->fire(fireRc.left + (fireRc.right - fireRc.left) / 2, fireRc.top + (fireRc.bottom - fireRc.top) / 2, getAngle(fireRc.left, fireRc.top, _playerRc.left, _playerRc.top), 3);
		}
	}
}

//에너미 공격들이 플레이어 충돌할 함수
void enemyManager::enemyAttackPlayerCollision()
{
	//파이어몬스터 총알 충돌
	for (int i = 0; i < _fireMonsterBullet->getVFireBullet().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_fireMonsterBullet->getVFireBullet()[i].rc, &_playerRc))
		{
			(*_fireMonsterBullet->setVFireBullet())[i].isCollision = true;
		}
	}

	//플레이어 렉트 임시용으로 만들어 충돌 실험용
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		(*_viBallMonster)->setTargetDistance(getDistance((*_viBallMonster)->getX(), (*_viBallMonster)->getY(), _x, _y));
		RECT temp;
		if (IntersectRect(&temp, &(*_viBallMonster)->getRangeRect(), &_playerRc))
		{
			(*_viBallMonster)->setMoveType(FOLLOW_MOVE_TYPE); //충돌하면 따라가는 타입으로
			//(*_viBallMonster)->setState(BALLMONSTER_STATE_MOVE);

			switch ((*_viBallMonster)->getState())
			{
			case BALLMONSTER_STATE_IDLE:
			case BALLMONSTER_STATE_MOVE:

				(*_viBallMonster)->setTargetAngle(getAngle((*_viBallMonster)->getX(), (*_viBallMonster)->getY(), _x, _y));

				
				
				if ((*_viBallMonster)->getTargetDistance() > 5)
				{
					if (((*_viBallMonster)->getTargetAngle() < (PI / 180) * 25 && (*_viBallMonster)->getTargetAngle() >= 0) ||
						((*_viBallMonster)->getTargetAngle() > (PI / 180) * 335 && (*_viBallMonster)->getTargetAngle() <= (PI / 180) * 360))
					{
						(*_viBallMonster)->setDirection(BALLMONSTER_DIRECTION_RIGHT);
					}
					else if ((*_viBallMonster)->getTargetAngle() < (PI / 180) * 115 && (*_viBallMonster)->getTargetAngle() > (PI / 180) * 65)
					{
						(*_viBallMonster)->setDirection(BALLMONSTER_DIRECTION_UP);
					}
					else if ((*_viBallMonster)->getTargetAngle() > (PI / 180) * 155 && (*_viBallMonster)->getTargetAngle() < (PI / 180) * 205)
					{
						(*_viBallMonster)->setDirection(BALLMONSTER_DIRECTION_LEFT);
					}
					else if ((*_viBallMonster)->getTargetAngle() > (PI / 180) * 245 && (*_viBallMonster)->getTargetAngle() < (PI / 180) * 295)
					{
						(*_viBallMonster)->setDirection(BALLMONSTER_DIRECTION_DOWN);
					}
				}
				else
				{
					(*_viBallMonster)->setState(BALLMONSTER_STATE_IDLE);
				}
				

				break;
			}
		}
	
		else if((*_viBallMonster)->getTargetDistance() < 160)
		{
			(*_viBallMonster)->setMoveType(BASIC_MOVE_TYPE);
		}

	}

	//for (int i = 0; i < _vKnightMonster.size(); i++)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_vKnightMonster[i]->getRangeRect(), &_playerRc))
	//	{
	//		switch (_vKnightMonster[i]->getState())
	//		{
	//		case KNIGHTMONSTER_STATE_ATTACK:
	//			_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DOWN_ATTACK);
	//			break;

	//			_vKnightMonster[i]->setDirection(KNIGHTMONSTER_UP_ATTACK);
	//			break;

	//			if (_vKnightMonster[i]->getRangeRect().left <= _playerRc.right && _vKnightMonster[i]->getRangeRect().right > _playerRc.left)
	//			_vKnightMonster[i]->setDirection(KNIGHTMONSTER_LEFT_ATTACK);
	//			break;

	//			if (_vKnightMonster[i]->getRangeRect().right >= _playerRc.left && _vKnightMonster[i]->getRangeRect().left < _playerRc.right)
	//			_vKnightMonster[i]->setDirection(KNIGHTMONSTER_RIGHT_ATTACK);
	//			break;
	//		
	//		}
	//	}
	//}
}

//에너미들이 죽을함수
void enemyManager::enemyDead()
{
}

//에너미들이 죽은다음 리스폰할 함수
void enemyManager::enemyRespon()
{
}
