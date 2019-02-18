#include "stdafx.h"
#include "bossScene.h"


bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	SOUNDMANAGER->addSound("bossSceneBGM", "sound/bossFight.mp3", true, true);

	_enemyManager = new enemyManager;
	_player = new player;
	_camera = new camera;
	_dungeonBossMap = new dungeonMap;
	_itemManager = new ItemManager;
	_bossBullet = new bossBullet;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	_player->setMapManagerAddressLink(_dungeonBossMap);
	_enemyManager->setDungeonMapAddressLink(_dungeonBossMap);

	_dungeonBossMap->setDungeonFloor(DUNGEON_FLOOR::BOSS_FLOOR);
	_dungeonBossMap->init(_dungeonBossMap->getDungeonFloor());
	_player->init();
	_enemyManager->init();
	_itemManager->init();
	_bossBullet->init("bossBullet", GAMESIZEY, 1);
	_enemyManager->setEnemy();

	//플레이어 초기위치
	_player->setPlayerPosX(1280 / 2 - 50);
	_player->setPlayerPosY(1000);

	_camera->init(GAMESIZEX, GAMESIZEY, 1280, 2560);

	_worldTime = TIMEMANAGER->getWorldTime();
	_moveWorldTime = TIMEMANAGER->getWorldTime();
	_isBossAppear = false;

	for (int i = 0; i < 4; i++)
	{
		_moveGoal[i].x = 400 + i * 150;
		_moveGoal[i].y = 600 + i * 80;
	}
	_goalX = GAMESIZEX / 2 + 70;
	_goalY = 650;
	_moveSpeed = 20.f;
	_bulletPattern = BULLET_PATTERN::BLUE_BULLET; //처음엔 골드총알로
	_attackPattern = ATTACK_PATTERN::ATTACK_TWO;
	_bulletSpeed = 7;

	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
	SAFE_DELETE(_dungeonBossMap);
	SAFE_DELETE(_camera);
	SAFE_DELETE(_bossBullet);
	SAFE_DELETE(_itemManager);
}

void bossScene::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_player->update(false, 1);
	_enemyManager->update();
	_itemManager->update();

	//보스 등장
	bossAppear();
	//보스 무브패턴
	movePattern();
	//보스 공격패턴
	attackPattern();

	_bossBullet->update();
}

void bossScene::render()
{
	if (_isBossAppear == true || _isOnce[BOSS_APPEAR] == true)
	{
		_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
	}
	_dungeonBossMap->render(_camera->getCameraX(), _camera->getCameraY());
	_itemManager->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(), _camera->getCameraY());
	_bossBullet->render(_camera->getCameraX(), _camera->getCameraY());

	//char str[128];

	//sprintf_s(str, "_rndMove : %d", _rndMove);
	//TextOut(getMemDC(), 100, 260, str, strlen(str));

	//sprintf_s(str, "moveWorldTime : %f", _moveWorldTime);
	//TextOut(getMemDC(), 100, 280, str, strlen(str));

	//for (int i = 0; i < 4; i++)
	//{
	//	sprintf_s(str, "_moveGoalX : %f", _moveGoal[i].x);
	//	TextOut(getMemDC(), 600, i * 20, str, strlen(str));

	//	sprintf_s(str, "_moveGoalY : %f", _moveGoal[i].y);
	//	TextOut(getMemDC(), 800, i * 20, str, strlen(str));
	//}

	//sprintf_s(str, "_distance : %f", _enemyManager->getVBoss()[0]->getTargetDistance());
	//TextOut(getMemDC(), 400, 100, str, strlen(str));

	//sprintf_s(str, "bossX : %f", _enemyManager->getVBoss()[0]->getX());
	//TextOut(getMemDC(), 100, 200, str, strlen(str));

	//sprintf_s(str, "bossY : %f", _enemyManager->getVBoss()[0]->getY());
	//TextOut(getMemDC(), 100, 240, str, strlen(str));


}

