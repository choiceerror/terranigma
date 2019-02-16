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
	_fireMonsterBullet = new fireMonsterBullet;
	_fireMonsterBullet->init("fireMonster", GAMESIZEX / 2, 10);
	_fireBulletSpeed = 5;

	_objectRc = RectMake(80, 355, 160, 125);
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

	//에너미들의 타일검출
	tileCheckObjectCollision();

	//에너미 AI 함수
	enemyAI();

	//플레이어 공격에 에너미들이 맞을 함수
	playerAttackEnemyCollision();

	//에너미들이 죽을함수
	enemyDead();
}

void enemyManager::render(float cameraX, float cameraY)
{
	//Rectangle(getMemDC(), _objectRc);
	//Rectangle(getMemDC(), _playerAttackRc);
	//렌더링 모음 함수
	drawAll(cameraX, cameraY);

	//char str[128];

	for (int i = 0; i < _vKnightMonster.size(); i++)
	{
		//sprintf_s(str, "distance : %f", _vKnightMonster[i]->getTargetDistance());
		//TextOut(getMemDC(), 100, 200 + i * 20, str, strlen(str));

		//sprintf_s(str, "idX : %d", _vKnightMonster[i]->getIdX());
		//TextOut(getMemDC(), 100, 400 + i * 20, str, strlen(str));


		//sprintf_s(str, "idY : %d", _vKnightMonster[i]->getIdY());
		//TextOut(getMemDC(), 100, 600 + i * 20, str, strlen(str));

		//sprintf_s(str, "state : %d", _vKnightMonster[i]->getState());
		//TextOut(getMemDC(), 100, 400 + i * 20, str, strlen(str));

		//sprintf_s(str, "viewY : %f", _vKnightMonster[i]->getViewY());
		//TextOut(getMemDC(), 100, 300 + i * 20, str, strlen(str));

		//sprintf_s(str, "x : %f", _vKnightMonster[i]->getX());
		//TextOut(getMemDC(), 300, 100 + i * 20, str, strlen(str));

		//sprintf_s(str, "hp : %d", _vKnightMonster[i]->getCurrentHP());
		//TextOut(getMemDC(), 300, 200 + i * 20, str, strlen(str));
	}

	for (int i = 0; i < _vBallMonster.size(); i++)
	{
		//sprintf_s(str, "targetDistance : %f", _vBallMonster[i]->getTargetDistance());
		//TextOut(getMemDC(), 600, 100 + i * 20, str, strlen(str));

		//sprintf_s(str, "ballviewX : %f", _vBallMonster[i]->getViewX());
		//TextOut(getMemDC(), 600, 200 + i * 20, str, strlen(str));

		//sprintf_s(str, "ballviewY : %f", _vBallMonster[i]->getViewY());
		//TextOut(getMemDC(), 600, 300 + i * 20, str, strlen(str));

		//sprintf_s(str, "speed : %f", _vBallMonster[i]->getSpeed());
		//TextOut(getMemDC(), 800, 100 + i * 20, str, strlen(str));

		//sprintf_s(str, "bally : %f", _vBallMonster[i]->getY());
		//TextOut(getMemDC(), 800, 200 + i * 20, str, strlen(str));

		//sprintf_s(str, "isAttack : %d", _vBallMonster[i]->getIsAttack());
		//TextOut(getMemDC(), 100, 200 + i * 20, str, strlen(str));
	}

	//for (int i = 0; i < _vFireMonster.size(); i++)
	//{
	//	sprintf_s(str, "isAttack : %d", _vFireMonster[i]->getIsAttack());
	//	TextOut(getMemDC(), 600, 100 + i * 20, str, strlen(str));
	//}
}

//업데이트 모음
void enemyManager::updateCollection()
{
	//불몬스터 업데이트
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		(*_viBallMonster)->update();
	}
	//파이어몬스터 업데이트
	for (_viFireMonster = _vFireMonster.begin(); _viFireMonster != _vFireMonster.end(); _viFireMonster++)
	{
		(*_viFireMonster)->update();
	}
	//나이트몬스터 업데이트
	for (_viKnightMonster = _vKnightMonster.begin(); _viKnightMonster != _vKnightMonster.end(); _viKnightMonster++)
	{
		(*_viKnightMonster)->update();
	}

	//파이어몬스터 총알 업데이트
	_fireMonsterBullet->update();
}

//렌더링 모음
void enemyManager::drawAll(float cameraX, float cameraY)
{
	//볼몬스터 렌더링
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		(*_viBallMonster)->render(cameraX, cameraY);
	}
	//파이어몬스터 렌더링
	for (_viFireMonster = _vFireMonster.begin(); _viFireMonster != _vFireMonster.end(); _viFireMonster++)
	{
		(*_viFireMonster)->render(cameraX, cameraY);
	}
	//나이트몬스터 렌더링
	for (_viKnightMonster = _vKnightMonster.begin(); _viKnightMonster != _vKnightMonster.end(); _viKnightMonster++)
	{
		(*_viKnightMonster)->render(cameraX, cameraY);
	}
	//불몬스터 총알 렌더링
	for (int i = 0; i < _fireMonsterBullet->getVFireBullet().size(); i++)
	{
		_fireMonsterBullet->render(cameraX, cameraY);
	}
}

//에너미 셋팅
void enemyManager::setEnemy()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ballMonster* bm;
			bm = new ballMonster;

			fireMonster* fm;
			fm = new fireMonster;
			if (_dungeonMap->getDungeonFloor() == DUNGEON_FLOOR::FIRST_FLOOR)
			{
				bm->init("ball", "ballMonster", GAMESIZEX / 4 + j * 300, 300 + i * 200, j, i, BALLMONSTER_HP);
				_vBallMonster.push_back(bm);

				fm->init("fire", "fireMonster", GAMESIZEX / 3 + j * 200, 500 + i * 300, j, i, FIREMONSTER_HP);
				_vFireMonster.push_back(fm);
			}
			else if (_dungeonMap->getDungeonFloor() == DUNGEON_FLOOR::SECOND_FLOOR)
			{
				bm->init("ball", "ballMonster", 200 + j * 700, 200 + i * 800, j, i, BALLMONSTER_HP);
				_vBallMonster.push_back(bm);

				fm->init("fire", "fireMonster", 200 + j * 680, 460 + i * 300, j, i, FIREMONSTER_HP);
				_vFireMonster.push_back(fm);

				knightMonster* km;
				km = new knightMonster;

				km->init("knight", "knightMonster", 2240 / 3 + j * 300, 1600 / 2 + i * 300, j, i, KNIGHTMONSTER_HP);
				_vKnightMonster.push_back(km);
			}
			
		}

		//밑에쪽 생성
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ballMonster* bm;
				bm = new ballMonster;
				if (_dungeonMap->getDungeonFloor() == DUNGEON_FLOOR::FIRST_FLOOR)
				{
					bm->init("ball", "ballMonster", GAMESIZEX / 4 + j * 300, 1500 + i * 500, j, i, BALLMONSTER_HP);
					_vBallMonster.push_back(bm);
				}
			}
		}
	}
}

