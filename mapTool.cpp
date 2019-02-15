#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	setUp();

	_camera = new camera;
	_camera->init(800, 800, 3200, 3200);

	ptMouse2.x = 0;
	ptMouse2.y = 0;

	view.x = 0;
	view.y = 0;

	viewRc = RectMake(view.x, view.y, 5, 5);


	num = 2;
	tilenum = 0;
	for (int i = 0; i < 5; ++i)
	{
		box[i] = RectMakeCenter(900 + (i * 150), 750, 120, 50);
	}

	for (int i = 0; i < 6; ++i)
	{
		tileBox[i] = RectMakeCenter(1400 + (i * 70), 650, 50, 50);
	}

	check = false;
	_leftDragMode = false;

	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update()
{
	ClickBox();

	ptMouse2.x = _ptMouse.x + _camera->getCameraX();
	ptMouse2.y = _ptMouse.y + _camera->getCameraY();



	_camera->update(view.x, view.y);
	viewMove();
	mapSize();
	tileDrag();


	viewRc = RectMake(view.x - _camera->getCameraX(), view.y - _camera->getCameraY(), 20, 20);
}

void mapTool::render()
{
	PatBlt(IMAGEMANAGER->findImage("background")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);


	if (tilenum == 0)
	{
		IMAGEMANAGER->render("타일맵4", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("타일맵4")->GetWidth(), 0);
	}
	else if (tilenum == 1)
	{
		IMAGEMANAGER->render("타일맵", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("타일맵")->GetWidth(), 0);
	}
	else if (tilenum == 2)
	{
		IMAGEMANAGER->render("타일맵2", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("타일맵2")->GetWidth(), 0);
	}
	else if (tilenum == 3)
	{
		IMAGEMANAGER->render("타일맵5", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("타일맵5")->GetWidth(), 0);
	}
	else if (tilenum == 4)
	{
		IMAGEMANAGER->render("타일맵6", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("타일맵6")->GetWidth(), 0);
	}
	else if (tilenum == 5)
	{
		IMAGEMANAGER->render("타일맵7", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("타일맵7")->GetWidth(), 0);
	}
	//지형
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (_vvMap[i][j]->rc.left - _camera->getCameraX() + 32 < 0) continue;
			if (_vvMap[i][j]->rc.left - _camera->getCameraX() > 800) continue;
			if (_vvMap[i][j]->rc.top - _camera->getCameraY() + 32 < 0) continue;
			if (_vvMap[i][j]->rc.top - _camera->getCameraY() > 800) continue;

			//기본 세팅//
			//IMAGEMANAGER->frameRender("타일맵4", IMAGEMANAGER->findImage("background")->getMemDC(),
			//	_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
			//	_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);


			if (_vvMap[i][j]->a == 0)
			{
				IMAGEMANAGER->frameRender("타일맵4", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->a == 1))
			{
				IMAGEMANAGER->frameRender("타일맵", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->a == 2))
			{
				IMAGEMANAGER->frameRender("타일맵2", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->a == 3))
			{
				IMAGEMANAGER->frameRender("타일맵5", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->a == 4))
			{
				IMAGEMANAGER->frameRender("타일맵6", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->a == 5))
			{
				IMAGEMANAGER->frameRender("타일맵7", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
		}
	}

	////오브젝트
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (_vvMap[i][j]->obj == OBJ_NONE) continue;

			if (_vvMap[i][j]->rc.left - _camera->getCameraX() + 32 < 0) continue;
			if (_vvMap[i][j]->rc.left - _camera->getCameraX() > 800) continue;
			if (_vvMap[i][j]->rc.top - _camera->getCameraY() + 32 < 0) continue;
			if (_vvMap[i][j]->rc.top - _camera->getCameraY() > 800) continue;

			////기본 세팅//
			//IMAGEMANAGER->frameRender("타일맵4", IMAGEMANAGER->findImage("background")->getMemDC(),
			//	_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
			//	_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);

			if (_vvMap[i][j]->a == 0)
			{
				IMAGEMANAGER->frameRender("타일맵4", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 1)
			{
				IMAGEMANAGER->frameRender("타일맵", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 2)
			{
				IMAGEMANAGER->frameRender("타일맵2", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 3)
			{
				IMAGEMANAGER->frameRender("타일맵5", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 4)
			{
				IMAGEMANAGER->frameRender("타일맵6", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->a == 5)
			{
				IMAGEMANAGER->frameRender("타일맵7", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
		}
	}


	//==========================체크 박스 =====================================//

	for (int i = 0; i <6; ++i)
	{
		Rectangle(getMemDC(), tileBox[i]);
	}

	IMAGEMANAGER->render("save", getMemDC(), box[0].left, box[0].top);
	IMAGEMANAGER->render("load", getMemDC(), box[1].left, box[1].top);
	IMAGEMANAGER->render("terrain", getMemDC(), box[2].left, box[2].top);
	IMAGEMANAGER->render("object", getMemDC(), box[3].left, box[3].top);
	IMAGEMANAGER->render("eraser", getMemDC(), box[4].left, box[4].top);

	//==========================체크 박스 =====================================//
	//오른쪽
	if (_mouseUp || _ptMouse.x < _tilesetting[0].tilerc.left)
	{
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 180, 0));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		HBRUSH brush = CreateSolidBrush(MAGENTA);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

		if (_tileBox.x >= 0 && _tileBox.y >= 0)
		{
			MoveToEx(getMemDC(), _tilesetting[_tileBox.x + _tileBox.y * 30].tilerc.left, _tilesetting[_tileBox.x + _tileBox.y * 30].tilerc.top, NULL);
			LineTo(getMemDC(), _tilesetting[_tileBox.lastX + _tileBox.lastY * 30].tilerc.right, _tilesetting[_tileBox.x + _tileBox.y * 30].tilerc.top);
			LineTo(getMemDC(), _tilesetting[_tileBox.lastX + _tileBox.lastY * 30].tilerc.right, _tilesetting[_tileBox.lastX + _tileBox.lastY * 30].tilerc.bottom);
			LineTo(getMemDC(), _tilesetting[_tileBox.x + _tileBox.y * 30].tilerc.left, _tilesetting[_tileBox.lastX + _tileBox.lastY * 30].tilerc.bottom);
			LineTo(getMemDC(), _tilesetting[_tileBox.x + _tileBox.y * 30].tilerc.left, _tilesetting[_tileBox.x + _tileBox.y * 30].tilerc.top);
		}
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
		SelectObject(getMemDC(), oldPen);
		DeleteObject(pen);
	}
	//왼쪽
	if (_ptMouse.x < 800)
	{
		_mouseIndex.x = (_ptMouse.x + _camera->getCameraX())/ 32;
		_mouseIndex.y = (_ptMouse.y + _camera->getCameraY()) / 32;

		if (_mouseIndex.x < TILEX && _mouseIndex.y < TILEY)
		{
			if (!_leftDragMode)
			{
				HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 240, 255));
				HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("background")->getMemDC(), pen);
				HBRUSH brush = CreateSolidBrush(MAGENTA);
				HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("background")->getMemDC(), brush);

				MoveToEx(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.left - _camera->getCameraX(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.top - _camera->getCameraY(), NULL);
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.right - _camera->getCameraX(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.top - _camera->getCameraY());
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.right - _camera->getCameraX(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.bottom - _camera->getCameraY());
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.left - _camera->getCameraX(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.bottom - _camera->getCameraY());
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.left - _camera->getCameraX(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.top - _camera->getCameraY());

				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
				SelectObject(getMemDC(), oldPen);
				DeleteObject(pen);
			}
			
			if(!_mouseUp && _leftDragMode)
			{
				HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 240, 255));
				HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("background")->getMemDC(), pen);
				HBRUSH brush = CreateSolidBrush(MAGENTA);
				HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("background")->getMemDC(), brush);

				MoveToEx(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_leftStartDrag.y][_leftStartDrag.x]->rc.left - _camera->getCameraX(), _vvMap[_leftStartDrag.y][_leftStartDrag.x]->rc.top - _camera->getCameraY(), NULL);
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.right - _camera->getCameraX(), _vvMap[_leftStartDrag.y][_leftStartDrag.x]->rc.top - _camera->getCameraY());
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.right - _camera->getCameraX(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.bottom - _camera->getCameraY());
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_leftStartDrag.y][_leftStartDrag.x]->rc.left - _camera->getCameraX(), _vvMap[_mouseIndex.y][_mouseIndex.x]->rc.bottom - _camera->getCameraY());
				LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), _vvMap[_leftStartDrag.y][_leftStartDrag.x]->rc.left - _camera->getCameraX(), _vvMap[_leftStartDrag.y][_leftStartDrag.x]->rc.top - _camera->getCameraY());

				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
				SelectObject(getMemDC(), oldPen);
				DeleteObject(pen);
			}
		}
	}



	//=========================================================================
	char str[128];

	if (_leftDragMode)
	{
		sprintf_s(str, "드래그모드 활성화");
		TextOut(getMemDC(), 850, 530, str, strlen(str));
	}

	if (num == 0)
	{
		sprintf_s(str, "저장");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 1)
	{
		sprintf_s(str, "로드");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 2)
	{
		sprintf_s(str, "지형");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 3)
	{
		sprintf_s(str, "오브젝트");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	else if (num == 4)
	{
		sprintf_s(str, "지우기");
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}


	sprintf_s(str, "첫타일  x : %d   첫타일 y : %d", _mouseIndex.x, _mouseIndex.y);
	TextOut(getMemDC(), 1300, 520, str, strlen(str));

	sprintf_s(str, "마지막타일 x : %d   마지막타일 y : %d", _tileBox.lastX, _tileBox.lastY);
	TextOut(getMemDC(), 1300, 550, str, strlen(str));

	sprintf_s(str, "뺀 타일 x : %d   뺀 타일 y : %d", abs(_tileBox.q), abs(_tileBox.w));
	TextOut(getMemDC(), 1300, 580, str, strlen(str));

	sprintf_s(str, "타일X개수 : %d", TILEX);
	TextOut(getMemDC(), 1100, 530, str, strlen(str));
	sprintf_s(str, "타일Y개수 : %d", TILEY);
	TextOut(getMemDC(), 1100, 550, str, strlen(str));

	//if (_tileBox.x != _tileBox.y && _tileBox.q != _tileBox.w)
	//{
	//	rc = RectMakeCenter(_tilesetting[_tileBox.x + basicTileX * _tileBox.y].tilerc.left, _tilesetting[_tileBox.x + basicTileX * _tileBox.y].tilerc.top, 100, 100);
	//	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	//	FrameRect(getMemDC(), &rc, brush);
	//}
	if (_tileBox.x == _tileBox.y && _tileBox.q == _tileBox.w)
	{
		EllipseMakeCenter(getMemDC(), _tilesetting[_tileBox.x + basicTileX * _tileBox.y].tilerc.left, _tilesetting[_tileBox.x + basicTileX * _tileBox.y].tilerc.top, 6, 6);
	}
	Rectangle(IMAGEMANAGER->findImage("background")->getMemDC(), viewRc);




	IMAGEMANAGER->render("background", getMemDC(), 0, 0, 0, 0, 800, WINSIZEY);
}

