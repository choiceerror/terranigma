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

	IMAGEMANAGER->findImage("black")->setAlpahBlend(true);

	_enemyManager = new enemyManager;
	_player = new player;
	_camera = new camera;
	_dungeonBossMap = new dungeonMap;
	_itemManager = new ItemManager;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	_player->setMapManagerAddressLink(_dungeonBossMap);
	_enemyManager->setDungeonMapAddressLink(_dungeonBossMap);
	_enemyManager->setCameraAddressLink(_camera);

	_dungeonBossMap->setDungeonFloor(DUNGEON_FLOOR::BOSS_FLOOR);
	_dungeonBossMap->init(_dungeonBossMap->getDungeonFloor());
	_player->init(false);
	_enemyManager->init();
	_itemManager->init();

	_enemyManager->setEnemy();

	//플레이어 초기위치
	//_player->setPlayerPosX(574);
	//_player->setPlayerPosY(2464);
	//_player->setPlayerDirection(UP);

	_camera->init(GAMESIZEX, GAMESIZEY, 1280, 2560);
	_dungeonDown = RectMake(512, 2528, 128, 32);

	_isAlphaOn = false;
	_isAlphaOut = true;
	_alphaValue = 255;

	_isDungeonDown = false;
	_once = false;
	_worldTime = 0;

	playerSceneLoad();

	_player->setPlayerCurrentScene(PLAYERSCENE::BOSS);

	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
	SAFE_DELETE(_dungeonBossMap);
	SAFE_DELETE(_camera);
}

void bossScene::update()
{
	alphaBlend();
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_itemManager->update();
	_enemyManager->update();
	_dungeonBossMap->update();
	dungeonChange();
	if (!_isDungeonDown)
	{
		_player->update(true, 1);
	}
}

void bossScene::render()
{
	_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
	_dungeonBossMap->render(_camera->getCameraX(), _camera->getCameraY());
	_enemyManager->bossBulletDraw(_camera->getCameraX(), _camera->getCameraY());
	_itemManager->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(), _camera->getCameraY(), true);

	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), _alphaValue);
}

void bossScene::dungeonChange()
{
	RECT temp;

	if (IntersectRect(&temp, &_player->getPlayerRc(), &_dungeonDown))
	{
		_isDungeonDown = true;
		_isAlphaOn = true;
	}
	if (_isDungeonDown)
	{
		if (!_once)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
		}

		_player->setPlayerUnMove(true);
		_player->setTileCheck(false);
		_player->setPlayerDirection(DOWN);
		_player->setPlayerPosY(_player->getPlayerY() + 3);

		if (1.4 + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_isDungeonDown = true;
			playerSceneSave();
			SCENEMANAGER->changeScene("dungeon2F");
		}

		_once = true;
	}
}

void bossScene::alphaBlend()
{
	if (_isAlphaOut)
	{
		if (_alphaValue > 0)
		{
			_alphaValue -= 3;
		}

		if (_alphaValue <= 0)
		{
			_isAlphaOut = false;
		}
	}

	if (_isAlphaOn)
	{
		if (_alphaValue < 255)
		{
			_alphaValue += 3;
		}

		if (_alphaValue > 255)
		{
			_alphaValue = 255;
		}
	}

	if (_isAlphaOut && _isAlphaOut)
	{
		_alphaValue -= 3;
	}
}

void bossScene::playerSceneSave()
{
	HANDLE file;
	DWORD save;
	
	file = CreateFile("saveFile/playerScene.txt", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int scene;

	scene = (int)_player->getPlayerCurrentScene();

	WriteFile(file, &scene, sizeof(int), &save, NULL);

	CloseHandle(file);
}

void bossScene::playerSceneLoad()
{
	HANDLE file;
	DWORD load;

	int scene;

	file = CreateFile("saveFile/playerScene.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &scene, sizeof(int), &load, NULL);

	if (scene > 7)
	{
		scene = (int)PLAYERSCENE::DUNGEON_2F;
	}

	_player->setPlayerCurrentScene((PLAYERSCENE)scene);

	if (_player->getPlayerCurrentScene() == PLAYERSCENE::DUNGEON_2F)
	{
		_player->setPlayerPosX(574);
		_player->setPlayerPosY(2464);
		_player->setPlayerDirection(UP);
	}

	if (_player->getPlayerY() < 2000)
	{
		_player->setPlayerPosX(574);
		_player->setPlayerPosY(2464);
		_player->setPlayerDirection(UP);
	}

	CloseHandle(file);
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