//에너미들의 AI
void enemyManager::enemyAI()
{
	//공몬스터
	for (int i = 0; i < _vBallMonster.size(); i++)
	{
		//몬스터와 플레이어간의 거리를 구해줌.
		_vBallMonster[i]->setTargetDistance(getDistance(_vBallMonster[i]->getX(), _vBallMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY()));
		RECT temp;
		if (IntersectRect(&temp, &_vBallMonster[i]->getRangeRect(), &_player->getPlayerRc()))
		{
			_vBallMonster[i]->setMoveType(FOLLOW_MOVE_TYPE); //충돌하면 따라가는 타입으로
			_vBallMonster[i]->setState(BALLMONSTER_STATE_MOVE); //그리고 계속움직임.
			_vBallMonster[i]->setTargetAngle(getAngle(_vBallMonster[i]->getX(), _vBallMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY())); //몬스터와 플레이어간의 각도 구해줌.
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
		else if (_vBallMonster[i]->getTargetDistance() > 480)
		{
			_vBallMonster[i]->setMoveType(BASIC_MOVE_TYPE);
			_vBallMonster[i]->setIsAttack(false);
		}

		//거리가 가까워지면 공격하고 시간텀마다 공격하기 위함.
		if (_vBallMonster[i]->getTargetDistance() < 300 && 1.5f + _vBallMonster[i]->getWorldTime() <= TIMEMANAGER->getWorldTime() && _vBallMonster[i]->getMoveType() == FOLLOW_MOVE_TYPE)
		{
			_vBallMonster[i]->setIsAttack(true);
		}

		//공격상태라면
		if (_vBallMonster[i]->getIsAttack() == true && _vBallMonster[i]->getState() != BALLMONSTER_STATE_IDLE && _vBallMonster[i]->getState() == FOLLOW_MOVE_TYPE)
		{
			// 0.8초전에 공격각도 잡기위함
			if (0.8f + _vBallMonster[i]->getAttackWorldTime() >= TIMEMANAGER->getWorldTime())
			{
				_vBallMonster[i]->setAttackAngle(getAngle(_vBallMonster[i]->getX(), _vBallMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY()));
				//여기는 처음에 스피드 0이랑 프레임속도 빠르게 해서 공격을 준비함.
				_vBallMonster[i]->getMotion()->setFPS(40);
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

			//부딪혀도 다꺼줌.
			if (IntersectRect(&temp, &_vBallMonster[i]->getRect(), &_player->getPlayerRc()))
			{
				_vBallMonster[i]->getMotion()->setFPS(5);
				_vBallMonster[i]->setWorldTime(TIMEMANAGER->getWorldTime());
				_vBallMonster[i]->setAttackWorldTime(TIMEMANAGER->getWorldTime());
				_vBallMonster[i]->setIsAttack(false);
				_vBallMonster[i]->setSpeed(1.0f);
			}
		}

	}

	//불몬스터
	for (int i = 0; i < _vFireMonster.size(); i++)
	{
		RECT temp;
		//거리 구해주고
		_vFireMonster[i]->setTargetDistance(getDistance(_vFireMonster[i]->getX(), _vFireMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY()));

		if (IntersectRect(&temp, &_vFireMonster[i]->getRangeRect(), &_player->getPlayerRc()))
		{
			//각도 구해줌
			_vFireMonster[i]->setTargetAngle(getAngle(_vFireMonster[i]->getX(), _vFireMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY()));
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
					fireMonsterBulletFireCollision(i); //불총알 발사하고 충돌할 함수
				}
				break;
			}
		}
		else if (_vFireMonster[i]->getTargetDistance() > 500 && _vFireMonster[i]->getState() != FIREMONSTER_STATE_DEAD)
		{
			_vFireMonster[i]->setMoveType(BASIC_MOVE_TYPE);
		}

	}

	//기사 몬스터
	for (int i = 0; i < _vKnightMonster.size(); i++)
	{
		RECT temp;
		//기사와 플레이어간의 거리 구해줌.
		_vKnightMonster[i]->setTargetDistance(getDistance(_vKnightMonster[i]->getX(), _vKnightMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY()));

		//판정렉트와 충돌하면
		if (IntersectRect(&temp, &_vKnightMonster[i]->getRangeRect(), &_player->getPlayerRc()))
		{
			//기사와 플레이어간의 각도 구해줌.
			_vKnightMonster[i]->setTargetAngle(getAngle(_vKnightMonster[i]->getX(), _vKnightMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY()));
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
				break;
			}
		}
		//일정거리 지나면 다시 기본움직임 타입으로
		else if (_vKnightMonster[i]->getTargetDistance() > 500 && _vKnightMonster[i]->getMoveType() == FOLLOW_MOVE_TYPE)
		{
			_vKnightMonster[i]->setMoveType(BASIC_MOVE_TYPE);
		}

		//거리가 가까워지면 공격
		if (_vKnightMonster[i]->getTargetDistance() <= 100 && _vKnightMonster[i]->getMoveType() == FOLLOW_MOVE_TYPE)
		{
			_vKnightMonster[i]->setAttackAngle(getAngle(_vKnightMonster[i]->getX(), _vKnightMonster[i]->getY(), _player->getPlayerX(), _player->getPlayerY()));
			//오른쪽각도에 있으면 오른쪽공격으로
			if ((_vKnightMonster[i]->getAttackAngle() < (PI / 180) * 60 && _vKnightMonster[i]->getAttackAngle() > 0) ||
				(_vKnightMonster[i]->getAttackAngle() > (PI / 180) * 300 && _vKnightMonster[i]->getAttackAngle() < PI2))
			{
				_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_RIGHT);
				_vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_ATTACK);
			}
			//위에각도에 있으면 위쪽공격으로
			else if (_vKnightMonster[i]->getAttackAngle() > (PI / 180) * 60 && _vKnightMonster[i]->getAttackAngle() < (PI / 180) * 120)
			{
				_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_UP);
				_vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_ATTACK);
			}
			//왼쪽각도
			else if (_vKnightMonster[i]->getAttackAngle() > (PI / 180) * 120 && _vKnightMonster[i]->getAttackAngle() < (PI / 180) * 210)
			{
				_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_LEFT);
				_vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_ATTACK);
			}
			//아래각도
			else if (_vKnightMonster[i]->getAttackAngle() > (PI / 180) * 210 && _vKnightMonster[i]->getAttackAngle() < (PI / 180) * 300)
			{
				_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_DOWN);
				_vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_ATTACK);
			}
			_vKnightMonster[i]->setAttackWorldTime(TIMEMANAGER->getWorldTime());
		}
		//멀어지면 랜덤으로 움직임
		else if (_vKnightMonster[i]->getTargetDistance() > 100 && 1.0f + _vKnightMonster[i]->getAttackWorldTime() <= TIMEMANAGER->getWorldTime())
		{
			if (_vKnightMonster[i]->getRndState() == 0) _vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_MOVE);
			else _vKnightMonster[i]->setState(KNIGHTMONSTER_STATE_IDLE);
		}
	}
}

