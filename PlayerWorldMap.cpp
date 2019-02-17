#include "stdafx.h"
#include "PlayerWorldMap.h"
#include "world.h"

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
	_speed = 5.f;
	_playerRc = RectMakeCenter(_x, _y, 30, 30);
	_playerDirection = WORLDMAP_IDLE_DOWN;
	
	_ani = KEYANIMANAGER->findAnimation("ark", "worldMapIdleDown");
	return S_OK;
}

void PlayerWorldMap::release()
{
}

void PlayerWorldMap::update(int check)
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !(KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		if (_x > 0)
		{
			_x -= _speed;
		}
		_playerDirection = WORLDMAP_MOVE_LEFT;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !(KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		if (_x < 1920)
		{
			_x += _speed;
		}
		_playerDirection = WORLDMAP_MOVE_RIGHT;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP) && !(KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
	{
		if (_y > 0)
		{
			_y -= _speed;
		}
		_playerDirection = WORLDMAP_MOVE_UP;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !(KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
	{
		if (_y < 1920)
		{
			_y += _speed;
		}
		_playerDirection = WORLDMAP_MOVE_DOWN;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _playerDirection == WORLDMAP_MOVE_LEFT) 	_playerDirection = WORLDMAP_IDLE_LEFT;

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _playerDirection == WORLDMAP_MOVE_RIGHT) 	_playerDirection = WORLDMAP_IDLE_RIGHT;
	
	if (KEYMANAGER->isOnceKeyUp(VK_UP) && _playerDirection == WORLDMAP_MOVE_UP) 	_playerDirection = WORLDMAP_IDLE_UP;
	
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _playerDirection == WORLDMAP_MOVE_DOWN) 	_playerDirection = WORLDMAP_IDLE_DOWN;

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

	_playerRc = RectMakeCenter(_x, _y + 13 , 30, 30);

	if (check == 3)
	{
		tileCheck();
	}
}

void PlayerWorldMap::render(float cameraX, float cameraY)
{
	_playerImage->expandAniRenderCenter(IMAGEMANAGER->findImage("worldMapTile")->getMemDC(), _x - cameraX, _y - cameraY, _ani, 1, 1);
	//Rectangle(getMemDC(), _playerRc);
}

void PlayerWorldMap::tileCheck()
{
	RECT rcCollision;
	RECT rc;

	rcCollision = _playerRc;

	TileX = _x / TileSIZE;
	TileY = _y / TileSIZE;


	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _playerDirection != WORLDMAP_MOVE_LEFT || _playerDirection != WORLDMAP_MOVE_RIGHT)
	{
		tileIndex[0].x = TileX - 1;
		tileIndex[0].y = TileY;


		for (int i = 0; i < 1; ++i)
		{
			if (_world->getTile(tileIndex[i].x, tileIndex[i].y)->obj == OBJ_WALL)
			{
				if (IntersectRect(&rc, &_world->getTile(tileIndex[i].x, tileIndex[i].y)->rc, &rcCollision))
				{
					_x += _speed;
				}
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _playerDirection != WORLDMAP_MOVE_LEFT || _playerDirection != WORLDMAP_MOVE_RIGHT)
	{
		tileIndex[0].x = TileX + 1;
		tileIndex[0].y = TileY;


		for (int i = 0; i < 1; ++i)
		{
			if (_world->getTile(tileIndex[i].x, tileIndex[i].y)->obj == OBJ_WALL)
			{
				if (IntersectRect(&rc, &_world->getTile(tileIndex[i].x, tileIndex[i].y)->rc, &rcCollision))
				{
					_x -= _speed;
				}
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _playerDirection != WORLDMAP_MOVE_UP || _playerDirection != WORLDMAP_MOVE_DOWN)
	{
		tileIndex[0].x = TileX ;
		tileIndex[0].y = TileY - 1;
		//tileIndex[1].x = TileX - 1;
		//tileIndex[1].y = TileY - 1;

		for (int i = 0; i < 1; ++i)
		{
			if (_world->getTile(tileIndex[i].x, tileIndex[i].y)->obj == OBJ_WALL)
			{
				if (IntersectRect(&rc, &_world->getTile(tileIndex[i].x, tileIndex[i].y)->rc, &rcCollision))
				{
					_y += _speed;
				}
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _playerDirection != WORLDMAP_MOVE_UP || _playerDirection != WORLDMAP_MOVE_DOWN)
	{
		tileIndex[0].x = TileX;
		tileIndex[0].y = TileY + 1;

		for (int i = 0; i < 1; ++i)
		{
			if (_world->getTile(tileIndex[i].x, tileIndex[i].y)->obj == OBJ_WALL)
			{
				if (IntersectRect(&rc, &_world->getTile(tileIndex[i].x, tileIndex[i].y)->rc, &rcCollision))
				{
					_y -= _speed;
				}
			}
		}
	}
}