void mapTool::setUp()
{
	Click = CTRL_TERRAINDRAW;

	TILEX = 40;
	TILEY = 40;
	_tilePosX = 0;
	_TilePosY = 0;

	for (int i = 0; i < TILEY; ++i)
	{
		vector<tagTile*> vTile;
		for (int j = 0; j < TILEX; ++j)
		{
			tagTile* _tile = new tagTile;
			_tile->a = 2;
			_tile->FrameX = 12;
			_tile->FrameY = 4;
			_tile->objFrameX = 0;
			_tile->objFrameY = 0;
			_tile->terrain = terrainSelect(_tile->FrameX, _tile->FrameY);
			_tile->obj = OBJ_NONE;
			_tile->rc = RectMake(j * TileSIZE, i * TileSIZE, TileSIZE, TileSIZE);
			vTile.push_back(_tile);
		}
		_vvMap.push_back(vTile);
	}

	for (int i = 0; i < basicTileY; ++i)
	{
		for (int j = 0; j < basicTileX; ++j)
		{
			_tilesetting[i * basicTileX + j].tilex = j;
			_tilesetting[i * basicTileX + j].tiley = i;


			SetRect(&_tilesetting[i * basicTileX + j].tilerc,
				(WINSIZEX - IMAGEMANAGER->findImage("타일맵4")->GetWidth()) + j * TileSIZE,
				i * TileSIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("타일맵4")->GetWidth()) + j * TileSIZE + TileSIZE,
				i * TileSIZE + TileSIZE);
		}
	}

	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		//SetRect(&_tiles[i * TILEX + j].rc, j * TileMainSIZE, i * TileMainSIZE, j * TileMainSIZE + TileMainSIZE, i * TileMainSIZE + TileMainSIZE);
	//		SetRect(&_vvMap[i][j]->rc, j * TileMainSIZE, i * TileMainSIZE, j * TileMainSIZE + TileMainSIZE, i * TileMainSIZE + TileMainSIZE);
	//	}
	//}

}

