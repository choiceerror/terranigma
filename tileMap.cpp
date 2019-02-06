#include "stdafx.h"
#include "tileMap.h"


tileMap::tileMap()
{
}


tileMap::~tileMap()
{
}

HRESULT tileMap::init()
{
	IMAGEMANAGER->addFrameImage("Å¸ÀÏ¸Ê", "tileimage\\terranigma.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Å¸ÀÏ¸Ê2", "tileimage\\terranigma2.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Å¸ÀÏ¸Ê4", "tileimage\\terranigma4.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save", "tileimage\\save.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load", "tileimage\\load.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("terrain", "tileimage\\terrain.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object", "tileimage\\object.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eraser", "tileimage\\eraser.bmp", 120, 50, true, RGB(255, 0, 255));



	setUp();

	ptMouse2.x = 0;
	ptMouse2.y = 0;

	num = 2;
	tilenum = 0;
	for (int i = 0; i < 5; ++i)
	{
		box[i] = RectMakeCenter(900 + (i * 150), 750, 120, 50);
	}

	for (int i = 0; i < 5; ++i)
	{
		tileBox[i] = RectMakeCenter(1400 + (i * 70), 650, 50, 50);
	}
	return S_OK;
}

void tileMap::release()
{
}

void tileMap::update()
{
	ClickBox();

	ptMouse2.x = _ptMouse.x;
	ptMouse2.y = _ptMouse.y;
}

void tileMap::render()
{
	IMAGEMANAGER->render("background", getMemDC(), 0, 0, 0, 0, 800, WINSIZEY);
	
	if (tilenum == 0)
	{
		IMAGEMANAGER->render("Å¸ÀÏ¸Ê4", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Å¸ÀÏ¸Ê4")->GetWidth(), 0);
	}
	else if (tilenum == 1)
	{
		IMAGEMANAGER->render("Å¸ÀÏ¸Ê", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Å¸ÀÏ¸Ê")->GetWidth(), 0);
	}
	else if (tilenum == 2)
	{
		IMAGEMANAGER->render("Å¸ÀÏ¸Ê2", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Å¸ÀÏ¸Ê2")->GetWidth(), 0);
	}

	//ÁöÇü
	for (int i = 0; i < tileX * tileY; ++i)
	{
		if (_tiles[i].rc.left + 32 < 0) continue;
		if (_tiles[i].rc.left > 800) continue;
		if (_tiles[i].rc.top + 32 < 0) continue;
		if (_tiles[i].rc.top > 800) continue;


		if (_tiles[i].a == 0)
		{
			IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê4", IMAGEMANAGER->findImage("background")->getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].FrameX, _tiles[i].FrameY);
		}
		else if ((_tiles[i].a == 1))
		{
			IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê", IMAGEMANAGER->findImage("background")->getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].FrameX, _tiles[i].FrameY);
		}
		else if ((_tiles[i].a == 2))
		{
			IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê2", IMAGEMANAGER->findImage("background")->getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].FrameX, _tiles[i].FrameY);
		}
	}

	////¿ÀºêÁ§Æ®
	for (int i = 0; i < tileX * tileY; ++i)
	{
		
		if (_tiles[i].obj == OBJ_NONE) continue;
		
		if (_tiles[i].rc.left + 32 < 0) continue;
		if (_tiles[i].rc.left > 800) continue;
		if (_tiles[i].rc.top  + 32 < 0) continue;
		if (_tiles[i].rc.top  > 800) continue;

		if (_tiles[i].a == 0)
		{
			IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê4", IMAGEMANAGER->findImage("background")->getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].objFrameX, _tiles[i].objFrameY);
		}
		else if (_tiles[i].a == 1)
		{
			IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê", IMAGEMANAGER->findImage("background")->getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].objFrameX, _tiles[i].objFrameY);
		}
		else if (_tiles[i].a == 2)
		{
			IMAGEMANAGER->frameRender("Å¸ÀÏ¸Ê2", IMAGEMANAGER->findImage("background")->getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}


//==========================Ã¼Å© ¹Ú½º =====================================//

	for (int i = 0; i < 5; ++i)
	{
		Rectangle(getMemDC(), tileBox[i]);
	}

	IMAGEMANAGER->render("save",getMemDC(), box[0].left, box[0].top);
	IMAGEMANAGER->render("load", getMemDC(), box[1].left, box[1].top);
	IMAGEMANAGER->render("terrain", getMemDC(), box[2].left, box[2].top);
	IMAGEMANAGER->render("object", getMemDC(), box[3].left, box[3].top);
	IMAGEMANAGER->render("eraser", getMemDC(), box[4].left, box[4].top);

	
	char str[128];

	if (num == 0)
	{
		sprintf_s(str, "ÀúÀå");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 1)
	{
		sprintf_s(str, "·Îµå");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 2)
	{
		sprintf_s(str, "ÁöÇü");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 3)
	{
		sprintf_s(str, "¿ÀºêÁ§Æ®");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 4)
	{
		sprintf_s(str, "Áö¿ì±â");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
}

void tileMap::setUp()
{
	for (int i = 0; i < basicTileY; ++i)
	{
		for (int j = 0; j < basicTileX; ++j)
		{
			_tilesteeing[i * basicTileX + j].tilex = j;
			_tilesteeing[i * basicTileX + j].tiley = i;


			SetRect(&_tilesteeing[i * basicTileX + j].tilerc,
				(WINSIZEX - IMAGEMANAGER->findImage("Å¸ÀÏ¸Ê4")->GetWidth()) + j * TileSIZE,
				i * TileSIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("Å¸ÀÏ¸Ê4")->GetWidth()) + j * TileSIZE + TileSIZE,
				i * TileSIZE + TileSIZE);
		}
	}

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			SetRect(&_tiles[i * tileX + j].rc, j * TileMainSIZE, i * TileMainSIZE, j * TileMainSIZE + TileMainSIZE, i * TileMainSIZE + TileMainSIZE);
		}
	}

	Click = CTRL_TERRAINDRAW;

	for (int i = 0; i < tileX * tileY; ++i)
	{
		_tiles[i].FrameX = 0;
		_tiles[i].FrameY = 10;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].objFrameX, _tiles[i].objFrameY);
		_tiles[i].obj = OBJ_NONE;
	}

}

void tileMap::setMap()
{
	for (int i = 0; i < basicTileX * basicTileY; ++i)
	{
		if (PtInRect(&_tilesteeing[i].tilerc, _ptMouse))
		{
			_tileBox.x = _tilesteeing[i].tilex;
			_tileBox.y = _tilesteeing[i].tiley;
		}
	}


	for (int i = 0; i < tileX * tileY; ++i)
	{
		{   if (_ptMouse.x <= 800)
		{
			if (PtInRect(&_tiles[i].rc, ptMouse2))
			{
				if (Click == CTRL_TERRAINDRAW)
				{
					_tiles[i].FrameX = _tileBox.x;
					_tiles[i].FrameY = _tileBox.y;
					_tiles[i].a = tilenum;
					_tiles[i].terrain = terrainSelect(_tileBox.x, _tileBox.y);
				}
				else if (Click == CTRL_OBJDRAW)
				{
					_tiles[i].objFrameX = _tileBox.x;
					_tiles[i].objFrameY = _tileBox.y;
					_tiles[i].a = tilenum;
					_tiles[i].obj = objSelect(_tileBox.x, _tileBox.y);
				}
				else  if (Click == CTRL_ERASER)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameX = NULL;
					_tiles[i].obj = OBJ_NONE;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
		}
	}
}

void tileMap::ClickBox()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&box[0], _ptMouse))
		{
			Click = CTRL_SAVE;
			save();
			num = 0;
		}
		else if (PtInRect(&box[1], _ptMouse))
		{
			Click = CTRL_LOAD;
			load();
			num = 1;
		}
		else if (PtInRect(&box[2], _ptMouse))
		{
			Click = CTRL_TERRAINDRAW;
			num = 2;
		}
		else if (PtInRect(&box[3], _ptMouse))
		{
			Click = CTRL_OBJDRAW;
			num = 3;
		}
		else if (PtInRect(&box[4], _ptMouse))
		{
			Click = CTRL_ERASER;
			num = 4;
		}
		else if (PtInRect(&tileBox[0], _ptMouse))
		{
			tilenum = 0;
		}
		else if (PtInRect(&tileBox[1], _ptMouse))
		{
			tilenum = 1;
		}
		else if (PtInRect(&tileBox[2], _ptMouse))
		{
			tilenum =2;
		}
		else if (PtInRect(&tileBox[3], _ptMouse))
		{
			tilenum = 3;
		}
		setMap();
	}
}

void tileMap::save()
{
	HANDLE file;
	DWORD save;

	file = CreateFile("mapSave.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * tileX * tileY, &save, NULL);

	CloseHandle(file);
}

void tileMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("mapSave.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * tileX * tileY, &read, NULL);


	CloseHandle(file);
}

TERRAIN tileMap::terrainSelect(int frameX, int frameY)
{
	return TERRAIN();
}

OBJECT tileMap::objSelect(int frameX, int frameY)
{
	return OBJECT();
}