void bossScene::bossAppear()
{
	if (_player->getPlayerY() <= 900 && _isOnce[BOSS_APPEAR] == false)
	{
		_isBossAppear = true;
		SOUNDMANAGER->play("bossSceneBGM");
		_isOnce[BOSS_APPEAR] = true;
	}

	if (_isBossAppear == true && _enemyManager->getVBoss()[0]->getState() == BOSS_STATE_IDLE) //보스등장
	{
		_appearGoal.x = GAMESIZEX / 2 + 70;
		_appearGoal.y = 650;

		_elapsedTime = TIMEMANAGER->getElapsedTime();

		//골까지의 각도를 구해주고
		_goalAngle = getAngle(_enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY(), _appearGoal.x, _appearGoal.y);
		//골까지의 거리 구해줌.
		_goalDistance = getDistance(_enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY(), _appearGoal.x, _appearGoal.y);
		if (_isOnce[LINEAR_APPEAR] == false)
		{
			//거속시 선형보간
			_appearSpeed = _goalDistance * (_elapsedTime / 6.0f);
			_worldTime = TIMEMANAGER->getWorldTime();
		}
		_isOnce[LINEAR_APPEAR] = true;

		//8초전에만 움직임.
		if (8.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_enemyManager->getVBoss()[0]->setX(_enemyManager->getVBoss()[0]->getX() + cosf(_goalAngle) * _appearSpeed);
			_enemyManager->getVBoss()[0]->setY(_enemyManager->getVBoss()[0]->getY() + -sinf(_goalAngle) * _appearSpeed);
		}

		if (_goalDistance <= 10 && _isOnce[CAMERA_LINEAR] == false)
		{
			_camera->linearKeepMove(_appearGoal.x, _appearGoal.y + 50, 2, 100000);
			_isOnce[CAMERA_LINEAR] = true; //카메라도 한번만 받기위함.
			_isBossAppear = false; //도착점에도달했으면 보스 등장하는거 꺼줌.
			_enemyManager->getVBoss()[0]->setState(BOSS_STATE_MOVE);
		}
	}
}

void bossScene::movePattern()
{
	if (_isBossAppear == false && _enemyManager->getVBoss()[0]->getState() == BOSS_STATE_MOVE)
	{
		if (_isOnce[WORLDTIME] == false)
		{
			_moveWorldTime = TIMEMANAGER->getWorldTime();
			_attackWorldTime[ATTACK_NONE] = TIMEMANAGER->getWorldTime();
			_isOnce[WORLDTIME] = true;
		}

		switch (_enemyManager->getVBoss()[0]->getState())
		{
		case BOSS_STATE_MOVE:

			//4초후에 움직여라
			if (4.0f + _moveWorldTime <= TIMEMANAGER->getWorldTime())
			{
				if (2.0f + _rndMoveWorldTime <= TIMEMANAGER->getWorldTime())
				{
					_rndMove = RND->getRandomInt(0, 3);

					_rndMoveWorldTime = TIMEMANAGER->getWorldTime();
				}

				if (_enemyManager->getVBoss()[0]->getTargetDistance() > 2)
				{
					_enemyManager->getVBoss()[0]->setX(_enemyManager->getVBoss()[0]->getX() + cosf(_enemyManager->getVBoss()[0]->getMoveAngle() * _moveSpeed));
					_enemyManager->getVBoss()[0]->setY(_enemyManager->getVBoss()[0]->getY() + -sinf(_enemyManager->getVBoss()[0]->getMoveAngle() * _moveSpeed));
				}
				else
				{
					_enemyManager->getVBoss()[0]->setX(_goalX);
					_enemyManager->getVBoss()[0]->setY(_goalY);
				}

				_goalX = _moveGoal[_rndMove].x;
				_goalY = _moveGoal[_rndMove].y;

				//각도와 거리는 갱신
				_enemyManager->getVBoss()[0]->setMoveAngle(getAngle(_moveGoal[_rndMove].x, _moveGoal[_rndMove].y, _enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY()));
				_enemyManager->getVBoss()[0]->setTargetDistance(getDistance(_moveGoal[_rndMove].x, _moveGoal[_rndMove].y, _enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY()));

			}
			break;

		}
	}
}

