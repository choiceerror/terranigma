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
	_image = IMAGEMANAGER->addFrameImage("타일맵4", "tileimage\\terranigma4.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	_image2 = IMAGEMANAGER->addFrameImage("타일맵", "tileimage\\terranigma3.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	_image3 = IMAGEMANAGER->addFrameImage("타일맵2", "tileimage\\terranigma2.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	_image4 = IMAGEMANAGER->addFrameImage("townTile", "tileimage\\townTile.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	_image5 = IMAGEMANAGER->addFrameImage("worldTile", "tileimage\\worldTile2.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	_image6 = IMAGEMANAGER->addFrameImage("bossTile", "tileimage\\bossTile.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("backMap", "image/mapToolbackground.bmp", 1920, 800, true, MAGENTA);
	IMAGEMANAGER->addImage("right", "tileimage/Right.bmp", 30, 30, true, WHITE);
	IMAGEMANAGER->addImage("left", "tileimage/Left.bmp", 30, 30, true, WHITE);
	IMAGEMANAGER->addImage("up", "tileimage/Up.bmp", 30, 30, true, WHITE);
	IMAGEMANAGER->addImage("down", "tileimage/Down.bmp", 30, 30, true, WHITE);
	setUp();

	_camera = new camera;
	_camera->init(800, 800, 3200, 3200);

	ptMouse2.x = 0;
	ptMouse2.y = 0;

	view.x = 0;
	view.y = 0;
//====== 이미지 위치 세팅======//
	_image->SetX(1800);
	_image2->SetX(1800);
	_image3->SetX(1800);
	_image4->SetX(1800);
	_image5->SetX(1800);
	_image6->SetX(1800);
//============================//
	viewRc = RectMake(view.x, view.y, 5, 5);

	_mapEnd.x = 855;
	num = 2;
	tilenum = 7;
	for (int i = 0; i < 5; ++i)
	{
		box[i] = RectMakeCenter(900 + (i * 150), 750, 120, 50);
	}
	for (int i = 0; i < 4; ++i)
	{
		if (i == 0)
		{
			sizeButton[i] = RectMakeCenter(900, 550, 30, 30);
		}
		else if (i == 1)
		{
			sizeButton[i] = RectMakeCenter(900, 600, 30, 30);
		}
		else
		{
			sizeButton[i] = RectMakeCenter(725 + (i * 70), 575, 30, 30);
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		SelectMap[i] = RectMakeCenter(1500 + (i * 150), 650, 30, 30);
	}


	for (int i = 0; i < 6; ++i)
	{
		tileMoveBox[i] = RectMakeCenter(WINSIZEX - 16, 16 + (i * 32), 30, 30);
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

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&SelectMap[0], _ptMouse))
		{
			if (selectNumber > 0)
			{
				selectNumber--;
			}
		}
		else if (PtInRect(&SelectMap[1], _ptMouse))
		{
			if (selectNumber < 4)
			{
				selectNumber++;
			}
		}
	}
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (PtInRect(&_vvMap[i][j]->rc, ptMouse2))
			{		
				if (ptMouse2.x -_camera->getCameraX() <= 800)
				{
					x = _vvMap[i][j]->rc.left / TileSIZE;
					y = _vvMap[i][j]->rc.top / TileSIZE;
				}
			}
		}
	}
	tileimgMove();
	viewRc = RectMake(view.x - _camera->getCameraX(), view.y - _camera->getCameraY(), 20, 20);
}

