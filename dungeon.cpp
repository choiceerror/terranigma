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


	IMAGEMANAGER->addFrameImage("ballMonster", "image/enemy1.bmp", 64, 64, 4, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("fireMonster", "image/enemy2.bmp", 90, 87, 5, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("knightMonster", "image/enemy_3.bmp", 910, 800, 7, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("boss", "image/보스.bmp", 1048, 239, 4, 1, true, MAGENTA);

	_enemyManager = new enemyManager;
	_player = new player;
	_camera = new camera;
	_dungeon = new dungeonMap;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	//_player->setMapManagetAddressLink(_dungeon);

	_dungeon->init();
	_player->init();
	_enemyManager->init();

	_enemyManager->setEnemy();
	_camera->init(GAMESIZEX, GAMESIZEY, 3200, 3200);



	return S_OK;
}

void dungeon::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
	SAFE_DELETE(_dungeon);
}

void dungeon::update()
{
	_enemyManager->update();
	_player->update();
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
}

void dungeon::render()
{

	_dungeon->render(_camera->getCameraX(), _camera->getCameraY());

	_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(), _camera->getCameraY());

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