//플레이어 공격에 에너미들이 맞을 함수
void enemyManager::playerAttackEnemyCollision()
{
	//플레이어의 공격렉트
	//오른쪽 공격, 대쉬공격, 연속공격, 점프공격, 대쉬 점프공격
	if ((_player->getPlayerAni()->getFramePosArr().x >= 1 && _player->getPlayerAni()->getFramePosArr().x < 4 && _player->getPlayerAni()->getFramePosArr().y == 13)
		|| (_player->getPlayerAni()->getFramePosArr().x <= 2 && _player->getPlayerAni()->getFramePosArr().y == 28)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 180 && _player->getPlayerAni()->getFramePosArrOnce() <= 187)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 230 && _player->getPlayerAni()->getFramePosArrOnce() <= 235)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 279 && _player->getPlayerAni()->getFramePosArrOnce() <= 280))
	{
		_playerAttackRc = RectMakeCenter(_player->getPlayerX() + 30, _player->getPlayerY(), 100, 30);
	}
	//왼쪽 공격, 대쉬공격, 연속공격 , 점프공격, 대쉬 점프공격
	else if ((_player->getPlayerAni()->getFramePosArr().x >= 5 && _player->getPlayerAni()->getFramePosArr().y == 13)
		|| (_player->getPlayerAni()->getFramePosArr().x >= 4 && _player->getPlayerAni()->getFramePosArr().y == 28)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 192 && _player->getPlayerAni()->getFramePosArrOnce() <= 199)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 242 && _player->getPlayerAni()->getFramePosArrOnce() <= 247)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 291 && _player->getPlayerAni()->getFramePosArrOnce() <= 292))
	{
		_playerAttackRc = RectMakeCenter(_player->getPlayerX() - 30, _player->getPlayerY(), 100, 30);
	}
	//위공격, 대쉬공격, 연속공격, 점프공격, 대쉬 점프공격
	else if ((_player->getPlayerAni()->getFramePosArr().x >= 1 && _player->getPlayerAni()->getFramePosArr().x < 4 && _player->getPlayerAni()->getFramePosArr().y == 14)
		|| (_player->getPlayerAni()->getFramePosArr().x <= 2 && _player->getPlayerAni()->getFramePosArr().y == 29)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 204 && _player->getPlayerAni()->getFramePosArrOnce() <= 209)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 255 && _player->getPlayerAni()->getFramePosArrOnce() <= 259)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 303 && _player->getPlayerAni()->getFramePosArrOnce() <= 304))
	{
		_playerAttackRc = RectMakeCenter(_player->getPlayerX(), _player->getPlayerY() - 30, 30, 100);
	}
	//아래 공격, 대쉬공격, 연속공격, 점프공격, 대쉬 점프공격
	else if ((_player->getPlayerAni()->getFramePosArr().x >= 5 && _player->getPlayerAni()->getFramePosArr().y == 14)
		|| (_player->getPlayerAni()->getFramePosArr().x >= 4 && _player->getPlayerAni()->getFramePosArr().y == 29)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 216 && _player->getPlayerAni()->getFramePosArrOnce() <= 222)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 267 && _player->getPlayerAni()->getFramePosArrOnce() <= 271)
		|| (_player->getPlayerAni()->getFramePosArrOnce() >= 315 && _player->getPlayerAni()->getFramePosArrOnce() <= 316))
	{
		_playerAttackRc = RectMakeCenter(_player->getPlayerX(), _player->getPlayerY() + 30, 30, 100);
	}
	//공격끝나면 렉트없앰.
	else _playerAttackRc = RectMakeCenter(NULL, NULL, NULL, NULL);

	switch (_player->getPlayerState())
	{
	case PLAYER_ATTACK:
	case PLAYER_JUMP_ATTACK:
	case PLAYER_DASH_JUMP_ATTACK:
	case PLAYER_DASH_ATTACK:
	case PLAYER_COMBINATION:

		RECT temp;
		//기사몬스터
		for (int i = 0; i < _vKnightMonster.size(); i++)
		{
			if (IntersectRect(&temp, &_playerAttackRc, &_vKnightMonster[i]->getRect()))
			{
				_vKnightMonster[i]->setCurrentHP(_vKnightMonster[i]->getCurrentHP() - 10);
				_vKnightMonster[i]->setIsHit(true);
				if (_player->getPlayerDirection() == LEFT)
				{
					_vKnightMonster[i]->setX(_vKnightMonster[i]->getX() - 2);
				}
				else if (_player->getPlayerDirection() == RIGHT)
				{
					_vKnightMonster[i]->setX(_vKnightMonster[i]->getX() + 2);
				}
				else if (_player->getPlayerDirection() == UP)
				{
					_vKnightMonster[i]->setY(_vKnightMonster[i]->getY() - 2);
				}
				else if (_player->getPlayerDirection() == DOWN)
				{
					_vKnightMonster[i]->setY(_vKnightMonster[i]->getY() + 2);
				}
			}
		}

		//공몬스터
		for (int i = 0; i < _vBallMonster.size(); i++)
		{
			if (IntersectRect(&temp, &_playerAttackRc, &_vBallMonster[i]->getRect()))
			{
				_vBallMonster[i]->setIsHit(true);
				_vBallMonster[i]->setCurrentHP(_vBallMonster[i]->getCurrentHP() - 10);
				if (_player->getPlayerDirection() == LEFT)
				{
					_vBallMonster[i]->setX(_vBallMonster[i]->getX() - 2);
				}
				else if (_player->getPlayerDirection() == RIGHT)
				{
					_vBallMonster[i]->setX(_vBallMonster[i]->getX() + 2);
				}
				else if (_player->getPlayerDirection() == UP)
				{
					_vBallMonster[i]->setY(_vBallMonster[i]->getY() - 2);
				}
				else if (_player->getPlayerDirection() == DOWN)
				{
					_vBallMonster[i]->setY(_vBallMonster[i]->getY() + 2);
				}
			}
		}

		//불몬스터
		for (int i = 0; i < _vFireMonster.size(); i++)
		{
			if (IntersectRect(&temp, &_playerAttackRc, &_vFireMonster[i]->getRect()))
			{
				_vFireMonster[i]->setIsHit(true);
				_vFireMonster[i]->setCurrentHP(_vFireMonster[i]->getCurrentHP() - 10);
				if (_player->getPlayerDirection() == LEFT)
				{
					_vFireMonster[i]->setX(_vFireMonster[i]->getX() - 2);
				}
				else if (_player->getPlayerDirection() == RIGHT)
				{
					_vFireMonster[i]->setX(_vFireMonster[i]->getX() + 2);
				}
				else if (_player->getPlayerDirection() == UP)
				{
					_vFireMonster[i]->setY(_vFireMonster[i]->getY() - 2);
				}
				else if (_player->getPlayerDirection() == DOWN)
				{
					_vFireMonster[i]->setY(_vFireMonster[i]->getY() + 2);
				}
			}
		}
		break;
	}
}