void mapTool::setMap()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			tagTile* pTile = _vvMap[i][j];

			if (PtInRect(&_vvMap[i][j]->rc, ptMouse2) && _ptMouse.x <= 800)
			{
				if (check == false && _leftDragMode == false)
				{
					if (Click == CTRL_TERRAINDRAW)
					{
						pTile->FrameX = _tileBox.x;
						pTile->FrameY = _tileBox.y;
						pTile->a = tilenum;
						pTile->terrain = terrainSelect(_tileBox.x, _tileBox.y);
					}
					else if (Click == CTRL_OBJDRAW)
					{
						pTile->objFrameX = _tileBox.x;
						pTile->objFrameY = _tileBox.y;
						pTile->a = tilenum;
						pTile->obj = objSelect(_tileBox.x, _tileBox.y);
					}
				}
				//드래그 했을때
				else if (check == true)
				{
					if (Click == CTRL_TERRAINDRAW)
					{
						for (int k = 0; k < abs(_tileBox.q) + 1; ++k)
						{
							for (int l = 0; l < abs(_tileBox.w) + 1; ++l)
							{
								_vvMap[i + l][j + k]->FrameX = _tileBox.x + k;
								_vvMap[i + l][j + k]->FrameY = _tileBox.y + l;
								_vvMap[i + l][j + k]->a = tilenum;
								_vvMap[i + l][j + k]->terrain = terrainSelect(_tileBox.x + k, _tileBox.y + l);
							}
						}
					}
					else if (Click == CTRL_OBJDRAW)
					{
						for (int k = 0; k < abs(_tileBox.q) + 1; ++k)
						{
							for (int l = 0; l < abs(_tileBox.w) + 1; ++l)
							{
								_vvMap[i + l][j + k]->objFrameX = _tileBox.x + k;
								_vvMap[i + l][j + k]->objFrameY = _tileBox.y + l;
								_vvMap[i + l][j + k]->a = tilenum;
								_vvMap[i + l][j + k]->obj = objSelect(_tileBox.x + k, _tileBox.y + l);
							}
						}
					}
				}
				if (Click == CTRL_ERASER)
				{
					pTile->objFrameX = NULL;
					pTile->objFrameY = NULL;
					pTile->obj = OBJ_NONE;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
}

void mapTool::ClickBox()
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
			tilenum = 2;
		}
		else if (PtInRect(&tileBox[3], _ptMouse))
		{
			tilenum = 3;
		}
		else if (PtInRect(&tileBox[4], _ptMouse))
		{
			tilenum = 4;
		}
		else if (PtInRect(&tileBox[5], _ptMouse))
		{
			tilenum = 5;
		}
		setMap();
	}
}

