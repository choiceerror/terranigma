#include "stdafx.h"
#include "dungeonMap.h"


dungeonMap::dungeonMap()
{
}


dungeonMap::~dungeonMap()
{
}

HRESULT dungeonMap::init()
{

	_dungeonFloor = DUNGEON_FLOOR::FIRST_FLOOR;
	load();
	return S_OK;
}

void dungeonMap::release()
{
}

void dungeonMap::update()
{
}

void dungeonMap::render(float cameraX, float cameraY)
{
	tileDraw(cameraX, cameraY);
}

void dungeonMap::load()
{
	//1Ãþ¸Ê
	if (_dungeonFloor == DUNGEON_FLOOR::FIRST_FLOOR)
	{
		HANDLE file2;
		DWORD read2;
		char mapSize[128];
		file2 = CreateFile("saveFile\\dungeonSize.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file2, mapSize, 128, &read2, NULL);

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

		file = CreateFile("saveFile\\dungeonSave.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

		_attribute = new DWORD[TILEX * TILEY];

		memset(_attribute, 0, sizeof(DWORD)*TILEX*TILEY);

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
		CloseHandle(file);
		CloseHandle(file2);
	}
	//2Ãþ¸Ê
	else if (_dungeonFloor == DUNGEON_FLOOR::SECOND_FLOOR)
	{
		HANDLE file2;
		DWORD read2;
		char mapSize[128];
		file2 = CreateFile("saveFile\\dungeon2FSize.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file2, mapSize, 128, &read2, NULL);

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

		file = CreateFile("saveFile\\dungeon2FSave.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

		_attribute = new DWORD[TILEX * TILEY];

		memset(_attribute, 0, sizeof(DWORD)*TILEX*TILEY);

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
		CloseHandle(file);
		CloseHandle(file2);
	}
}

void dungeonMap::tileDraw(float cameraX, float cameraY)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (PtInRect(&_vvMap[i][j]->rc, _ptMouse))
			{
				obx = _vvMap[i][j]->objFrameX;
				oby = _vvMap[i][j]->objFrameY;
				tix = _vvMap[i][j]->FrameX;
				tiy = _vvMap[i][j]->FrameY;
			}

			if (_vvMap[i][j]->rc.left - cameraX + 32 < 0) continue;
			if (_vvMap[i][j]->rc.left - cameraX > 1024) continue;
			if (_vvMap[i][j]->rc.top - cameraY + 32 < 0) continue;
			if (_vvMap[i][j]->rc.top - cameraY > 768) continue;

			if (_vvMap[i][j]->a == 0)
			{
				IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê4", getMemDC(),
					_vvMap[i][j]->rc.left - cameraX, _vvMap[i][j]->rc.top - cameraY,
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if (_vvMap[i][j]->a == 1)
			{
				IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê", getMemDC(),
					_vvMap[i][j]->rc.left - cameraX, _vvMap[i][j]->rc.top - cameraY,
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if (_vvMap[i][j]->a == 2)
			{
				IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê2", getMemDC(),
					_vvMap[i][j]->rc.left - cameraX, _vvMap[i][j]->rc.top - cameraY,
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
		}
	}

	//¿ÀºêÁ§Æ®
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (_vvMap[i][j]->obj == OBJ_NONE) continue;
			if (_vvMap[i][j]->rc.left - cameraX + 32 < 0) continue;
			if (_vvMap[i][j]->rc.left - cameraX > 1024) continue;
			if (_vvMap[i][j]->rc.top - cameraY + 32 < 0) continue;
			if (_vvMap[i][j]->rc.top - cameraY > 768) continue;

			if (_vvMap[i][j]->a == 0)
			{
				IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê4", getMemDC(),
					_vvMap[i][j]->rc.left - cameraX, _vvMap[i][j]->rc.top - cameraY,
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 1)
			{
				IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê", getMemDC(),
					_vvMap[i][j]->rc.left - cameraX, _vvMap[i][j]->rc.top - cameraY,
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 2)
			{
				IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê2", getMemDC(),
					_vvMap[i][j]->rc.left - cameraX, _vvMap[i][j]->rc.top - cameraY,
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
		}
	}

	char str[128];

	sprintf_s(str, "¿Àºêx:%d ¿Àºêy:%d  ÁöÇüx:%d ÁöÇüy:%d", obx, oby, tix, tiy);
	TextOut(getMemDC(), 600, 500, str, strlen(str));
}