//불총알 발사, 충돌함수
void enemyManager::fireMonsterBulletFireCollision(int num)
{
	//파이어 몬스터가 쏜 총알의 카운트 발사가 true라면
	if (_vFireMonster[num]->fireBulletCountFire() == true)
	{
		RECT fireRc; //불몬스터 렉트
		fireRc = _vFireMonster[num]->getRect();

		//불몬스터가 총알을 방향별로 쏘게함.
		for (int i = 0; i < 4; i++)
		{
			_fireMonsterBullet->fire(fireRc.left + (fireRc.right - fireRc.left) / 2, fireRc.top + (fireRc.bottom - fireRc.top) / 2, PI + i * (PI / 2), _fireBulletSpeed);
		}
	}

	//파이어몬스터 총알 충돌
	for (int i = 0; i < _fireMonsterBullet->getVFireBullet().size(); i++)
	{
		//타일 충돌렉트에 실제렉트 대입.
		(*_fireMonsterBullet->setVFireBullet())[i].tileCollisionRc = _fireMonsterBullet->getVFireBullet()[i].rc;

		//인덱스 정해주기
		(*_fireMonsterBullet->setVFireBullet())[i].idX = _fireMonsterBullet->getVFireBullet()[i].x / TileSIZE;
		(*_fireMonsterBullet->setVFireBullet())[i].idY = _fireMonsterBullet->getVFireBullet()[i].y / TileSIZE;

		//타일 인덱스로 검사 8방향 검사
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[0].x = _fireMonsterBullet->getVFireBullet()[i].idX - 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[0].y = _fireMonsterBullet->getVFireBullet()[i].idY;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[1].x = _fireMonsterBullet->getVFireBullet()[i].idX - 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[1].y = _fireMonsterBullet->getVFireBullet()[i].idY - 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[2].x = _fireMonsterBullet->getVFireBullet()[i].idX - 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[2].y = _fireMonsterBullet->getVFireBullet()[i].idY + 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[3].x = _fireMonsterBullet->getVFireBullet()[i].idX;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[3].y = _fireMonsterBullet->getVFireBullet()[i].idY - 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[4].x = _fireMonsterBullet->getVFireBullet()[i].idX;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[4].y = _fireMonsterBullet->getVFireBullet()[i].idY + 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[5].x = _fireMonsterBullet->getVFireBullet()[i].idX + 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[5].y = _fireMonsterBullet->getVFireBullet()[i].idY;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[6].x = _fireMonsterBullet->getVFireBullet()[i].idX + 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[6].y = _fireMonsterBullet->getVFireBullet()[i].idY - 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[7].x = _fireMonsterBullet->getVFireBullet()[i].idX + 1;
		(*_fireMonsterBullet->setVFireBullet())[i].tileIndex[7].y = _fireMonsterBullet->getVFireBullet()[i].idY + 1;


		RECT temp;
		for (int j = 0; j < 8; j++)
		{
			//타일에 부딪히면
			if (_dungeonMap->getAttr(_fireMonsterBullet->getVFireBullet()[i].tileIndex[j].x, _fireMonsterBullet->getVFireBullet()[i].tileIndex[j].y) == ATTR_UNMOVE
				&& IntersectRect(&temp, &_dungeonMap->getTile(_fireMonsterBullet->getVFireBullet()[i].tileIndex[j].x, _fireMonsterBullet->getVFireBullet()[i].tileIndex[j].y)->rc, &_fireMonsterBullet->getVFireBullet()[i].tileCollisionRc))
			{
				//총알 없애줌
				(*_fireMonsterBullet->setVFireBullet())[i].isCollision = true;
				break;
			}
			
		}

		(*_fireMonsterBullet->setVFireBullet())[i].tileCollisionRc = RectMakeCenter(_fireMonsterBullet->getVFireBullet()[i].x, _fireMonsterBullet->getVFireBullet()[i].y, _fireMonsterBullet->getVFireBullet()[i].image->getFrameWidth(), _fireMonsterBullet->getVFireBullet()[i].image->getFrameHeight());

		if (IntersectRect(&temp, &_fireMonsterBullet->getVFireBullet()[i].rc, &_player->getPlayerRc()))
		{
			(*_fireMonsterBullet->setVFireBullet())[i].isCollision = true;
			_vFireMonster[num]->setAttackWorldTime(TIMEMANAGER->getWorldTime());
			_vFireMonster[num]->setIsAttack(true); //불공격에 맞았다.
		}
		//0.8초뒤 공격꺼줌
		if (0.8f + _vFireMonster[num]->getAttackWorldTime() <= TIMEMANAGER->getWorldTime())
		{
			_vFireMonster[num]->setIsAttack(false);
		}
	}
}

