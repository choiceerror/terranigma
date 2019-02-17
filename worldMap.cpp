#include "stdafx.h"
#include "worldMap.h"


worldMap::worldMap()
{
}


worldMap::~worldMap()
{
}

HRESULT worldMap::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);
	IMAGEMANAGER->addImage("fake3DHigh", 1024, 120);
	IMAGEMANAGER->addImage("blue", "image/fake3DBlue.bmp",1024,120,true,MAGENTA);
	IMAGEMANAGER->addImage("middle", "image/middle.bmp", 1024, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("middle2", "image/middle2.bmp", 1024, 50, true, MAGENTA);

	_playerWorldMap = new PlayerWorldMap;
	_world = new world;
	_camera = new camera;
	_mode7 = new mode7;

	_world->init();
	_playerWorldMap->init();
	_camera->init(GAMESIZEX, GAMESIZEY, 1920, 1920);
	_mode7->init(IMAGEMANAGER->findImage("worldMapTile"));
	_mode7->setMode7Point(_playerWorldMap->getPlayerX(), _playerWorldMap->getPlayerY(), (PI / 180) * 90);

	IMAGEMANAGER->findImage("blue")->setAlpahBlend(true);
	IMAGEMANAGER->findImage("middle")->setAlpahBlend(true);
	IMAGEMANAGER->findImage("middle2")->setAlpahBlend(true);
	IMAGEMANAGER->findImage("black")->setAlpahBlend(true);
	_alphaValue = 0;

	_playerWorldMap->setTownManagerAddressLink(_world);
	return S_OK;
}

void worldMap::release()
{
}

void worldMap::update()
{
	//_camera->update(_playerWorldMap->getPlayerX(), _playerWorldMap->getPlayerY());
	_playerWorldMap->update(3);

	_mode7->update();
	_mode7->setMode7Point(_playerWorldMap->getPlayerX(), _playerWorldMap->getPlayerY(), (PI / 180) * 90);
}

void worldMap::render()
{
	_world->render(_camera->getCameraX(), _camera->getCameraY());
	_playerWorldMap->render(_camera->getCameraX(), _camera->getCameraY());
	//IMAGEMANAGER->render("worldMapTile", getMemDC());
	_mode7->setObjectImage(IMAGEMANAGER->findImage("worldMapTile"));

	_mode7->render(getMemDC());

	//BitBlt(IMAGEMANAGER->findImage("fake3DHigh")->getMemDC(), 0, 0, GAMESIZEX, 120, IMAGEMANAGER->findImage("backBuffer")->getMemDC(), 0, GAMESIZEY - 120, SRCCOPY);
	POINT pt[3];
	pt[0].x = 0;
	pt[1].x = 1024;
	pt[2].x = 0;
	pt[0].y = 120;
	pt[1].y = 120;
	pt[2].y = 0;
	PlgBlt(IMAGEMANAGER->findImage("fake3DHigh")->getMemDC(), pt, IMAGEMANAGER->findImage("backBuffer")->getMemDC(), 0, GAMESIZEY -120, 1024, 120, NULL, 0, 0);

	if (_mode7->getFlatMode() == false)
	{
		IMAGEMANAGER->render("fake3DHigh", getMemDC(), 0, 0);
		IMAGEMANAGER->findImage("blue")->alphaRender(getMemDC(), 0, 0, 130);
		IMAGEMANAGER->findImage("middle")->alphaRender(getMemDC(), 0, 95, 150);
		IMAGEMANAGER->findImage("middle2")->alphaRender(getMemDC(), 0, 95, 100);
	}


	PatBlt(IMAGEMANAGER->findImage("worldMapTile")->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY, NULL);
	PatBlt(IMAGEMANAGER->findImage("fake3DHigh")->getMemDC(), 0, 0, GAMESIZEX, 80, NULL);
}

void worldMap::fake3DHighImage()
{
}

void worldMap::setWindowsSize(int x, int y, int width, int height)
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