void mapTool::save()
{
	HANDLE file2;
	DWORD save2;
	char mapSize[128];
	sprintf_s(mapSize, "%d,%d", TILEX, TILEY);
	file2 = CreateFile("saveFile\\dungeonSize.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file2, mapSize, strlen(mapSize), &save2, NULL);

	CloseHandle(file2);

	tagTile* _tiles = new tagTile[TILEX * TILEY];
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[j + i * TILEX] = *_vvMap[i][j];
		}
	}

	HANDLE file;
	DWORD save;

	file = CreateFile("saveFile\\dungeonSave.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

	CloseHandle(file);

	delete[] _tiles;
}

void mapTool::load()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//SAFE_DELETE(_vvMap[i][j]);
		}
		_vvMap[i].clear();
	}
	_vvMap.clear();

	HANDLE file2;
	DWORD read2;
	char mapSize[128];

	file2 = CreateFile("saveFile\\dungeonSize.map", GENERIC_READ, NULL, NULL,
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

	file = CreateFile("saveFile\\dungeonSave.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_vvMap[i][j] = &_tiles[j + i * TILEX];
		}
	}
}

void mapTool::viewMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (view.y > 0)
		{
			view.y -= 20;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{

		view.y += 20;

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{

		view.x += 20;

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (view.x > 0)
		{
			view.x -= 20;
		}
	}
}

void mapTool::tileDrag()
{
	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < basicTileX * basicTileY; ++i)
		{
			if (PtInRect(&_tilesetting[i].tilerc, _ptMouse))
			{
				_tileBox.x = _tilesetting[i].tilex;
				_tileBox.y = _tilesetting[i].tiley;
			}
		}

		if (_ptMouse.x < 800)
		{
			_leftStartDrag.x = _mouseIndex.x;
			_leftStartDrag.y = _mouseIndex.y;
		}
		_mouseUp = false;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < basicTileX * basicTileY; ++i)
		{
			if (PtInRect(&_tilesetting[i].tilerc, _ptMouse))
			{
				_tileBox.lastX = _tilesetting[i].tilex;
				_tileBox.lastY = _tilesetting[i].tiley;
			}
		}
		_mouseUp = true;

		if (_ptMouse.x < 800)
		{
			_leftLastDrag.x = _mouseIndex.x;
			_leftLastDrag.y = _mouseIndex.y;

			_leftSubtraction.x = _leftLastDrag.x - _leftStartDrag.x;
			_leftSubtraction.y = _leftLastDrag.y - _leftStartDrag.y;

			tileLeftDrag();
		}


	}
	_tileBox.q = abs(_tileBox.lastX) - abs(_tileBox.x);
	_tileBox.w = abs(_tileBox.lastY) - abs(_tileBox.y);

	abs(_tileBox.q);
	abs(_tileBox.w);


	if (_tileBox.x == _tileBox.lastX)
	{
		check = false;
	}

	else if (_tileBox.x != _tileBox.lastX)
	{
		check = true;
	}
}

