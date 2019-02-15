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

	IMAGEMANAGER->addFrameImage("bird", "image/꼬꼬.bmp", 140, 160, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elle", "image/엘.bmp", 100, 140, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elder", "image/장로.bmp", 330, 40, 11, 1, true, RGB(255, 0, 255));

	_player = new player;
	_playerWorldMap = new PlayerWorldMap;
	_camera = new camera;
	_town = new townMap;
	_npcManager = new npcManager;


	_player->init();
	_playerWorldMap->init();
	_town->init();

	_npcManager->setBird();
	_npcManager->setElder();
	_npcManager->setElle();
	_npcManager->init();
	

	_player->setTownManagerAddressLink(_town);

	_camera->init(GAMESIZEX, GAMESIZEY, 3200, 3200);

	return S_OK;
}

void town::release()
{
}

void town::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_player->update(false, 2);
	_playerWorldMap->update();
	_npcManager->update();
	_npcManager->aiBirdUpdate();

}

void town::render()
{
	_player->render(0, 0);
	_npcManager->render(_camera->getCameraX(), _camera->getCameraY());
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
