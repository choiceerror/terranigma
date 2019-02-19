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
	_goldBullet = new bossBullet;
	_blueBullet = new bossBullet;
	_redBullet = new bossBullet;
	_rgbBullet = new bossBullet;
	_shockAttack = new tagShockAttack;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	_player->setMapManagerAddressLink(_dungeonBossMap);
	_enemyManager->setDungeonMapAddressLink(_dungeonBossMap);

	_dungeonBossMap->setDungeonFloor(DUNGEON_FLOOR::BOSS_FLOOR);
	_dungeonBossMap->init(_dungeonBossMap->getDungeonFloor());
	_player->init();
	//_enemyManager->init();
	_itemManager->init();
	_goldBullet->init("bossBullet", GAMESIZEY, 1);
	_blueBullet->init("bossBullet", GAMESIZEY, 1);
	_redBullet->init("bossBullet", GAMESIZEY, 1);
	_rgbBullet->init("bossBullet", GAMESIZEY, 1);
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
	_bulletPattern = BULLET_PATTERN::GOLD_BULLET; //처음엔 골드총알로
	_attackPattern = ATTACK_PATTERN::ATTACK_ONE;

	for (int i = 0; i < 3; i++)
	{
		_bulletSpeed[i] = 7;
	}

	//전기이펙트 
	_shockAttack->x = _enemyManager->getVBoss()[0]->getX();
	_shockAttack->y = _enemyManager->getVBoss()[0]->getY();
	_shockAttack->image = IMAGEMANAGER->findImage("shockAttack");
	_shockAttack->rc = RectMakeCenter(_shockAttack->x, _shockAttack->y, _shockAttack->image->getFrameWidth(), _shockAttack->image->getFrameHeight());
	int rightShock[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("shock", "rightShock", "shockAttack", rightShock, 8, 5, true);

	int leftShock[] = { 15, 14, 13, 12, 11, 10, 9, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("shock", "leftShock", "shockAttack", leftShock, 8, 5, true);

	_shockAttack->ani = KEYANIMANAGER->findAnimation("shock", "rightShock");

	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
	SAFE_DELETE(_dungeonBossMap);
	SAFE_DELETE(_camera);
	SAFE_DELETE(_goldBullet);
	SAFE_DELETE(_blueBullet);
	SAFE_DELETE(_redBullet);
	SAFE_DELETE(_rgbBullet);
	SAFE_DELETE(_itemManager);
	SAFE_DELETE(_shockAttack);
}

void bossScene::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_player->update(false, 1);
	_itemManager->update();
	_enemyManager->update();
	_dungeonBossMap->update();
	if (_enemyManager->getVBoss()[0]->getCurrentHP() > 0)
	{
		//보스 등장
		bossAppear();
		//보스 무브패턴
		movePattern();
		//보스 공격패턴
		attackPattern();

		if (_bulletPattern == BULLET_PATTERN::GOLD_BULLET || _bulletPattern == BULLET_PATTERN::BLUE_BULLET || _bulletPattern == BULLET_PATTERN::RED_BULLET)
		{
			_goldBullet->update();
			_blueBullet->update();
			_redBullet->update();
		}

		if (_bulletPattern == BULLET_PATTERN::RGB_BULLET)
		{
			_rgbBullet->update();
		}
	}
}

