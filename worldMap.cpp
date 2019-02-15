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
	
	_playerWorldMap = new PlayerWorldMap;
	_world = new world;
	_camera = new camera;


	_world->init();
	_playerWorldMap->init();
	_camera->init(GAMESIZEX, GAMESIZEY, 1920, 1920);

	return S_OK;
}

void worldMap::release()
{
}

void worldMap::update()
{
	_camera->update(_playerWorldMap->getPlayerX(), _playerWorldMap->getPlayerY());
	_playerWorldMap->update();
}

void worldMap::render()
{
	_world->render(_camera->getCameraX(), _camera->getCameraY());
	_playerWorldMap->render(_camera->getCameraX(), _camera->getCameraY());
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


