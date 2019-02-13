#include "stdafx.h"
#include "town.h"


town::town()
{
}


town::~town()
{
}

HRESULT town::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	_player = new player;
	_playerWorldMap = new PlayerWorldMap;
	_camera = new camera;
	_town = new townMap;


	_player->init();
	_playerWorldMap->init();
	_town->init();

	_player->setTownManagerAddressLink(_town);

	_camera->init(GAMESIZEX, GAMESIZEY, 3200, 3200);
	return S_OK;
}

void town::release()
{
}

void town::update()
{
	_player->update(false);
	_playerWorldMap->update();
}

void town::render()
{
	_player->render(0 , 0);
	//_playerWorldMap->render(0, 0);
}

void town::setWindowsSize(int x, int y, int width, int height)
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
