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

	//load();

	IMAGEMANAGER->addFrameImage("ballMonster", "image/enemy1.bmp", 64, 64, 4, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("fireMonster", "image/enemy2.bmp", 90, 87, 5, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("knightMonster", "image/enemy_3.bmp", 910, 800, 7, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("boss", "image/보스.bmp", 1048, 239, 4, 1, true, MAGENTA);

	_enemyManager = new enemyManager;
	_player = new player;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);

	_player->init();
	_enemyManager->init();
	_enemyManager->setEnemy();

	

	return S_OK;
}

void dungeon::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
}

void dungeon::update()
{
	_enemyManager->update();
	_player->update();
}

void dungeon::render()
{
	tileDraw();

	_enemyManager->render();
	_player->render();
}

void dungeon::load()
{
	HANDLE file2;
	DWORD read2;
	char mapSize[128];

	file2 = CreateFile("saveFile\\mapSize.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file2, mapSize, 128, &read2, NULL);
	CloseHandle(file2);

	string sizeX, sizeY;
	bool x = true;
	for (int i = 0; i < strlen(mapSize); i++)
	{
		if (mapSize[i] == ',')
		{
			x = false;
			continue;
		}
		if (mapSize[i] == NULL) break;
		if (x)
		{
			sizeX += mapSize[i];
		}
		else
		{
			sizeY += mapSize[i];
		}
	}


	TILEX = stoi(sizeX);
	TILEY = stoi(sizeY);
	_vvMap.resize(TILEY);


	for (int i = 0; i < TILEY; i++)
	{
		_vvMap[i].resize(TILEX);
	}

	tagTile* _tiles = new tagTile[TILEX * TILEY];
	HANDLE file;
	DWORD read;

	file = CreateFile("saveFile\\mapSave.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);
	_attribute = new DWORD[TILEX * TILEY];

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_attribute[j + i * TILEX] = NULL;
			_vvMap[i][j] = &_tiles[j + i * TILEX];

			if (_vvMap[i][j]->obj == OBJ_WALL)
			{
				_attribute[j + i * TILEX] |= ATTR_UNMOVE;
			}
		}
	}
}

void dungeon::tileDraw()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (_vvMap[i][j]->a == 0)
			{
				IMAGEMANAGER->frameRender("타일맵4", getMemDC(),
					_vvMap[i][j]->rc.left, _vvMap[i][j]->rc.top,
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if (_vvMap[i][j]->a == 1)
			{
				IMAGEMANAGER->frameRender("타일맵", getMemDC(),
					_vvMap[i][j]->rc.left, _vvMap[i][j]->rc.top,
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if (_vvMap[i][j]->a == 2)
			{
				IMAGEMANAGER->frameRender("타일맵2", getMemDC(),
					_vvMap[i][j]->rc.left, _vvMap[i][j]->rc.top,
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
		}
	}

	//오브젝트
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (_vvMap[i][j]->obj == OBJ_NONE) continue;

			if (_vvMap[i][j]->a == 0)
			{
				IMAGEMANAGER->frameRender("타일맵4", getMemDC(),
					_vvMap[i][j]->rc.left, _vvMap[i][j]->rc.top,
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 1)
			{
				IMAGEMANAGER->frameRender("타일맵", getMemDC(),
					_vvMap[i][j]->rc.left, _vvMap[i][j]->rc.top,
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 2)
			{
				IMAGEMANAGER->frameRender("타일맵2", getMemDC(),
					_vvMap[i][j]->rc.left, _vvMap[i][j]->rc.top,
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
		}
	}

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

