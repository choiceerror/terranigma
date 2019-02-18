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

	_enemyManager = new enemyManager;
	_player = new player;
	_camera = new camera;
	_dungeonBossMap = new dungeonMap;
	_itemManager = new ItemManager;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	_player->setMapManagerAddressLink(_dungeonBossMap);
	_enemyManager->setDungeonMapAddressLink(_dungeonBossMap);

	_dungeonBossMap->setDungeonFloor(DUNGEON_FLOOR::BOSS_FLOOR);
	_dungeonBossMap->init(_dungeonBossMap->getDungeonFloor());
	_player->init();
	_enemyManager->init();
	_itemManager->init();
	_enemyManager->setEnemy();
	_player->setPlayerPosX(1280 / 2 - 50);
	_player->setPlayerPosY(2500);

	_camera->init(GAMESIZEX, GAMESIZEY, 1280, 2560);

	_worldTime = TIMEMANAGER->getWorldTime();
	_isBossAppear = false;

	SOUNDMANAGER->addSound("bossSceneBGM", "sound/bossFight.mp3", true, true);

	_moveWorldTime = TIMEMANAGER->getWorldTime();

	for (int i = 0; i < 3; i++)
	{
		_moveGoal[i].x = 400 + i * 200;
		_moveGoal[i].y = 500 + i * 200;
	}
	return S_OK;
}

void bossScene::release()
{
}

void bossScene::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_player->update(false, 1);
	_enemyManager->update();
	_itemManager->update();
	bossAppear();
	
	movePattern();
}

void bossScene::render()
{
	char str[128];
	sprintf_s(str, "bossX : %f", _enemyManager->getVBoss()[0]->getX());
	TextOut(getMemDC(), 100, 200, str, strlen(str));

	sprintf_s(str, "bossY : %f", _enemyManager->getVBoss()[0]->getY());
	TextOut(getMemDC(), 100, 240, str, strlen(str));

	sprintf_s(str, "_rndMove : %d", _rndMove);
	TextOut(getMemDC(), 100, 260, str, strlen(str));

	sprintf_s(str, "moveWorldTime : %f", _moveWorldTime);
	TextOut(getMemDC(), 100, 280, str, strlen(str));

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "_moveGoalX : %f", _moveGoal[i].x);
		TextOut(getMemDC(), 600, i * 20, str, strlen(str));

		sprintf_s(str, "_moveGoalY : %f", _moveGoal[i].y);
		TextOut(getMemDC(), 800, i * 20, str, strlen(str));
	}

	if (_isBossAppear == true || _isOnce[BOSS_APPEAR] == true)
	{
		_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
	}
	_dungeonBossMap->render(_camera->getCameraX(), _camera->getCameraY());
	_itemManager->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(), _camera->getCameraY());


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
		_goal.x = GAMESIZEX / 2 + 70;
		_goal.y = 650;

		_elapsedTime = TIMEMANAGER->getElapsedTime();

		//골까지의 각도를 구해주고
		_goalAngle = getAngle(_enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY(), _goal.x, _goal.y);
		//골까지의 거리 구해줌.
		_goalDistance = getDistance(_enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY(), _goal.x, _goal.y);
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
			_camera->linearKeepMove(_goal.x, _goal.y + 50, 2, 100000);
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
			_isOnce[WORLDTIME] = true;
		}


		if (1.0f + _rndMoveWorldTime <= TIMEMANAGER->getWorldTime())
		{
			_rndMove = RND->getRandomInt(0, 2);

			_enemyManager->getVBoss()[0]->setMoveAngle(getAngle(_moveGoal[_rndMove].x, _moveGoal[_rndMove].y, _enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY()));
			//보스와 움직일 위치까지의 거리 구해줌.
			_enemyManager->getVBoss()[0]->setTargetDistance(getDistance(_moveGoal[_rndMove].x, _moveGoal[_rndMove].y, _enemyManager->getVBoss()[0]->getX(), _enemyManager->getVBoss()[0]->getY()));

			_rndMoveWorldTime = TIMEMANAGER->getWorldTime();
		}


	
		switch (_enemyManager->getVBoss()[0]->getState())
		{
		case BOSS_STATE_MOVE:

			//4초후에 움직여라
			if (4.0f + _moveWorldTime <= TIMEMANAGER->getWorldTime())
			{
				if (_isOnce[LINEAR_MOVE] == false)
				{
					_moveSpeed = _enemyManager->getVBoss()[0]->getTargetDistance() * (TIMEMANAGER->getElapsedTime() / 0.01f);
					_isOnce[LINEAR_MOVE] = true;
				}

				_enemyManager->getVBoss()[0]->setX(_enemyManager->getVBoss()[0]->getX() + cosf(_enemyManager->getVBoss()[0]->getMoveAngle() * _moveSpeed));
				_enemyManager->getVBoss()[0]->setY(_enemyManager->getVBoss()[0]->getY() + -sinf(_enemyManager->getVBoss()[0]->getMoveAngle() * _moveSpeed));
			
			}
			break;
			
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
