#include "stdafx.h"
#include "town.h"
#pragma warning(disable:4996)

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
	IMAGEMANAGER->addFrameImage("townHuman", "image/townHuman.bmp", 700, 250, 14, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("black")->setAlpahBlend(true);

	_alphaValue = 255;

	_player = new player;
	_camera = new camera;
	_town = new townMap;
	_npcManager = new npcManager;

	_player->setTownManagerAddressLink(_town);
	_player->setnpcManagerAddressLink(_npcManager);
	_npcManager->setTownManagerAddressLink(_town);

	_player->init();
	_town->init();

	_npcManager->setBird();
	_npcManager->setElder();
	_npcManager->setElle();
	_npcManager->setTownHuman(TOWN_FISHMAN, 870, 870);
	_npcManager->setTownHuman(TOWN_GRANDFA, 200, 500);
	_npcManager->setTownHuman(TOWN_GRANDMA, 200, 400);
	_npcManager->init();

	_escape = RectMake(672, 1856 + 32, 128, 64);
	
	_camera->init(GAMESIZEX, GAMESIZEY, 1920, 1920);

	_worldTime = 0;
	_once = false;
	_worldMapIn = false;
	_fadeOut = true;
	

	return S_OK;
}

void town::release()
{
}

void town::update()
{
	townIn();
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_npcManager->update(2);
	_npcManager->aiBirdUpdate();
	worldMapIn();
	_player->update(false, 2);
}

void town::render()
{
	_town->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(),_camera->getCameraY());
	_npcManager->render(_camera->getCameraX(), _camera->getCameraY());
	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), _alphaValue);


	//Rectangle(getMemDC(), _escape);
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

void town::worldMapIn()
{
	RECT temp;
	if (IntersectRect(&temp, &_player->getPlayerRc(), &_escape))
	{
		_worldMapIn = true;
	}

	if (_worldMapIn)
	{
		_player->setTileCheck(false);

		_alphaValue += 3;

		_player->setPlayerDirection(DOWN);

		_player->setPlayerUnMove(true);

		_player->setPlayerPosY(_player->getPlayerY() + 3);

		if (!_once)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
		}

		if (1.4f + _worldTime <= TIMEMANAGER->getWorldTime())
		{

			playerSave();

			SCENEMANAGER->changeScene("worldMap");
		}


		_once = true;
	}
}

void town::playerSave()
{
	_player->setPlayerCurrentScene(PLAYERSCENE::TOWN);

	char temp[128];

	vector<string> vStr;

	vStr.push_back(itoa((int)_player->getPlayerCurrentScene(), temp, 10));

	TXTDATA->txtSave("saveFile/playerScene.scene", vStr);
}

void town::townIn()
{
	if (_fadeOut)
	{
		if (_fadeOut > 0)
		{
			_alphaValue -= 3;
		}

		if (_alphaValue < 0)
		{
			_alphaValue = 0;
			_fadeOut = false;
		}
	}
}
