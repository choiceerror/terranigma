#include "stdafx.h"
#include "dungeon.h"


dungeon::dungeon()
{
}


dungeon::~dungeon()
{
}

HRESULT dungeon::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);


	IMAGEMANAGER->addFrameImage("ballMonster", "image/enemy1.bmp", 128, 128, 4, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("fireMonster", "image/enemy2.bmp", 180, 174, 5, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("knightMonster", "image/enemy3.bmp", 1820, 1600, 7, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("boss", "image/보스.bmp", 1048, 239, 4, 1, true, MAGENTA);
	EFFECTMANAGER->addEffect("deadEffect", "image/deadEffect2.bmp", 1496, 110, 136, 110, 5, 0.17f, 1000);
	_enemyManager = new enemyManager;
	_player = new player;
	_camera = new camera;
	_dungeon = new dungeonMap;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	_player->setMapManagerAddressLink(_dungeon);

	_dungeon->init();
	_player->init();
	_enemyManager->init();

	_enemyManager->setEnemy();
	_camera->init(GAMESIZEX, GAMESIZEY, GAMESIZEX, 3200);



	return S_OK;
}

void dungeon::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
	SAFE_DELETE(_dungeon);
	SAFE_DELETE(_camera);
}

void dungeon::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_player->update();
	_enemyManager->update();
}

void dungeon::render()
{

	_dungeon->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(), _camera->getCameraY());
	_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());


	//char str[128];

	//sprintf_s(str, "cameraX : %f", _camera->getCameraX());
	//TextOut(getMemDC(), 600, 500, str, strlen(str));

	//sprintf_s(str, "cameraY : %f", _camera->getCameraY());
	//TextOut(getMemDC(), 600, 520, str, strlen(str));

}

void dungeon::setWindowsSize(int x, int y, int width, int height)
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