void bossScene::render()
{
	if (_enemyManager->getVBoss()[0]->getCurrentHP() > 0)
	{
		if (_isBossAppear == true || _isOnce[BOSS_APPEAR] == true)
		{
			_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
		}
	}

	_dungeonBossMap->render(_camera->getCameraX(), _camera->getCameraY());
	_itemManager->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(), _camera->getCameraY(), true);

	if (_enemyManager->getVBoss()[0]->getCurrentHP() > 0)
	{
		if (_bulletPattern == BULLET_PATTERN::GOLD_BULLET || _bulletPattern == BULLET_PATTERN::BLUE_BULLET || _bulletPattern == BULLET_PATTERN::RED_BULLET)
		{
			_goldBullet->render(_camera->getCameraX(), _camera->getCameraY());
			_blueBullet->render(_camera->getCameraX(), _camera->getCameraY());
			_redBullet->render(_camera->getCameraX(), _camera->getCameraY());
		}

		if (_bulletPattern == BULLET_PATTERN::RGB_BULLET)
		{
			_rgbBullet->render(_camera->getCameraX(), _camera->getCameraY());
		}

		if (_attackPattern == ATTACK_SHOCK)
		{
			_shockAttack->image->expandAniRenderCenter(getMemDC(), _shockAttack->x, _shockAttack->y, _shockAttack->ani, 3.f, 3.f);
		}

		if (_bulletPattern == BULLET_PATTERN::RGB_BULLET)
		{
			_shockAttack->image->expandAniRenderCenter(getMemDC(), _shockAttack->x, _shockAttack->y, _shockAttack->ani, 3.f, 3.f);
		}
	}
	
	//Rectangle(getMemDC(), _shockAttack->rc2.left - _camera->getCameraX(), _shockAttack->rc2.top - _camera->getCameraY(), _shockAttack->rc2.right - _camera->getCameraX(), _shockAttack->rc2.bottom - _camera->getCameraY());
	//Rectangle(getMemDC(), _shockAttack->rc.left - _camera->getCameraX(), _shockAttack->rc.top - _camera->getCameraY(), _shockAttack->rc.right - _camera->getCameraX(), _shockAttack->rc.bottom - _camera->getCameraY());
	char str[128];

	//sprintf_s(str, "_rndMove : %d", _rndMove);
	//TextOut(getMemDC(), 100, 260, str, strlen(str));

	//sprintf_s(str, "hp : %d", _enemyManager->getVBoss()[0]->getCurrentHP());
	//TextOut(getMemDC(), 100, 280, str, strlen(str));

	//for (int i = 0; i < _bossBullet->getVBossBullet().size(); i++)
	//{
	//	sprintf_s(str, "bulletSize : %d", _bossBullet->getVBossBullet().size());
	//	TextOut(getMemDC(), 400, 100, str, strlen(str));

	//}
	//sprintf_s(str, "attackWorldTime[ATTACK_ONE] : %f", _attackWorldTime[ATTACK_ONE]);
	//TextOut(getMemDC(), 400, 100, str, strlen(str));

	//sprintf_s(str, "attackWorldTime[ATTACK_TWO] : %f", _attackWorldTime[ATTACK_TWO]);
	//TextOut(getMemDC(), 400, 120, str, strlen(str));

	//sprintf_s(str, "attackWorldTime[ATTACK_THREE] : %f", _attackWorldTime[ATTACK_THREE]);
	//TextOut(getMemDC(), 400, 140, str, strlen(str));

	//for (int i = 0; i < 4; i++)
	//{
	//	sprintf_s(str, "_rndAttack: %d", _rndAttack[i]);
	//	TextOut(getMemDC(), 200, 100 + i * 20, str, strlen(str));
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
	//보스가 다 등장하고 움직인 상태라면
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
		if (_bulletPattern != BULLET_PATTERN::RGB_BULLET)
		{
			//총알 나갈종류 정하기
			for (int i = 0; i < _goldBullet->getVBossBullet().size(); i++)
			{
				if (_attackPattern == ATTACK_ONE)
				{
					_bulletPattern = BULLET_PATTERN::GOLD_BULLET;
					(*_goldBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("goldBullet", "gold");
				}
			}
			for (int i = 0; i < _blueBullet->getVBossBullet().size(); i++)
			{
				if (_attackPattern == ATTACK_TWO)
				{
					_bulletPattern = BULLET_PATTERN::BLUE_BULLET;
					(*_blueBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("blueBullet", "blue");
				}
			}
			for (int i = 0; i < _redBullet->getVBossBullet().size(); i++)
			{
				if (_attackPattern == ATTACK_THREE)
				{
					_bulletPattern = BULLET_PATTERN::RED_BULLET;
					(*_redBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("redBullet", "red");
				}
			}
		}
		else
		{
			for (int i = 0; i < _rgbBullet->getVBossBullet().size(); i++)
			{
				if (_attackPattern == ATTACK_ONE)
				{
					(*_rgbBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("goldBullet", "gold");
				}

				else if (_attackPattern == ATTACK_TWO)
				{
					(*_rgbBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("blueBullet", "blue");
				}

				else if (_attackPattern == ATTACK_THREE)
				{
					(*_rgbBullet->setVBossBullet())[i].ani = KEYANIMANAGER->findAnimation("redBullet", "red");
				}
			}
		}

		POINTFLOAT boss;
		boss.x = _enemyManager->getVBoss()[0]->getX();
		boss.y = _enemyManager->getVBoss()[0]->getY();

		//체력 1000이하일때만 패턴다르게
		if (_enemyManager->getVBoss()[0]->getCurrentHP() <= 1000)
		{
			_bulletPattern = BULLET_PATTERN::RGB_BULLET;

			for (int i = 0; i < 4; i++)
			{
				_rndAttack[i] = RND->getRandomInt(1, 3);
				if (i <= 2) _rndAttackType[i] = RND->getRandomInt(1, 2);
			}

			if (_rndAttack[ATTACK_ONE] == 1) _attackPattern = ATTACK_TWO;
			else if (_rndAttack[ATTACK_ONE] == 2) _attackPattern = ATTACK_THREE;

			if (_rndAttack[ATTACK_TWO] == 1) _attackPattern = ATTACK_ONE;
			else if (_rndAttack[ATTACK_TWO] == 2) _attackPattern = ATTACK_THREE;

			if (_rndAttack[ATTACK_THREE] == 1) _attackPattern = ATTACK_ONE;
			else if (_rndAttack[ATTACK_THREE] == 2) _attackPattern = ATTACK_TWO;

			switch (_attackPattern)
			{
			case ATTACK_ONE:

				//시간마다 공격
				if (3.0f + _attackWorldTime[ATTACK_ONE] <= TIMEMANAGER->getWorldTime())
				{
					if (_rndAttackType[0] == 1)
					{
						_rgbBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 1);
						_rgbBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 1);
					}
					else if (_rndAttackType[0] == 2)
					{
						_rgbBullet->bossFire(boss.x - 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);
						_rgbBullet->bossFire(boss.x - 200, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);
						_rgbBullet->bossFire(boss.x + 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);
						_rgbBullet->bossFire(boss.x + 200, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);

					}

					_attackWorldTime[ATTACK_ONE] = TIMEMANAGER->getWorldTime();
				}
				break;
			case ATTACK_TWO:

				//시간마다 공격
				if (3.0f + _attackWorldTime[ATTACK_TWO] <= TIMEMANAGER->getWorldTime())
				{
					_rgbBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_TWO], 1);
					_rgbBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_TWO], 1);

					_attackWorldTime[ATTACK_TWO] = TIMEMANAGER->getWorldTime();
				}

				break;
			case ATTACK_THREE:

				//시간마다 공격
				if (3.0f + _attackWorldTime[ATTACK_THREE] <= TIMEMANAGER->getWorldTime())
				{
					if (_rndAttackType[1] == 1)
					{
						_rgbBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 1);
						_rgbBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 1);
					}
					else if (_rndAttackType[1] == 2)
					{
						_rgbBullet->bossFire(boss.x - 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
						_rgbBullet->bossFire(boss.x - 200, boss.y - 100, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
						_rgbBullet->bossFire(boss.x + 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
						_rgbBullet->bossFire(boss.x + 200, boss.y - 100, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
					}

					_attackWorldTime[ATTACK_THREE] = TIMEMANAGER->getWorldTime();
				}
				break;

			}

			if (0.1f + _attackWorldTime[ATTACK_SHOCK] >= TIMEMANAGER->getWorldTime())
			{
				if (_rndAttackType[2] == 1)
				{
					_shockAttack->ani = KEYANIMANAGER->findAnimation("shock", "leftShock");
				}
				else if (_rndAttackType[2] == 2)
				{
					_shockAttack->ani = KEYANIMANAGER->findAnimation("shock", "rightShock");
				}

				_shockAttack->x = _enemyManager->getVBoss()[0]->getX() - 70;
				_shockAttack->y = _enemyManager->getVBoss()[0]->getY() / 2 + 200;
				_shockAttack->rc = RectMakeCenter(_shockAttack->x, _shockAttack->y, 10, 300);
				_shockAttack->rc2 = RectMakeCenter(_shockAttack->x + 140, _shockAttack->y, 10, 300);

				_shockAttack->ani->start();

			}
			else
			{
				_shockAttack->rc = RectMakeCenter(NULL, NULL, NULL, NULL);
				_shockAttack->rc2 = RectMakeCenter(NULL, NULL, NULL, NULL);
				_attackWorldTime[ATTACK_SHOCK] = TIMEMANAGER->getWorldTime();
			}

		}

		//체력이 1000이상일때만
		else if (_enemyManager->getVBoss()[0]->getCurrentHP() > 1000)
		{
			switch (_attackPattern)
			{
			case ATTACK_ONE:

				//시간마다 공격
				if (3.0f + _attackWorldTime[ATTACK_ONE] <= TIMEMANAGER->getWorldTime() && _bulletPattern == BULLET_PATTERN::GOLD_BULLET)
				{
					_rndAttack[ATTACK_ONE] = RND->getRandomInt(1, 3);
					_rndAttackType[0] = RND->getRandomInt(1, 2);

					if (_rndAttackType[0] == 1)
					{
						_goldBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 1);
						_goldBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 1);
					}
					else if (_rndAttackType[0] == 2)
					{
						_goldBullet->bossFire(boss.x - 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);
						_goldBullet->bossFire(boss.x - 200, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);
						_goldBullet->bossFire(boss.x + 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);
						_goldBullet->bossFire(boss.x + 200, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_ONE], 3);

					}

					//랜덤어택
					if (_rndAttack[ATTACK_ONE] == 1)
					{
						_bulletPattern = BULLET_PATTERN::BLUE_BULLET;
						_attackPattern = ATTACK_TWO;
					}
					else if (_rndAttack[ATTACK_ONE] == 2)
					{
						_bulletPattern = BULLET_PATTERN::RED_BULLET;
						_attackPattern = ATTACK_THREE;
					}
					else if (_rndAttack[ATTACK_ONE] == 3)
					{
						_attackPattern = ATTACK_SHOCK;
					}

					_attackWorldTime[ATTACK_ONE] = TIMEMANAGER->getWorldTime();
				}
				break;
			case ATTACK_TWO:

				//시간마다 공격
				if (3.0f + _attackWorldTime[ATTACK_TWO] <= TIMEMANAGER->getWorldTime() && _bulletPattern == BULLET_PATTERN::BLUE_BULLET)
				{
					_rndAttack[ATTACK_TWO] = RND->getRandomInt(1, 3);

					_blueBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_TWO], 1);
					_blueBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_TWO], 1);

					//랜덤어택
					if (_rndAttack[ATTACK_TWO] == 1)
					{
						_bulletPattern = BULLET_PATTERN::GOLD_BULLET;
						_attackPattern = ATTACK_ONE;
					}
					else if (_rndAttack[ATTACK_TWO] == 2)
					{
						_bulletPattern = BULLET_PATTERN::RED_BULLET;
						_attackPattern = ATTACK_THREE;
					}
					else if (_rndAttack[ATTACK_ONE] == 3)
					{
						_attackPattern = ATTACK_SHOCK;
					}

					_attackWorldTime[ATTACK_TWO] = TIMEMANAGER->getWorldTime();

				}

				break;
			case ATTACK_THREE:

				//시간마다 공격
				if (3.0f + _attackWorldTime[ATTACK_THREE] <= TIMEMANAGER->getWorldTime() && _bulletPattern == BULLET_PATTERN::RED_BULLET)
				{
					_rndAttack[ATTACK_THREE] = RND->getRandomInt(1, 3);
					_rndAttackType[1] = RND->getRandomInt(1, 2);

					if (_rndAttackType[1] == 1)
					{
						_redBullet->bossFire(boss.x - 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 1);
						_redBullet->bossFire(boss.x + 150, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 1);
					}
					else if (_rndAttackType[1] == 2)
					{
						_redBullet->bossFire(boss.x - 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
						_redBullet->bossFire(boss.x - 200, boss.y - 100, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
						_redBullet->bossFire(boss.x + 100, boss.y, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
						_redBullet->bossFire(boss.x + 200, boss.y - 100, (PI / 180) * 270, _bulletSpeed[ATTACK_THREE], 3);
					}

					//랜덤어택
					if (_rndAttack[ATTACK_THREE] == 1)
					{
						_bulletPattern = BULLET_PATTERN::GOLD_BULLET;
						_attackPattern = ATTACK_ONE;
					}
					else if (_rndAttack[ATTACK_THREE] == 2)
					{
						_bulletPattern = BULLET_PATTERN::BLUE_BULLET;
						_attackPattern = ATTACK_TWO;
					}
					else if (_rndAttack[ATTACK_ONE] == 3)
					{
						_attackPattern = ATTACK_SHOCK;
					}

					_attackWorldTime[ATTACK_THREE] = TIMEMANAGER->getWorldTime();
				}
				break;
			case ATTACK_SHOCK:

				if (_enemyManager->getVBoss()[0]->countAttack() == true)
				{
					_rndAttack[ATTACK_SHOCK] = RND->getRandomInt(1, 3);
					_rndAttackType[2] = RND->getRandomInt(1, 2);

					if (_rndAttackType[2] == 1)
					{
						_shockAttack->ani = KEYANIMANAGER->findAnimation("shock", "leftShock");
					}
					else if (_rndAttackType[2] == 2)
					{
						_shockAttack->ani = KEYANIMANAGER->findAnimation("shock", "rightShock");
					}

					//랜덤어택
					if (_rndAttack[ATTACK_SHOCK] == 1)
					{
						_bulletPattern = BULLET_PATTERN::GOLD_BULLET;
						_attackPattern = ATTACK_ONE;
					}
					else if (_rndAttack[ATTACK_SHOCK] == 2)
					{
						_bulletPattern = BULLET_PATTERN::BLUE_BULLET;
						_attackPattern = ATTACK_TWO;
					}
					else if (_rndAttack[ATTACK_SHOCK] == 3)
					{
						_bulletPattern = BULLET_PATTERN::RED_BULLET;
						_attackPattern = ATTACK_THREE;
					}
					_shockAttack->x = _enemyManager->getVBoss()[0]->getX();
					_shockAttack->y = _enemyManager->getVBoss()[0]->getY() / 2 + 200;
					_shockAttack->rc = RectMakeCenter(_shockAttack->x, _shockAttack->y, 10, 300);
					_shockAttack->ani->start();

				}
				else
				{
					_shockAttack->rc = RectMakeCenter(NULL, NULL, NULL, NULL);
				}
				break;

			}
		}

		//두번째공격이고 파란색총알일때나 세가지 섞은총알일때만
		if ((_attackPattern == ATTACK_TWO && _bulletPattern == BULLET_PATTERN::BLUE_BULLET) || (_bulletPattern == BULLET_PATTERN::RGB_BULLET))
		{
			//블루총알일때만
			if (_bulletPattern == BULLET_PATTERN::BLUE_BULLET)
			{
				for (int i = 0; i < _blueBullet->getVBossBullet().size(); i++)
				{
					//두번째공격일때만 각도꺾음.
					if (_blueBullet->getVBossBullet()[i].y >= _player->getPlayerY())
					{
						(*_blueBullet->setVBossBullet())[0].angle = PI2;
						(*_blueBullet->setVBossBullet())[1].angle = PI;
					}
				}
			}
			//세가지 다 섞은총알일때만
			else if (_bulletPattern == BULLET_PATTERN::RGB_BULLET)
			{
				for (int i = 0; i < _rgbBullet->getVBossBullet().size(); i++)
				{
					if (_rgbBullet->getVBossBullet()[i].y >= _player->getPlayerY())
					{
						(*_rgbBullet->setVBossBullet())[0].angle = PI2;
						(*_rgbBullet->setVBossBullet())[1].angle = PI;
					}
				}
			}
		}
		//세번째 공격이고 레드총알이거나 세가지 섞은총알일때만
		if ((_attackPattern == ATTACK_THREE && _bulletPattern == BULLET_PATTERN::RED_BULLET) || (_bulletPattern == BULLET_PATTERN::RGB_BULLET))
		{
			//레드총알
			if (_bulletPattern == BULLET_PATTERN::RED_BULLET)
			{
				for (int i = 0; i < _redBullet->getVBossBullet().size(); i++)
				{
					if (_redBullet->getVBossBullet()[i].y >= _player->getPlayerY())
					{
						if (0.7f + _redBullet->getVBossBullet()[i].bulletWorlTime >= TIMEMANAGER->getWorldTime())
						{
							(*_redBullet->setVBossBullet())[i].speed = 0;
							(*_redBullet->setVBossBullet())[i].ani->setFPS(30);
						}
						else if (0.8f + _redBullet->getVBossBullet()[i].bulletWorlTime <= TIMEMANAGER->getWorldTime() && 1.8f + _redBullet->getVBossBullet()[i].bulletWorlTime > TIMEMANAGER->getWorldTime())
						{
							(*_redBullet->setVBossBullet())[i].speed = _redBullet->getVBossBullet()[i].speed + 0.3f;
							(*_redBullet->setVBossBullet())[0].angle = PI2;
							(*_redBullet->setVBossBullet())[1].angle = PI;
						}
						else if (1.8f + _redBullet->getVBossBullet()[i].bulletWorlTime <= TIMEMANAGER->getWorldTime())
						{
							(*_redBullet->setVBossBullet())[i].speed = 7;
							(*_redBullet->setVBossBullet())[i].ani->setFPS(7);
							(*_redBullet->setVBossBullet())[i].bulletWorlTime = TIMEMANAGER->getWorldTime();
						}
					}
				}
			}
			//세가지다 섞은총알
			else if (_bulletPattern == BULLET_PATTERN::RGB_BULLET)
			{
				for (int i = 0; i < _rgbBullet->getVBossBullet().size(); i++)
				{
					if (_rgbBullet->getVBossBullet()[i].y >= _player->getPlayerY())
					{
						if (0.7f + _rgbBullet->getVBossBullet()[i].bulletWorlTime >= TIMEMANAGER->getWorldTime())
						{
							(*_rgbBullet->setVBossBullet())[i].speed = 0;
							(*_rgbBullet->setVBossBullet())[i].ani->setFPS(30);
						}
						else if (0.8f + _rgbBullet->getVBossBullet()[i].bulletWorlTime <= TIMEMANAGER->getWorldTime() && 1.8f + _rgbBullet->getVBossBullet()[i].bulletWorlTime > TIMEMANAGER->getWorldTime())
						{
							(*_rgbBullet->setVBossBullet())[i].speed = _rgbBullet->getVBossBullet()[i].speed + 0.5f;
							(*_rgbBullet->setVBossBullet())[0].angle = PI2;
							(*_rgbBullet->setVBossBullet())[1].angle = PI;
						}
						else if (1.8f + _rgbBullet->getVBossBullet()[i].bulletWorlTime <= TIMEMANAGER->getWorldTime())
						{
							(*_rgbBullet->setVBossBullet())[i].speed = 7;
							(*_rgbBullet->setVBossBullet())[i].ani->setFPS(7);
							(*_rgbBullet->setVBossBullet())[i].bulletWorlTime = TIMEMANAGER->getWorldTime();
						}
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