void mapTool::render()
{
	PatBlt(IMAGEMANAGER->findImage("background")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	IMAGEMANAGER->render("backMap", getMemDC());

	IMAGEMANAGER->render("right", getMemDC(), sizeButton[3].left, sizeButton[3].top);
	IMAGEMANAGER->render("left", getMemDC(), sizeButton[2].left, sizeButton[2].top);
	IMAGEMANAGER->render("up", getMemDC(), sizeButton[0].left, sizeButton[0].top);
	IMAGEMANAGER->render("down", getMemDC(), sizeButton[1].left, sizeButton[1].top);
	IMAGEMANAGER->render("left", getMemDC(), SelectMap[0].left, SelectMap[0].top);
	IMAGEMANAGER->render("right", getMemDC(), SelectMap[1].left, SelectMap[1].top);
	if (tilenum == 0)
	{
	_image->render(getMemDC(), _image->GetX() - _mapSpeed, 0);	
	}
	else if (tilenum == 1)
	{
		_image2->render(getMemDC(), _image2->GetX() - _mapSpeed, 0);
	}
	else if (tilenum == 2)
	{
		_image3->render(getMemDC(), _image3->GetX() - _mapSpeed, 0);
	}
	else if (tilenum == 3)
	{
		_image4->render(getMemDC(), _image4->GetX() - _mapSpeed, 0);
	}
	else if (tilenum == 4)
	{
		_image5->render(getMemDC(), _image5->GetX() - _mapSpeed, 0);
	}
	else if (tilenum == 5)
	{
		_image6->render(getMemDC(), _image6->GetX() - _mapSpeed, 0);
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

			if (_vvMap[i][j]->selectTile == 0)
			{
				IMAGEMANAGER->frameRender("타일맵4", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->selectTile == 1))
			{
				IMAGEMANAGER->frameRender("타일맵", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->selectTile == 2))
			{
				IMAGEMANAGER->frameRender("타일맵2", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->selectTile == 3))
			{
				IMAGEMANAGER->frameRender("townTile", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->selectTile == 4))
			{
				IMAGEMANAGER->frameRender("worldTile", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}
			else if ((_vvMap[i][j]->selectTile == 5))
			{
				IMAGEMANAGER->frameRender("bossTile", IMAGEMANAGER->findImage("background")->getMemDC(),
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

			if (_vvMap[i][j]->selectTile == 0)
			{
				IMAGEMANAGER->frameRender("타일맵4", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->selectTile == 1)
			{
				IMAGEMANAGER->frameRender("타일맵", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->selectTile == 2)
			{
				IMAGEMANAGER->frameRender("타일맵2", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->selectTile == 3)
			{
				IMAGEMANAGER->frameRender("townTile", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->selectTile == 4)
			{
				IMAGEMANAGER->frameRender("worldTile", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
			else if (_vvMap[i][j]->selectTile == 5)
			{
				IMAGEMANAGER->frameRender("bossTile", IMAGEMANAGER->findImage("background")->getMemDC(),
					_vvMap[i][j]->rc.left - _camera->getCameraX(), _vvMap[i][j]->rc.top - _camera->getCameraY(),
					_vvMap[i][j]->objFrameX, _vvMap[i][j]->objFrameY);
			}
		}
	}


	//==========================체크 박스 =====================================//

	for (int i = 0; i < 6; ++i)
	{
		Rectangle(getMemDC(), tileMoveBox[i]);
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
		_mouseIndex.x = (_ptMouse.x + _camera->getCameraX()) / 32;
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

			if (!_mouseUp && _leftDragMode)
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
		TextOut(getMemDC(), 950, 530, str, strlen(str));
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

	sprintf_s(str, "현재타일지점 : %d  %d",	 x ,y);
	{
		TextOut(getMemDC(), 1000, 580, str, strlen(str));
	}


	//sprintf_s(str, "첫타일  x : %d   첫타일 y : %d", _mouseIndex.x, _mouseIndex.y);
	//TextOut(getMemDC(), 1300, 520, str, strlen(str));
	//
	sprintf_s(str, "마지막타일 x : %d   마지막타일 y : %d", _tileBox.lastX, _tileBox.lastY);
	TextOut(getMemDC(), 1300, 550, str, strlen(str));
	//
	//sprintf_s(str, "뺀 타일 x : %d   뺀 타일 y : %d", abs(_tileBox.q), abs(_tileBox.w));
	//TextOut(getMemDC(), 1300, 580, str, strlen(str));

	sprintf_s(str, "타일X개수 : %d", TILEX);
	TextOut(getMemDC(), 1000, 530, str, strlen(str));
	sprintf_s(str, "타일Y개수 : %d", TILEY);
	TextOut(getMemDC(), 1000, 550, str, strlen(str));

	if (selectNumber == 0)
	{
		sprintf_s(str, "던전");
		TextOut(getMemDC(), 1530, 645, str, strlen(str));
	}
	else if (selectNumber == 1)
	{
		sprintf_s(str, "던전2F");
		TextOut(getMemDC(), 1530, 645, str, strlen(str));
	}
	else if (selectNumber == 2)
	{
		sprintf_s(str, "보스방");
		TextOut(getMemDC(), 1530, 645, str, strlen(str));
	}
	else if (selectNumber == 3)
	{
		sprintf_s(str, "마을");
		TextOut(getMemDC(), 1530, 645, str, strlen(str));
	}
	else if (selectNumber == 4)
	{
		sprintf_s(str, "월드맵");
		TextOut(getMemDC(), 1530, 645, str, strlen(str));
	}
	
	//sprintf_s(str, "맵 스피드 : %f" , _mapSpeed);
	//TextOut(getMemDC(), 930, 605, str, strlen(str));
	//
	//sprintf_s(str, "월드 타임 : %f", _worldTime);
	//TextOut(getMemDC(), 930, 635, str, strlen(str));
	//
	//
	//sprintf_s(str, "일립스 타임 : %f", _elapsedTime);
	//TextOut(getMemDC(), 930, 665, str, strlen(str));
	//
	//
	//sprintf_s(str, "앵글 : %f", _mapAngle);
	//TextOut(getMemDC(), 930, 695, str, strlen(str));
	//
	//
	//sprintf_s(str, "거리 : %f", _mapDistance);
	//TextOut(getMemDC(), 930, 725, str, strlen(str));
	
	//sprintf_s(str, "num : %d  %d  %d  %d  %d  %d",   num1,num2,num3,num4,num5,num6);
	//TextOut(getMemDC(), 1130, 600, str, strlen(str));

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
			_tile->selectTile = 0;
			_tile->FrameX = 0;
			_tile->FrameY = 15;
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
						pTile->selectTile = tilenum;
						pTile->terrain = terrainSelect(_tileBox.x, _tileBox.y);
					}
					else if (Click == CTRL_OBJDRAW)
					{
						pTile->objFrameX = _tileBox.x;
						pTile->objFrameY = _tileBox.y;
						pTile->selectTile = tilenum;
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
								_vvMap[i + l][j + k]->selectTile = tilenum;
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
								_vvMap[i + l][j + k]->selectTile = tilenum;
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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&box[0], _ptMouse))
		{
			Click = CTRL_SAVE;
			if (selectNumber == 0)
			{
				save(SaveAndLoad::DUNGEON);
			}
			if (selectNumber == 1)
			{
				save(SaveAndLoad::DUNGEON2F);
			}
			if (selectNumber == 2)
			{
				save(SaveAndLoad::BOSS);
			}
			if (selectNumber == 3)
			{
				save(SaveAndLoad::TOWN);
			}
			if (selectNumber == 4)
			{
				save(SaveAndLoad::WORLDMAP);
			}
			num = 0;
		}
		else if (PtInRect(&box[1], _ptMouse))
		{
			Click = CTRL_LOAD;
			if (selectNumber == 0)
			{
				load(SaveAndLoad::DUNGEON);
			}
			if (selectNumber == 1)
			{
				load(SaveAndLoad::DUNGEON2F);
			}
			if (selectNumber == 2)
			{
				load(SaveAndLoad::BOSS);
			}
			if (selectNumber == 3)
			{
				load(SaveAndLoad::TOWN);
			}
			if (selectNumber == 4)
			{
				load(SaveAndLoad::WORLDMAP);
			}
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
		//else if (PtInRect(&tileSelect[0], _ptMouse) && tilenum > 0)
		//{
		//	tilenum--;
		//}
		//else if (PtInRect(&tileSelect[1], _ptMouse) && tilenum < 5)
		//{
		//	tilenum++;
		//}
		else if (PtInRect(&tileMoveBox[0], _ptMouse))
		{
			tilenum = 0;
		}
		else if (PtInRect(&tileMoveBox[1], _ptMouse))
		{
			tilenum = 1;
		}
		else if (PtInRect(&tileMoveBox[2], _ptMouse))
		{
			tilenum = 2;
		}
		else if (PtInRect(&tileMoveBox[3], _ptMouse))
		{
			tilenum = 3;
		}
		else if (PtInRect(&tileMoveBox[4], _ptMouse))
		{
			tilenum = 4;
		}
		else if (PtInRect(&tileMoveBox[5], _ptMouse))
		{
			tilenum = 5;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		setMap();
	}
}

void mapTool::save(SaveAndLoad saveNum)
{
	if (saveNum == SaveAndLoad::DUNGEON)
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

	else if (saveNum == SaveAndLoad::DUNGEON2F)
	{
		HANDLE file2;
		DWORD save2;
		char mapSize[128];
		sprintf_s(mapSize, "%d,%d", TILEX, TILEY);
		file2 = CreateFile("saveFile\\dungeon2FSize.map", GENERIC_WRITE, NULL, NULL,
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

		file = CreateFile("saveFile\\dungeon2FSave.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

		CloseHandle(file);

		delete[] _tiles;
	}

	else if (saveNum == SaveAndLoad::BOSS)
	{
		HANDLE file2;
		DWORD save2;
		char mapSize[128];
		sprintf_s(mapSize, "%d,%d", TILEX, TILEY);
		file2 = CreateFile("saveFile\\bossSize.map", GENERIC_WRITE, NULL, NULL,
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

		file = CreateFile("saveFile\\bossSave.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

		CloseHandle(file);

		delete[] _tiles;
	}
	else if (saveNum == SaveAndLoad::TOWN)
	{
		HANDLE file2;
		DWORD save2;
		char mapSize[128];
		sprintf_s(mapSize, "%d,%d", TILEX, TILEY);
		file2 = CreateFile("saveFile\\townSize.map", GENERIC_WRITE, NULL, NULL,
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

		file = CreateFile("saveFile\\townSave.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

		CloseHandle(file);

		delete[] _tiles;
	}
	else if (saveNum == SaveAndLoad::WORLDMAP)
	{
		HANDLE file2;
		DWORD save2;
		char mapSize[128];
		sprintf_s(mapSize, "%d,%d", TILEX, TILEY);
		file2 = CreateFile("saveFile\\worldSize.map", GENERIC_WRITE, NULL, NULL,
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

		file = CreateFile("saveFile\\worldSave.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

		CloseHandle(file);

		delete[] _tiles;
	}
}

void mapTool::load(SaveAndLoad loadNum)
{
	if (loadNum == SaveAndLoad::DUNGEON)
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

	else if (loadNum == SaveAndLoad::DUNGEON2F)
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

		file2 = CreateFile("saveFile\\dungeon2FSize.map", GENERIC_READ, NULL, NULL,
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

		file = CreateFile("saveFile\\dungeon2FSave.map", GENERIC_READ, NULL, NULL,
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

	else if (loadNum == SaveAndLoad::BOSS)
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

		file2 = CreateFile("saveFile\\bossSize.map", GENERIC_READ, NULL, NULL,
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

		file = CreateFile("saveFile\\bossSave.map", GENERIC_READ, NULL, NULL,
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

	else if (loadNum == SaveAndLoad::TOWN)
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

		file2 = CreateFile("saveFile\\townSize.map", GENERIC_READ, NULL, NULL,
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

		file = CreateFile("saveFile\\townSave.map", GENERIC_READ, NULL, NULL,
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

	else if (loadNum == SaveAndLoad::WORLDMAP)
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

		file2 = CreateFile("saveFile\\worldSize.map", GENERIC_READ, NULL, NULL,
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

		file = CreateFile("saveFile\\worldSave.map", GENERIC_READ, NULL, NULL,
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
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->selectTile = tilenum;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->terrain = terrainSelect(_tileBox.x, _tileBox.y);
				}
				else if (Click == CTRL_OBJDRAW)
				{
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->objFrameX = _tileBox.x;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->objFrameY = _tileBox.y;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->selectTile = tilenum;
					_vvMap[i + _leftStartDrag.y][j + _leftStartDrag.x]->obj = objSelect(_tileBox.x, _tileBox.y);
				}
			}
		}
	}
}

void mapTool::tileimgMove()
{
	_mapAngle = getAngle(1800, 0, _mapEnd.x, _mapEnd.y);
	_mapDistance = getDistance(1800, 0, _mapEnd.x, _mapEnd.y);

//===================맨 위 타일 ======================//
	if (tilenum == 0)
	{
		num1++;
		if (num1 < 2)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
			_elapsedTime = TIMEMANAGER->getElapsedTime();
			_mapSpeed = _mapDistance * (_elapsedTime / 1.0f);
		}
		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_image->SetX(_image->GetX() + cosf(_mapAngle) * _mapSpeed);
			_image->SetY(_image->GetY() + -sinf(_mapAngle) * _mapSpeed);
			tileMoveBox[0].left -= _mapSpeed;
			tileMoveBox[0].right -= _mapSpeed;

		
		}
		else if (0.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_image->SetX(856);
			tileMoveBox[0].left = 807;
			tileMoveBox[0].right = 840;
		}

	}
	else
	{
		num1 = 0;
		_image->SetX(1800);
		tileMoveBox[0].left = WINSIZEX - 32;
		tileMoveBox[0].right = WINSIZEX;
	}
//=============== 2번 타일 =======================//
	if (tilenum == 1)
	{
		num2++;
		if (num2 < 2)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
			_elapsedTime = TIMEMANAGER->getElapsedTime();
			_mapSpeed = _mapDistance * (_elapsedTime / 1.0f);
		}

		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_image2->SetX(_image2->GetX() + cosf(_mapAngle) * _mapSpeed);
			_image2->SetY(_image2->GetY() + -sinf(_mapAngle) * _mapSpeed);
			tileMoveBox[1].left -= _mapSpeed;
			tileMoveBox[1].right -= _mapSpeed;
		}
		else if (0.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_image2->SetX(856);
			tileMoveBox[1].left = 807;
			tileMoveBox[1].right = 840;
		}
	}
	else
	{
		num2 = 0;
		_image2->SetX(1800);
		tileMoveBox[1].left = WINSIZEX - 32;
		tileMoveBox[1].right = WINSIZEX;
	}
//===================3번 타일======================//
	if (tilenum == 2)
	{
		num3++;
		if (num3 < 2)
		{
			_worldTime= TIMEMANAGER->getWorldTime();
			_elapsedTime = TIMEMANAGER->getElapsedTime();
			_mapSpeed = _mapDistance * (_elapsedTime / 1.0f);
		}

		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_image3->SetX(_image3->GetX() + cosf(_mapAngle) * _mapSpeed);
			_image3->SetY(_image3->GetY() + -sinf(_mapAngle) * _mapSpeed);
			tileMoveBox[2].left -= _mapSpeed;
			tileMoveBox[2].right -= _mapSpeed;
		}
		else if (0.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_image3->SetX(856);
			tileMoveBox[2].left = 807;
			tileMoveBox[2].right = 840;
		}
	}
	else
	{
		num3 = 0;
		_image3->SetX(1800);
		tileMoveBox[2].left = WINSIZEX - 32;
		tileMoveBox[2].right = WINSIZEX;
	}
//========================4번 타일 ==================//
	if (tilenum == 3)
	{
		num4++;
		if (num4 < 2)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
			_elapsedTime = TIMEMANAGER->getElapsedTime();
			_mapSpeed = _mapDistance * (_elapsedTime / 1.0f);
		}

		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_image4->SetX(_image4->GetX() + cosf(_mapAngle) * _mapSpeed);
			_image4->SetY(_image4->GetY() + -sinf(_mapAngle) * _mapSpeed);
			tileMoveBox[3].left -= _mapSpeed;
			tileMoveBox[3].right -= _mapSpeed;
		}
		else if (0.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_image4->SetX(856);
			tileMoveBox[3].left = 807;
			tileMoveBox[3].right = 840;
		}
	}
	else
	{
		num4 = 0;
		_image4->SetX(1800);
		tileMoveBox[3].left = WINSIZEX - 32;
		tileMoveBox[3].right = WINSIZEX;
	}

	//========================5번 타일 ==========================//
	if (tilenum == 4)
	{
		num5++;
		if (num5 < 2)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
			_elapsedTime = TIMEMANAGER->getElapsedTime();
			_mapSpeed = _mapDistance * (_elapsedTime / 1.0f);
		}

		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_image5->SetX(_image5->GetX() + cosf(_mapAngle) * _mapSpeed);
			_image5->SetY(_image5->GetY() + -sinf(_mapAngle) * _mapSpeed);
			tileMoveBox[4].left -= _mapSpeed;
			tileMoveBox[4].right -= _mapSpeed;
		}
		else if (0.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_image5->SetX(856);
			tileMoveBox[4].left = 807;
			tileMoveBox[4].right = 840;
		}
	}
	else
	{
		num5 = 0;
		_image5->SetX(1800);
		tileMoveBox[4].left = WINSIZEX - 32;
		tileMoveBox[4].right = WINSIZEX;
	}
// ==========================6번 타일 ========================//
	if (tilenum == 5)
	{
		num6++;
		if (num6 < 2)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
			_elapsedTime = TIMEMANAGER->getElapsedTime();
			_mapSpeed = _mapDistance * (_elapsedTime / 1.0f);
		}

		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_image6->SetX(_image6->GetX() + cosf(_mapAngle) * _mapSpeed);
			_image6->SetY(_image6->GetY() + -sinf(_mapAngle) * _mapSpeed);
			tileMoveBox[5].left -= _mapSpeed;
			tileMoveBox[5].right -= _mapSpeed;
		}
		else if (0.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_image6->SetX(856);
			tileMoveBox[5].left = 807;
			tileMoveBox[5].right = 840;
		}
	}
	else
	{
		num6 = 0;
		_image6->SetX(1800);
		tileMoveBox[5].left = WINSIZEX - 32;
		tileMoveBox[5].right = WINSIZEX;
	}
 }
	
TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	if (tilenum == 3 && frameX == 19 && frameY == 1)

		return TR_WATER;
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	for (int i = 0; i < basicTileX; ++i)
	{
		for (int j = 0; j < basicTileY; ++j)
		{
			//if (frameX == i && frameY == j)
			//
			//	return OBJ_WALL;

			if (tilenum == 3 && frameX == 18 && frameY == 1)
			{
				return OBJ_WATER;
			}
			else if (tilenum == 3 && frameX == 18 && frameY == 0)
			{
				return OBJ_SHIRT;
			}
			else if (tilenum == 5 && frameX == 1 && frameY == 0)
			{
				return OBJ_FIRE;
			}
			else
				return OBJ_WALL;
		}
	}
}

void mapTool::mapSize()
{
	//사이즈 줄이기  
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&sizeButton[2], _ptMouse) && TILEX > 1)
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
		else if (PtInRect(&sizeButton[3], _ptMouse) && TILEX < 100)
		{
			for (int i = 0; i < TILEY; ++i)
			{
				tagTile* _tile = new tagTile;
				_tile->selectTile = 0;
				_tile->FrameX = 0;
				_tile->FrameY = 15;
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
		if (PtInRect(&sizeButton[0], _ptMouse) && TILEY > 1)
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
		if (PtInRect(&sizeButton[1], _ptMouse) && TILEY < 100)
		{
			vector<tagTile*> vTile;
			for (int i = 0; i < TILEX; i++)
			{
				tagTile* _tile = new tagTile;
				_tile->selectTile = 0;
				_tile->FrameX = 0;
				_tile->FrameY = 15;
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