//에너미들이 죽을함수
void enemyManager::enemyDead()
{
	//공몬스터
	for (int i = 0; i < _vBallMonster.size();)
	{
		if (_vBallMonster[i]->getCurrentHP() <= 0.0f)
		{
			EFFECTMANAGER->play("deadEffect", _vBallMonster[i]->getViewX(), _vBallMonster[i]->getViewY());

			//몬스터죽으면 몬스터위치 받고 푸시백
			POINTFLOAT monster;
			monster.x = _vBallMonster[i]->getX() - TileSIZE;
			monster.y = _vBallMonster[i]->getY() - TileSIZE;
			_vEnemyDeadPoint.push_back(monster);

			_vBallMonster.erase(_vBallMonster.begin() + i);
		}
		else i++;
	}

	//불몬스터
	for (int i = 0; i < _vFireMonster.size();)
	{
		if (_vFireMonster[i]->getCurrentHP() <= 0.0f)
		{
			EFFECTMANAGER->play("deadEffect", _vFireMonster[i]->getViewX(), _vFireMonster[i]->getViewY());

			//몬스터죽으면 몬스터위치 받고 푸시백
			POINTFLOAT monster;
			monster.x = _vFireMonster[i]->getX() - _vFireMonster[i]->getImage()->getFrameWidth();
			monster.y = _vFireMonster[i]->getY() - _vFireMonster[i]->getImage()->getFrameHeight() / 2;
			_vEnemyDeadPoint.push_back(monster);
		
			_vFireMonster.erase(_vFireMonster.begin() + i);
		}
		else i++;
	}

	//기사몬스터
	for (int i = 0; i < _vKnightMonster.size();)
	{
		if (_vKnightMonster[i]->getCurrentHP() <= 0.0f)
		{
			EFFECTMANAGER->play("deadEffect", _vKnightMonster[i]->getViewX(), _vKnightMonster[i]->getViewY());

			//몬스터죽으면 몬스터위치 받고 푸시백
			POINTFLOAT monster;
			monster.x = _vKnightMonster[i]->getX() - TileSIZE;
			monster.y = _vKnightMonster[i]->getY();
			_vEnemyDeadPoint.push_back(monster);
		
			_vKnightMonster.erase(_vKnightMonster.begin() + i);
		}
		else i++;
	}

}