void mapTool::tileLeftDrag()
{
	if (!check && _leftDragMode)
	{
		for (int i = 0; i < _leftSubtraction.y + 1; ++i)
		{
			for (int j = 0; j < _leftSubtraction.x + 1; ++j)
			{
				if (Click == CTRL_TERRAINDRAW)
				{
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->FrameX = _tileBox.x;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->FrameY = _tileBox.y;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->a = tilenum;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->terrain = terrainSelect(_tileBox.x, _tileBox.y);
				}
				else if (Click == CTRL_OBJDRAW)
				{
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->objFrameX = _tileBox.x;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->objFrameY = _tileBox.y;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->a = tilenum;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->obj = objSelect(_tileBox.x, _tileBox.y);
				}
			}
		}
	}
}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 4)

		return TR_TILE_ONE;
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	for (int i = 0; i < basicTileX; ++i)
	{
		for (int j = 0; j < basicTileY; ++j)
		{
			if (frameX == i && frameY == j)

				return OBJ_WALL;
		}
	}
}

void mapTool::mapSize()
{
	//사이즈 줄이기  
	if (KEYMANAGER->isStayKeyDown('1') && TILEX > 1)
	{
		for (int i = 0; i < TILEY; i++)
		{
			tagTile* map = _vvMap[i].back();
			_vvMap[i].pop_back();
			//SAFE_DELETE(map);
		}
		TILEX--;
	}
	//사이즈 늘이기
	if (KEYMANAGER->isStayKeyDown('2') && TILEX < 100)
	{
		for (int i = 0; i < TILEY; ++i)
		{
			tagTile* _tile = new tagTile;
			_tile->a = 2;
			_tile->FrameX = 12;
			_tile->FrameY = 4;
			_tile->objFrameX = 0;
			_tile->objFrameY = 0;
			_tile->terrain = terrainSelect(_tile->FrameX, _tile->FrameY);
			_tile->obj = OBJ_NONE;
			_tile->rc = RectMake(TILEX * TileSIZE, i * TileSIZE, TileSIZE, TileSIZE);
			_vvMap[i].push_back(_tile);
		}
		TILEX++;

	}

	// 사이즈 줄이기
	if (KEYMANAGER->isStayKeyDown('3') && TILEY > 1)
	{
		for (int i = 0; i < TILEX; i++)
		{
			//	delete _vvMap.back()[i];
			_vvMap.back()[i] = nullptr;
		}
		_vvMap.pop_back();
		TILEY--;
	}
	// 사이즈 늘리기
	if (KEYMANAGER->isStayKeyDown('4') && TILEY < 100)
	{
		vector<tagTile*> vTile;
		for (int i = 0; i < TILEX; i++)
		{
			tagTile* _tile = new tagTile;
			_tile->a = 2;
			_tile->FrameX = 12;
			_tile->FrameY = 4;
			_tile->objFrameX = 0;
			_tile->objFrameY = 0;
			_tile->terrain = terrainSelect(_tile->FrameX, _tile->FrameY);
			_tile->obj = OBJ_NONE;
			_tile->rc = RectMake(i * TileSIZE, TILEY * TileSIZE, TileSIZE, TileSIZE);
			vTile.push_back(_tile);
		}
		_vvMap.push_back(vTile);
		TILEY++;
	}

	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		if (_leftDragMode)
		{
			_leftDragMode = false;
		}
		else
		{
			_leftDragMode = true;
		}
	}

}

void mapTool::setWindowsSize(int x, int y, int width, int height)
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
