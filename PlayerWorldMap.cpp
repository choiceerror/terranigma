#include "stdafx.h"
#include "PlayerWorldMap.h"


PlayerWorldMap::PlayerWorldMap()
{
}


PlayerWorldMap::~PlayerWorldMap()
{
}

HRESULT PlayerWorldMap::init()
{
	_playerImage = IMAGEMANAGER->findImage("player");

	int worldMapIdleLeft[] = {364};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapIdleLeft", "player", worldMapIdleLeft, 1, 5, true);
	int worldMapIdleRight[] = {361};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapIdleRight", "player", worldMapIdleRight, 1, 5, true);
	int worldMapIdleUp[] = { 367};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapIdleUp", "player", worldMapIdleUp, 1, 5, true);
	int worldMapIdleDown[] = {370};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapIdleDown", "player", worldMapIdleDown, 1, 5, true);
	int worldMapLeft[] = { 363, 364, 365 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapLeft", "player", worldMapLeft, 3, 20, true);
	int worldMapRight[] = { 360, 361, 362 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapRight", "player", worldMapRight, 3, 20, true);
	int worldMapUp[] = { 366, 367, 368 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapUp", "player", worldMapUp, 3, 20, true);
	int worldMapDown[] = { 369, 370, 371 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapDown", "player", worldMapDown, 3, 20, true);

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_speed = 3;
	_playerRc = RectMakeCenter(_x, _y + 10, 30, 30);
	_playerDirection = WORLDMAP_IDLE_DOWN;
	return S_OK;
}

void PlayerWorldMap::release()
{
}

void PlayerWorldMap::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
	{
		_x -= _speed;
		_playerDirection = WORLDMAP_MOVE_LEFT;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD4)) 	_playerDirection = WORLDMAP_IDLE_LEFT;
	
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
	{
		_x += _speed;
		_playerDirection = WORLDMAP_MOVE_RIGHT;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD6)) 	_playerDirection = WORLDMAP_IDLE_RIGHT;

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
	{
		_y -= _speed;
		_playerDirection = WORLDMAP_MOVE_UP;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD8)) 	_playerDirection = WORLDMAP_IDLE_UP;

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
	{
		_y += _speed;
		_playerDirection = WORLDMAP_MOVE_DOWN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD5)) 	_playerDirection = WORLDMAP_IDLE_DOWN;

	switch (_playerDirection)
	{
	case WORLDMAP_IDLE_LEFT:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapIdleLeft");
		_ani->start();
		break;
	case WORLDMAP_IDLE_RIGHT:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapIdleRight");
		_ani->start();
		break;
	case WORLDMAP_IDLE_UP:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapIdleUp");
		_ani->start();
		break;
	case WORLDMAP_IDLE_DOWN:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapIdleDown");
		_ani->start();
		break;
	case WORLDMAP_MOVE_LEFT:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapLeft");
		_ani->start();
		break;
	case WORLDMAP_MOVE_RIGHT:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapRight");
		_ani->start();
		break;
	case WORLDMAP_MOVE_UP:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapUp");
		_ani->start();
		break;
	case WORLDMAP_MOVE_DOWN:
		_ani = KEYANIMANAGER->findAnimation("ark", "worldMapDown");
		_ani->start();
		break;
	}

	_playerRc = RectMakeCenter(_x, _y + 10, 30, 30);
}

void PlayerWorldMap::render(float cameraX, float cameraY)
{
	_playerImage->expandAniRenderCenter(getMemDC(), _x - cameraX, _y - cameraY, _ani, 2, 2);
}