//타일검출 충돌 함수
void enemyManager::tileCheckObjectCollision()
{
	//공몬스터
	for (int i = 0; i < _vBallMonster.size(); i++)
	{
		//충돌렉트에 실제렉트 대입
		_vBallMonster[i]->setTileCollisionRect(_vBallMonster[i]->getRect());

		//인덱스 정해주기
		_vBallMonster[i]->setIdX(_vBallMonster[i]->getX() / TileSIZE);
		_vBallMonster[i]->setIdY(_vBallMonster[i]->getY() / TileSIZE);

		//방향에따라 타일인덱스에 타일검출하기 위함
		switch (_vBallMonster[i]->getDirection())
		{
		case BALLMONSTER_DIRECTION_LEFT:
			_vBallMonster[i]->setTileIndex()[0].x = _vBallMonster[i]->getIdX() - 1;
			_vBallMonster[i]->setTileIndex()[0].y = _vBallMonster[i]->getIdY();
			_vBallMonster[i]->setTileIndex()[1].x = _vBallMonster[i]->getIdX() - 1;
			_vBallMonster[i]->setTileIndex()[1].y = _vBallMonster[i]->getIdY() + 1;
			_vBallMonster[i]->setTileIndex()[2].x = _vBallMonster[i]->getIdX() - 1;
			_vBallMonster[i]->setTileIndex()[2].y = _vBallMonster[i]->getIdY() - 1;
			break;
		case BALLMONSTER_DIRECTION_UP:
			_vBallMonster[i]->setTileIndex()[0].x = _vBallMonster[i]->getIdX();
			_vBallMonster[i]->setTileIndex()[0].y = _vBallMonster[i]->getIdY() - 1;
			_vBallMonster[i]->setTileIndex()[1].x = _vBallMonster[i]->getIdX() + 1;
			_vBallMonster[i]->setTileIndex()[1].y = _vBallMonster[i]->getIdY() - 1;
			_vBallMonster[i]->setTileIndex()[2].x = _vBallMonster[i]->getIdX() + 2;
			_vBallMonster[i]->setTileIndex()[2].y = _vBallMonster[i]->getIdY() - 1;
			break;
		case BALLMONSTER_DIRECTION_RIGHT:
			_vBallMonster[i]->setTileIndex()[0].x = _vBallMonster[i]->getIdX() + 1;
			_vBallMonster[i]->setTileIndex()[0].y = _vBallMonster[i]->getIdY();
			_vBallMonster[i]->setTileIndex()[1].x = _vBallMonster[i]->getIdX() + 1;
			_vBallMonster[i]->setTileIndex()[1].y = _vBallMonster[i]->getIdY() + 1;
			_vBallMonster[i]->setTileIndex()[2].x = _vBallMonster[i]->getIdX() + 1;
			_vBallMonster[i]->setTileIndex()[2].y = _vBallMonster[i]->getIdY() - 1;
			break;
		case BALLMONSTER_DIRECTION_DOWN:
			_vBallMonster[i]->setTileIndex()[0].x = _vBallMonster[i]->getIdX();
			_vBallMonster[i]->setTileIndex()[0].y = _vBallMonster[i]->getIdY() + 1;
			_vBallMonster[i]->setTileIndex()[1].x = _vBallMonster[i]->getIdX() + 1;
			_vBallMonster[i]->setTileIndex()[1].y = _vBallMonster[i]->getIdY() + 1;
			_vBallMonster[i]->setTileIndex()[2].x = _vBallMonster[i]->getIdX() + 2;
			_vBallMonster[i]->setTileIndex()[2].y = _vBallMonster[i]->getIdY() + 1;
			break;
		}

		RECT temp;
		//임시오브젝트 렉트 충돌용
		if (IntersectRect(&temp, &_objectRc, &_vBallMonster[i]->getRect()) && _dungeonMap->getDungeonFloor() == DUNGEON_FLOOR::SECOND_FLOOR)
		{
			switch (_vBallMonster[i]->getDirection())
			{
			case BALLMONSTER_DIRECTION_UP:
				_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().top - _objectRc.bottom);
				_vBallMonster[i]->setY(_vBallMonster[i]->getY() - _vBallMonster[i]->getTum());
				break;
			case BALLMONSTER_DIRECTION_DOWN:
				_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().bottom - _objectRc.top);
				_vBallMonster[i]->setY(_vBallMonster[i]->getY() - _vBallMonster[i]->getTum());
				break;
			}
			if (_vBallMonster[i]->getIsAttack() == true)
			{
				_vBallMonster[i]->setSpeed(0);
				_vBallMonster[i]->getMotion()->setFPS(5);
				_vBallMonster[i]->setIsAttack(false);
				_vBallMonster[i]->setAttackWorldTime(TIMEMANAGER->getWorldTime());
				_vBallMonster[i]->setWorldTime(TIMEMANAGER->getWorldTime());
			}
		}

		for (int j = 0; j < 3; i++)
		{
			if (_dungeonMap->getAttr(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y) == ATTR_UNMOVE
				&& IntersectRect(&temp, &_dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc, &_vBallMonster[i]->getTileCollisionRect()))
			{
				//랜덤으로 무빙을 받음.
				_rndMove[BALLMONSTER] = RND->getRandomInt(1, 3);

				if (_vBallMonster[i]->getState() != BALLMONSTER_STATE_IDLE && _vBallMonster[i]->getIsAttack() == false)
				{
					switch (_vBallMonster[i]->getDirection())
					{
					case BALLMONSTER_DIRECTION_LEFT:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().left - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.right);
						_vBallMonster[i]->setX(_vBallMonster[i]->getX() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_UP);
						}
						break;
					case BALLMONSTER_DIRECTION_RIGHT:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().right - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.left);
						_vBallMonster[i]->setX(_vBallMonster[i]->getX() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_LEFT);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_UP);
						}
						break;
					case BALLMONSTER_DIRECTION_UP:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().top - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.bottom);
						_vBallMonster[i]->setY(_vBallMonster[i]->getY() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_LEFT);
						}
						break;
					case BALLMONSTER_DIRECTION_DOWN:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().bottom - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.top);
						_vBallMonster[i]->setY(_vBallMonster[i]->getY() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_LEFT);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_UP);
						}
						break;
					}
				
				}
				else if (_vBallMonster[i]->getIsAttack() == true && _vBallMonster[i]->getState() != BALLMONSTER_STATE_IDLE)
				{
					_vBallMonster[i]->setSpeed(0);
					_vBallMonster[i]->getMotion()->setFPS(5);
					_vBallMonster[i]->setIsAttack(false);
					_vBallMonster[i]->setAttackWorldTime(TIMEMANAGER->getWorldTime());
					_vBallMonster[i]->setWorldTime(TIMEMANAGER->getWorldTime());

					switch (_vBallMonster[i]->getDirection())
					{
					case BALLMONSTER_DIRECTION_LEFT:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().left - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.right);
						_vBallMonster[i]->setX(_vBallMonster[i]->getX() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_UP);
						}
						break;
					case BALLMONSTER_DIRECTION_RIGHT:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().right - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.left);
						_vBallMonster[i]->setX(_vBallMonster[i]->getX() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_LEFT);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_UP);
						}
						break;
					case BALLMONSTER_DIRECTION_UP:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().top - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.bottom);
						_vBallMonster[i]->setY(_vBallMonster[i]->getY() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_LEFT);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_DOWN);
						}
						break;
					case BALLMONSTER_DIRECTION_DOWN:
						_vBallMonster[i]->setTum(_vBallMonster[i]->getRect().bottom - _dungeonMap->getTile(_vBallMonster[i]->getTileIndex(j).x, _vBallMonster[i]->getTileIndex(j).y)->rc.top);
						_vBallMonster[i]->setY(_vBallMonster[i]->getY() - _vBallMonster[i]->getTum());

						if (_rndMove[BALLMONSTER] == 1)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_LEFT);
						}
						else if (_rndMove[BALLMONSTER] == 2)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[BALLMONSTER] == 3)
						{
							_vBallMonster[i]->setDirection(BALLMONSTER_DIRECTION_UP);
						}
						break;
					}
				}
			}
			break;
		}
		_vBallMonster[i]->setTileCollisionRect(RectMakeCenter(_vBallMonster[i]->getX(), _vBallMonster[i]->getY(), _vBallMonster[i]->getImage()->getFrameWidth(), _vBallMonster[i]->getImage()->getFrameHeight()));
	}

	//불몬스터
	for (int i = 0; i < _vFireMonster.size(); i++)
	{
		_vFireMonster[i]->setTileCollisionRect(_vFireMonster[i]->getRect());

		//인덱스 정해주기
		_vFireMonster[i]->setIdX(_vFireMonster[i]->getX() / TileSIZE);
		_vFireMonster[i]->setIdY(_vFireMonster[i]->getY() / TileSIZE);

		//범위검사
		switch (_vFireMonster[i]->getDirection())
		{
		case FIREMONSTER_DIRECTION_LEFT:
			_vFireMonster[i]->setTileIndex()[0].x = _vFireMonster[i]->getIdX() - 1;
			_vFireMonster[i]->setTileIndex()[0].y = _vFireMonster[i]->getIdY();
			_vFireMonster[i]->setTileIndex()[1].x = _vFireMonster[i]->getIdX() - 1;
			_vFireMonster[i]->setTileIndex()[1].y = _vFireMonster[i]->getIdY() + 1;
			break;
		case FIREMONSTER_DIRECTION_UP:
			_vFireMonster[i]->setTileIndex()[0].x = _vFireMonster[i]->getIdX();
			_vFireMonster[i]->setTileIndex()[0].y = _vFireMonster[i]->getIdY() - 1;
			_vFireMonster[i]->setTileIndex()[1].x = _vFireMonster[i]->getIdX() + 1;
			_vFireMonster[i]->setTileIndex()[1].y = _vFireMonster[i]->getIdY() - 1;
			break;
		case FIREMONSTER_DIRECTION_RIGHT:
			_vFireMonster[i]->setTileIndex()[0].x = _vFireMonster[i]->getIdX() + 1;
			_vFireMonster[i]->setTileIndex()[0].y = _vFireMonster[i]->getIdY();
			_vFireMonster[i]->setTileIndex()[1].x = _vFireMonster[i]->getIdX() + 1;
			_vFireMonster[i]->setTileIndex()[1].y = _vFireMonster[i]->getIdY() + 1;
			break;
		case FIREMONSTER_DIRECTION_DOWN:
			_vFireMonster[i]->setTileIndex()[0].x = _vFireMonster[i]->getIdX();
			_vFireMonster[i]->setTileIndex()[0].y = _vFireMonster[i]->getIdY() + 1;
			_vFireMonster[i]->setTileIndex()[1].x = _vFireMonster[i]->getIdX() + 1;
			_vFireMonster[i]->setTileIndex()[1].y = _vFireMonster[i]->getIdY() + 1;
			break;
		}

		RECT temp;
		//임시오브젝트 렉트 충돌용 2층일때만
		if (IntersectRect(&temp, &_objectRc, &_vFireMonster[i]->getRect()) && _dungeonMap->getDungeonFloor() == DUNGEON_FLOOR::SECOND_FLOOR)
		{
			switch (_vFireMonster[i]->getDirection())
			{
			case FIREMONSTER_DIRECTION_UP:
				_vFireMonster[i]->setTum(_vFireMonster[i]->getRect().top - _objectRc.bottom);
				_vFireMonster[i]->setY(_vFireMonster[i]->getY() - _vFireMonster[i]->getTum());
				break;
			case FIREMONSTER_DIRECTION_DOWN:
				_vFireMonster[i]->setTum(_vFireMonster[i]->getRect().bottom - _objectRc.top);
				_vFireMonster[i]->setY(_vFireMonster[i]->getY() - _vFireMonster[i]->getTum());
				break;
			}
		}
		for (int j = 0; j < 2; i++)
		{
			if (_dungeonMap->getAttr(_vFireMonster[i]->getTileIndex(j).x, _vFireMonster[i]->getTileIndex(j).y) == ATTR_UNMOVE
				&& IntersectRect(&temp, &_dungeonMap->getTile(_vFireMonster[i]->getTileIndex(j).x, _vFireMonster[i]->getTileIndex(j).y)->rc, &_vFireMonster[i]->getTileCollisionRect()))
			{
				//랜덤으로 무빙을 받음.
				_rndMove[FIREMONSTER] = RND->getRandomInt(1, 3);

				switch (_vFireMonster[i]->getDirection())
				{
				case FIREMONSTER_DIRECTION_LEFT:
					_vFireMonster[i]->setTum(_vFireMonster[i]->getRect().left - _dungeonMap->getTile(_vFireMonster[i]->getTileIndex(j).x, _vFireMonster[i]->getTileIndex(j).y)->rc.right);
					_vFireMonster[i]->setX(_vFireMonster[i]->getX() - _vFireMonster[i]->getTum());

					if (_rndMove[FIREMONSTER] == 1)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_DOWN);
					}
					else if (_rndMove[FIREMONSTER] == 2)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_RIGHT);
					}
					else if (_rndMove[FIREMONSTER] == 3)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_UP);
					}
					break;
				case FIREMONSTER_DIRECTION_RIGHT:
					_vFireMonster[i]->setTum(_vFireMonster[i]->getRect().right - _dungeonMap->getTile(_vFireMonster[i]->getTileIndex(j).x, _vFireMonster[i]->getTileIndex(j).y)->rc.left);
					_vFireMonster[i]->setX(_vFireMonster[i]->getX() - _vFireMonster[i]->getTum());

					if (_rndMove[FIREMONSTER] == 1)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_DOWN);
					}
					else if (_rndMove[FIREMONSTER] == 2)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_LEFT);
					}
					else if (_rndMove[FIREMONSTER] == 3)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_UP);
					}
					break;
				case FIREMONSTER_DIRECTION_UP:
					_vFireMonster[i]->setTum(_vFireMonster[i]->getRect().top - _dungeonMap->getTile(_vFireMonster[i]->getTileIndex(j).x, _vFireMonster[i]->getTileIndex(j).y)->rc.bottom);
					_vFireMonster[i]->setY(_vFireMonster[i]->getY() - _vFireMonster[i]->getTum());

					if (_rndMove[FIREMONSTER] == 1)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_DOWN);
					}
					else if (_rndMove[FIREMONSTER] == 2)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_LEFT);
					}
					else if (_rndMove[FIREMONSTER] == 3)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_RIGHT);
					}
					break;
				case FIREMONSTER_DIRECTION_DOWN:
					_vFireMonster[i]->setTum(_vFireMonster[i]->getRect().bottom - _dungeonMap->getTile(_vFireMonster[i]->getTileIndex(j).x, _vFireMonster[i]->getTileIndex(j).y)->rc.top);
					_vFireMonster[i]->setY(_vFireMonster[i]->getY() - _vFireMonster[i]->getTum());

					if (_rndMove[FIREMONSTER] == 1)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_RIGHT);
					}
					else if (_rndMove[FIREMONSTER] == 2)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_LEFT);
					}
					else if (_rndMove[FIREMONSTER] == 3)
					{
						_vFireMonster[i]->setDirection(FIREMONSTER_DIRECTION_UP);
					}
					break;
				}

			}
			break;
		}
		_vFireMonster[i]->setTileCollisionRect(RectMakeCenter(_vFireMonster[i]->getX(), _vFireMonster[i]->getY(), _vFireMonster[i]->getImage()->getFrameWidth(), _vFireMonster[i]->getImage()->getFrameHeight()));

	}

	//기사몬스터
	for (int i = 0; i < _vKnightMonster.size(); i++)
	{
		_vKnightMonster[i]->setTileCollisionRect(_vKnightMonster[i]->getRect());

		//인덱스 정해주기
		_vKnightMonster[i]->setIdX(_vKnightMonster[i]->getX() / TileSIZE);
		_vKnightMonster[i]->setIdY(_vKnightMonster[i]->getY() / TileSIZE);

		//범위검사
		switch (_vKnightMonster[i]->getDirection())
		{
		case KNIGHTMONSTER_DIRECTION_LEFT:
			_vKnightMonster[i]->setTileIndex()[0].x = _vKnightMonster[i]->getIdX() - 1;
			_vKnightMonster[i]->setTileIndex()[0].y = _vKnightMonster[i]->getIdY();
			_vKnightMonster[i]->setTileIndex()[1].x = _vKnightMonster[i]->getIdX() - 1;
			_vKnightMonster[i]->setTileIndex()[1].y = _vKnightMonster[i]->getIdY() + 1;
			break;
		case KNIGHTMONSTER_DIRECTION_UP:
			_vKnightMonster[i]->setTileIndex()[0].x = _vKnightMonster[i]->getIdX();
			_vKnightMonster[i]->setTileIndex()[0].y = _vKnightMonster[i]->getIdY() - 1;
			_vKnightMonster[i]->setTileIndex()[1].x = _vKnightMonster[i]->getIdX() + 1;
			_vKnightMonster[i]->setTileIndex()[1].y = _vKnightMonster[i]->getIdY() - 1;
			break;
		case KNIGHTMONSTER_DIRECTION_RIGHT:
			_vKnightMonster[i]->setTileIndex()[0].x = _vKnightMonster[i]->getIdX() + 1;
			_vKnightMonster[i]->setTileIndex()[0].y = _vKnightMonster[i]->getIdY();
			_vKnightMonster[i]->setTileIndex()[1].x = _vKnightMonster[i]->getIdX() + 1;
			_vKnightMonster[i]->setTileIndex()[1].y = _vKnightMonster[i]->getIdY() + 1;
			break;
		case KNIGHTMONSTER_DIRECTION_DOWN:
			_vKnightMonster[i]->setTileIndex()[0].x = _vKnightMonster[i]->getIdX();
			_vKnightMonster[i]->setTileIndex()[0].y = _vKnightMonster[i]->getIdY() + 1;
			_vKnightMonster[i]->setTileIndex()[1].x = _vKnightMonster[i]->getIdX() + 1;
			_vKnightMonster[i]->setTileIndex()[1].y = _vKnightMonster[i]->getIdY() + 1;
			break;
		}
		RECT temp;
		for (int j = 0; j < 2; j++)
		{
			if (_dungeonMap->getAttr(_vKnightMonster[i]->getTileIndex(j).x, _vKnightMonster[i]->getTileIndex(j).y) == ATTR_UNMOVE
				&& IntersectRect(&temp, &_dungeonMap->getTile(_vKnightMonster[i]->getTileIndex(j).x, _vKnightMonster[i]->getTileIndex(j).y)->rc, &_vKnightMonster[i]->getTileCollisionRect()))
			{
				//랜덤으로 무빙함.
				_rndMove[KNIGHTMONSTER] = RND->getRandomInt(1, 3);

				//공격중이 아니고 가만히있지 않을때만
				if (_vKnightMonster[i]->getState() != KNIGHTMONSTER_STATE_ATTACK && _vKnightMonster[i]->getState() != KNIGHTMONSTER_STATE_IDLE)
				{
					switch (_vKnightMonster[i]->getDirection())
					{
					case KNIGHTMONSTER_DIRECTION_LEFT:
						_vKnightMonster[i]->setTum(_vKnightMonster[i]->getRect().left - _dungeonMap->getTile(_vKnightMonster[i]->getTileIndex(j).x, _vKnightMonster[i]->getTileIndex(j).y)->rc.right);
						_vKnightMonster[i]->setX(_vKnightMonster[i]->getX() - _vKnightMonster[i]->getTum());

						if (_rndMove[KNIGHTMONSTER] == 1)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[KNIGHTMONSTER] == 2)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[KNIGHTMONSTER] == 3)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_UP);
						}
						break;
					case KNIGHTMONSTER_DIRECTION_RIGHT:
						_vKnightMonster[i]->setTum(_vKnightMonster[i]->getRect().right - _dungeonMap->getTile(_vKnightMonster[i]->getTileIndex(j).x, _vKnightMonster[i]->getTileIndex(j).y)->rc.left);
						_vKnightMonster[i]->setX(_vKnightMonster[i]->getX() - _vKnightMonster[i]->getTum());

						if (_rndMove[KNIGHTMONSTER] == 1)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_LEFT);
						}
						else if (_rndMove[KNIGHTMONSTER] == 2)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[KNIGHTMONSTER] == 3)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_UP);
						}
						break;
					case KNIGHTMONSTER_DIRECTION_UP:
						_vKnightMonster[i]->setTum(_vKnightMonster[i]->getRect().top - _dungeonMap->getTile(_vKnightMonster[i]->getTileIndex(j).x, _vKnightMonster[i]->getTileIndex(j).y)->rc.top);
						_vKnightMonster[i]->setY(_vKnightMonster[i]->getY() - _vKnightMonster[i]->getTum());

						if (_rndMove[KNIGHTMONSTER] == 1)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[KNIGHTMONSTER] == 2)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_DOWN);
						}
						else if (_rndMove[KNIGHTMONSTER] == 3)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_LEFT);
						}
						break;
					case KNIGHTMONSTER_DIRECTION_DOWN:
						_vKnightMonster[i]->setTum(_vKnightMonster[i]->getRect().bottom - _dungeonMap->getTile(_vKnightMonster[i]->getTileIndex(j).x, _vKnightMonster[i]->getTileIndex(j).y)->rc.bottom);
						_vKnightMonster[i]->setY(_vKnightMonster[i]->getY() - _vKnightMonster[i]->getTum());

						if (_rndMove[KNIGHTMONSTER] == 1)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_RIGHT);
						}
						else if (_rndMove[KNIGHTMONSTER] == 2)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_LEFT);
						}
						else if (_rndMove[KNIGHTMONSTER] == 3)
						{
							_vKnightMonster[i]->setDirection(KNIGHTMONSTER_DIRECTION_UP);
						}
						break;
					}
				}
			}
			break;
		}
		_vKnightMonster[i]->setTileCollisionRect(RectMakeCenter(_vKnightMonster[i]->getX(), _vKnightMonster[i]->getY() + 50, _vKnightMonster[i]->getImage()->getFrameWidth() - 240, _vKnightMonster[i]->getImage()->getFrameHeight() - 180)); //타일깎음

	}
}

//에너미들이 죽은다음 리스폰할 함수
void enemyManager::enemyRespon()
{
}