void bossScene::attackPattern()
{
	if (_isBossAppear == false && _enemyManager->getVBoss()[0]->getState() == BOSS_STATE_MOVE && 4.0f + _attackWorldTime[ATTACK_NONE] <= TIMEMANAGER->getWorldTime())
	{
		for (int i = 0; i < _bossBullet->getVBossBullet().size(); i++)
		{
			//총알 나갈종류 정하기
			switch (_bulletPattern)
			{
			case BULLET_PATTERN::GOLD_BULLET:
				(*_bossBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("goldBullet", "gold");
				_bossBullet->getVBossBullet()[i].ani->start();
				break;
			case BULLET_PATTERN::BLUE_BULLET:
				(*_bossBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("blueBullet", "blue");
				_bossBullet->getVBossBullet()[i].ani->start();
				break;
			case BULLET_PATTERN::RED_BULLET:
				(*_bossBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("redBullet", "red");
				_bossBullet->getVBossBullet()[i].ani->start();
				break;
			}
		}

		POINTFLOAT boss;
		boss.x = _enemyManager->getVBoss()[0]->getX();
		boss.y = _enemyManager->getVBoss()[0]->getY();

		_bossBullet->setBulletMax(1);

		switch (_attackPattern)
		{
		case ATTACK_ONE:

			//시간마다 공격
			if (3.0f + _attackWorldTime[ATTACK_ONE] <= TIMEMANAGER->getWorldTime())
			{
				_rndAttack = RND->getRandomInt(1, 2);
				_rndAttackType = RND->getRandomInt(1, 2);
				if (_rndAttackType == 1)
				{
					_bossBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed);
				}
				else if (_rndAttackType == 2)
				{
					_bossBullet->setBulletMax(3);
					_bossBullet->bossFire(boss.x - 100, boss.y, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x - 200, boss.y, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x + 100, boss.y, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x + 200, boss.y, (PI / 180) * 270, _bulletSpeed);

				}
			
				//랜덤어택
				if (_rndAttack == 1)
				{
					_bulletPattern = BULLET_PATTERN::BLUE_BULLET;
					_attackPattern = ATTACK_TWO;
				}
				else if (_rndAttack == 2)
				{
					_bulletPattern = BULLET_PATTERN::RED_BULLET;
					_attackPattern = ATTACK_THREE;
				}

				_attackWorldTime[ATTACK_ONE] = TIMEMANAGER->getWorldTime();
			}
			break;
		case ATTACK_TWO:

			//시간마다 공격
			if (3.0f + _attackWorldTime[ATTACK_TWO] <= TIMEMANAGER->getWorldTime())
			{
				_rndAttack = RND->getRandomInt(1, 2);
				_rndAttackType = RND->getRandomInt(1, 2);

				_bossBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed);
				_bossBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed);
		
				//랜덤어택
				if (_rndAttack == 1)
				{
					_bulletPattern = BULLET_PATTERN::GOLD_BULLET;
					_attackPattern = ATTACK_ONE;
				}
				else if (_rndAttack == 2)
				{
					_bulletPattern = BULLET_PATTERN::RED_BULLET;
					_attackPattern = ATTACK_THREE;
				}

				_attackWorldTime[ATTACK_TWO] = TIMEMANAGER->getWorldTime();

			}

			break;
		case ATTACK_THREE:

			if (3.0f + _attackWorldTime[ATTACK_THREE] <= TIMEMANAGER->getWorldTime())
			{
				_rndAttack = RND->getRandomInt(1, 2);
				_rndAttackType = RND->getRandomInt(1, 2);

				if (_rndAttackType == 1)
				{
					_bossBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed);
				}
				else if (_rndAttackType == 2)
				{
					_bossBullet->setBulletMax(3);
					_bossBullet->bossFire(boss.x - 100, boss.y, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x - 200, boss.y - 100, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x + 100, boss.y, (PI / 180) * 270, _bulletSpeed);
					_bossBullet->bossFire(boss.x + 200, boss.y - 100, (PI / 180) * 270, _bulletSpeed);
				}

				//랜덤어택
				if (_rndAttack == 1)
				{
					_bulletPattern = BULLET_PATTERN::GOLD_BULLET;
					_attackPattern = ATTACK_ONE;
				}
				else if (_rndAttack == 2)
				{
					_bulletPattern = BULLET_PATTERN::BLUE_BULLET;
					_attackPattern = ATTACK_TWO;
				}

				_attackWorldTime[ATTACK_THREE] = TIMEMANAGER->getWorldTime();
			}
			break;
		}
		if (_attackPattern == ATTACK_TWO && _bulletPattern == BULLET_PATTERN::BLUE_BULLET)
		{
			for (int i = 0; i < _bossBullet->getVBossBullet().size(); i++)
			{
				//두번째공격일때만 각도꺾음.
				if (_bossBullet->getVBossBullet()[i].y >= _player->getPlayerY())
				{
					(*_bossBullet->setVBossBullet())[0].angle = PI2;
					(*_bossBullet->setVBossBullet())[1].angle = PI;
				}
			}
		}
		else if (_attackPattern == ATTACK_THREE && _bulletPattern == BULLET_PATTERN::RED_BULLET)
		{
			for (int i = 0; i < _bossBullet->getVBossBullet().size(); i++)
			{
				if (_bossBullet->getVBossBullet()[i].y >= _player->getPlayerY())
				{
					if (1.0f + _bulletWorldTime >= TIMEMANAGER->getWorldTime())
					{
						(*_bossBullet->setVBossBullet())[i].speed = 0;
						(*_bossBullet->setVBossBullet())[i].ani->setFPS(30);
					}
					else if (1.0f + _bulletWorldTime < TIMEMANAGER->getWorldTime() && 2.f + _bulletWorldTime > TIMEMANAGER->getWorldTime())
					{
						_bulletSpeed = 7;
						(*_bossBullet->setVBossBullet())[i].speed += 0.2f;
						(*_bossBullet->setVBossBullet())[0].angle = PI2;
						(*_bossBullet->setVBossBullet())[1].angle = PI;
					}
					else if (2.f + _bulletWorldTime <= TIMEMANAGER->getWorldTime())
					{
						(*_bossBullet->setVBossBullet())[i].speed = 7;
						(*_bossBullet->setVBossBullet())[i].ani->setFPS(7);
						_bulletWorldTime = TIMEMANAGER->getWorldTime();
					}
				}
			}
		}
	}
}


void bossScene::setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅을 한다
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);

}
