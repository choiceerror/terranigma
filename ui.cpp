#include "stdafx.h"
#include "ui.h"


ui::ui()
{
}


ui::~ui()
{
}

HRESULT ui::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY,GAMESIZEX,GAMESIZEY);

	IMAGEMANAGER->addFrameImage("yomi", "image/NPC_yomi.bmp", 275, 112, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UI", "image/UI.bmp", 4096, 768, 4, 1, true, MAGENTA);

	_placeFrameX = 0;

	_x = 537;
	_y = 339;
	_goalX = _x;
	_goalY = _y;
	_yomiAngle = 0;
	_yomiDistance = 0;
	_yomiSpeed = 11.f;

	_yomiPlace = 4;

	return S_OK;
}

void ui::release()
{
}

void ui::update()
{
	//요미이동 목표점 설정
	movePoint();
	//요미 프레임동작
	yomiFrame();
	//요미 이동
	yomiMove();





	//===============지울것================
	_goal = RectMake(_goalX, _goalY, 10, 10);

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		if (_placeFrameX > 2) _placeFrameX = -1;
		_placeFrameX++;
	}



	//====================================
}

void ui::render()
{
	IMAGEMANAGER->frameRender("UI", getMemDC(), 0, 0, _placeFrameX, 0);
	IMAGEMANAGER->expandRender("yomi", getMemDC(), _x - 30, _y - 36 * 3, _yomiFrameX, _yomiFrameY, 3.f, 3.f);
	

	char str[100];
	sprintf_s(str, "_좌표 : %d  %d", _x,_y);
	TextOut(getMemDC(), 30, 100, str, strlen(str));
	sprintf_s(str, "골 좌표 : %d  %d", _goalX, _goalY);
	TextOut(getMemDC(), 30, 120, str, strlen(str));

	//Rectangle(getMemDC(), _goal);
}

//윈도우 사이즈조정
void ui::setWindowsSize(int x, int y, int width, int height)
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

void ui::yomiFrame()
{
	_count++;

	if (_count % 5 == 0)
	{
		if (_yomiFrameX > 6) _yomiFrameX = -1;
		_yomiFrameX++;

		_count = 0;
	}
}

void ui::yomiMove()
{
	//요미가 목표점과 거리 이상일때 각도에 따라 이동
	if (_yomiDistance > _yomiSpeed)
	{
		_x += cosf(_yomiAngle) * _yomiSpeed;
		_y += -sinf(_yomiAngle) * _yomiSpeed;
	}
	else 
	{
		_x = _goalX;
		_y = _goalY;
	}

	//목표점은 인덱스(int _yomiPlace)로 바뀜
	_goalX = _pt[_yomiPlace].x;
	_goalY = _pt[_yomiPlace].y;
	
	//각도와 거리는 계속 갱신
	_yomiAngle = getAngle(_x, _y, _goalX, _goalY);
	_yomiDistance = getDistance(_x, _y, _goalX, _goalY);

	//요미 이동
	if (_placeFrameX == MAIN_ROOM)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_yomiPlace % 3 == 1 || _yomiPlace % 3 == 2)
			{
				_yomiPlace -= 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_yomiPlace % 3 == 0 || _yomiPlace % 3 == 1)
			{
				_yomiPlace += 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_yomiPlace / 3 == 1 || _yomiPlace / 3 == 2)
			{
				_yomiPlace -= 3;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_yomiPlace / 3 == 0 || _yomiPlace / 3 == 1)
			{
				_yomiPlace += 3;
			}
		}
	}
	else if (_placeFrameX == WEAPON_ROOM)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 5;
			}
			else if (_yomiPlace % 4 == 1 || _yomiPlace % 4 == 2 || _yomiPlace % 4 == 3)
			{
				_yomiPlace -= 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 6;
			}
			else if (_yomiPlace % 4 == 0 || _yomiPlace % 4 == 1 || _yomiPlace % 4 == 2)
			{
				_yomiPlace += 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_yomiPlace == 5 || _yomiPlace == 6)
			{
				_yomiPlace = 3;
			}
			else if (_yomiPlace == 3)
			{
				_yomiPlace = 1;
			}
			else if (_yomiPlace == 4)
			{
				_yomiPlace = 0;
			}
			else if (_yomiPlace == 7)
			{
				_yomiPlace = 2;
			}
			else if (_yomiPlace / 4 == 1 || _yomiPlace / 4 == 2 || _yomiPlace / 4 == 3 || _yomiPlace / 4 == 4)
			{
				_yomiPlace -= 4;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 5;
			}
			else if (_yomiPlace == 1)
			{
				_yomiPlace = 3;
			}
			else if (_yomiPlace == 2)
			{
				_yomiPlace = 7;
			}
			else if (_yomiPlace / 4 == 0 || _yomiPlace / 4 == 1 || _yomiPlace / 4 == 2 || _yomiPlace / 4 == 3)
			{
				_yomiPlace += 4;
			}	
		}
	}
	else if (_placeFrameX == ACCESSERY_ROOM)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 7;
			}
			else if (_yomiPlace != 0 && _yomiPlace % 9 != 4)
			{
				_yomiPlace -= 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 9;
			}
			else if (_yomiPlace != 2 && _yomiPlace != 35 &&_yomiPlace % 9 != 3)
			{
				_yomiPlace += 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 1;
			}
			else if (_yomiPlace == 4 || _yomiPlace == 5 || _yomiPlace == 6)
			{
				_yomiPlace = 0;
			}
			else if (_yomiPlace == 7 || _yomiPlace == 8 || _yomiPlace == 9)
			{
				_yomiPlace = 3;
			}
			else if (_yomiPlace == 10 || _yomiPlace == 11 || _yomiPlace == 12)
			{
				_yomiPlace = 2;
			}
			else if (_yomiPlace == 32)
			{
				_yomiPlace = 24;
			}
			else if (_yomiPlace == 33)
			{
				_yomiPlace = 26;
			}
			else if (_yomiPlace == 34)
			{
				_yomiPlace = 28;
			}
			else if (_yomiPlace == 35)
			{
				_yomiPlace = 30;
			}
			else if (_yomiPlace != 0 && _yomiPlace != 1 && _yomiPlace != 2)
			{
				_yomiPlace -= 9;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 8;
			}
			else if (_yomiPlace == 0)
			{
				_yomiPlace = 4;
			}
			else if (_yomiPlace == 2)
			{
				_yomiPlace = 12;
			}
			else if (_yomiPlace == 1)
			{
				_yomiPlace = 3;
			}
			else if (_yomiPlace == 22 || _yomiPlace == 23)
			{
				_yomiPlace = 31;
			}
			else if (_yomiPlace == 24 || _yomiPlace == 25)
			{
				_yomiPlace = 32;
			}
			else if (_yomiPlace == 26 || _yomiPlace == 27)
			{
				_yomiPlace = 33;
			}
			else if (_yomiPlace == 28 || _yomiPlace == 29)
			{
				_yomiPlace = 34;
			}
			else if (_yomiPlace == 30)
			{
				_yomiPlace = 35;
			}
			else if (_yomiPlace < 31 )
			{
				_yomiPlace += 9;
			}
		}
	}
	else if (_placeFrameX == ARMOR_ROOM)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 5;
			}
			else if (_yomiPlace % 4 == 1 || _yomiPlace % 4 == 2 || _yomiPlace % 4 == 3)
			{
				_yomiPlace -= 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 6;
			}
			else if (_yomiPlace % 4 == 0 || _yomiPlace % 4 == 1 || _yomiPlace % 4 == 2)
			{
				_yomiPlace += 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_yomiPlace == 5 || _yomiPlace == 6)
			{
				_yomiPlace = 3;
			}
			else if (_yomiPlace == 3)
			{
				_yomiPlace = 1;
			}
			else if (_yomiPlace == 4)
			{
				_yomiPlace = 0;
			}
			else if (_yomiPlace == 7)
			{
				_yomiPlace = 2;
			}
			else if (_yomiPlace / 4 == 1 || _yomiPlace / 4 == 2 || _yomiPlace / 4 == 3 || _yomiPlace / 4 == 4)
			{
				_yomiPlace -= 4;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_yomiPlace == 3)
			{
				_yomiPlace = 5;
			}
			else if (_yomiPlace == 1)
			{
				_yomiPlace = 3;
			}
			else if (_yomiPlace == 2)
			{
				_yomiPlace = 7;
			}
			else if (_yomiPlace / 4 == 0 || _yomiPlace / 4 == 1 || _yomiPlace / 4 == 2 || _yomiPlace / 4 == 3)
			{
				_yomiPlace += 4;
			}
		}
	}
}

void ui::movePoint()
{
	//방에 따라 점위치 설정
	if (_placeFrameX == MAIN_ROOM)
	{
		_pt[0].x = 280;
		_pt[1].x = 537;
		_pt[2].x = 793;
		_pt[3].x = 246;
		_pt[4].x = 537;
		_pt[5].x = 824;
		_pt[6].x = 346;
		_pt[7].x = 538;
		_pt[8].x = 729;

		_pt[0].y = 175;
		_pt[1].y = 175;
		_pt[2].y = 175;
		_pt[3].y = 341;
		_pt[4].y = 339;
		_pt[5].y = 340;
		_pt[6].y = 454;
		_pt[7].y = 431;
		_pt[8].y = 468;
	}
	else if (_placeFrameX == WEAPON_ROOM)
	{
		_pt[0].x = 280;
		_pt[1].x = 537;
		_pt[2].x = 793;
		_pt[3].x = 536;
		_pt[4].x = 271;
		_pt[5].x = 399;
		_pt[6].x = 656;
		_pt[7].x = 784;
		_pt[8].x = 208;
		_pt[9].x = 464;
		_pt[10].x = 592;
		_pt[11].x = 848;
		_pt[12].x = 208;
		_pt[13].x = 464;
		_pt[14].x = 592;
		_pt[15].x = 848;
		_pt[16].x = 271;
		_pt[17].x = 399;
		_pt[18].x = 656;
		_pt[19].x = 784;
		
		_pt[0].y = 175;
		_pt[1].y = 175;
		_pt[2].y = 175;
		_pt[3].y = 288;
		_pt[4].y = 348;
		_pt[5].y = 348;
		_pt[6].y = 348;
		_pt[7].y = 348;
		_pt[8].y = 400;
		_pt[9].y = 400;
		_pt[10].y = 400;
		_pt[11].y = 400;
		_pt[12].y = 514;
		_pt[13].y = 514;
		_pt[14].y = 514;
		_pt[15].y = 514;
		_pt[16].y = 570;
		_pt[17].y = 570;
		_pt[18].y = 570;
		_pt[19].y = 570;
	}
	else if (_placeFrameX == ACCESSERY_ROOM)
	{
		_pt[0].x = 280;
		_pt[1].x = 537;
		_pt[2].x = 793;
		_pt[3].x = 536;
		_pt[4].x = 271;
		_pt[5].x = 337;
		_pt[6].x = 401;
		_pt[7].x = 464;
		_pt[8].x = 528;
		_pt[9].x = 591;
		_pt[10].x = 656;
		_pt[11].x = 721;
		_pt[12].x = 784;
		_pt[13].x = 271;
		_pt[14].x = 337;
		_pt[15].x = 401;
		_pt[16].x = 464;
		_pt[17].x = 528;
		_pt[18].x = 591;
		_pt[19].x = 656;
		_pt[20].x = 721;
		_pt[21].x = 784;
		_pt[22].x = 271;
		_pt[23].x = 337;
		_pt[24].x = 401;
		_pt[25].x = 464;
		_pt[26].x = 528;
		_pt[27].x = 591;
		_pt[28].x = 656;
		_pt[29].x = 721;
		_pt[30].x = 784;
		_pt[31].x = 271;
		_pt[32].x = 401;
		_pt[33].x = 528;
		_pt[34].x = 656;
		_pt[35].x = 784;

		_pt[0].y = 175;
		_pt[1].y = 175;
		_pt[2].y = 175;
		_pt[3].y = 288;
		_pt[4].y = 346;
		_pt[5].y = 346;
		_pt[6].y = 346;
		_pt[7].y = 346;
		_pt[8].y = 346;
		_pt[9].y = 346;
		_pt[10].y = 346;
		_pt[11].y = 346;
		_pt[12].y = 346;
		_pt[13].y = 401;
		_pt[14].y = 401;
		_pt[15].y = 401;
		_pt[16].y = 401;
		_pt[17].y = 401;
		_pt[18].y = 401;
		_pt[19].y = 401;
		_pt[20].y = 401;
		_pt[21].y = 401;
		_pt[22].y = 458;
		_pt[23].y = 458;
		_pt[24].y = 458;
		_pt[25].y = 458;
		_pt[26].y = 458;
		_pt[27].y = 458;
		_pt[28].y = 458;
		_pt[29].y = 458;
		_pt[30].y = 458;
		_pt[31].y = 567;
		_pt[32].y = 567;
		_pt[33].y = 567;
		_pt[34].y = 567;
		_pt[35].y = 567;

	}
	else if (_placeFrameX == ARMOR_ROOM)
	{
	_pt[0].x = 280;
	_pt[1].x = 537;
	_pt[2].x = 793;
	_pt[3].x = 536;
	_pt[4].x = 271;
	_pt[5].x = 464;
	_pt[6].x = 594;
	_pt[7].x = 784;
	_pt[8].x = 208;
	_pt[9].x = 402;
	_pt[10].x = 657;
	_pt[11].x = 848;
	_pt[12].x = 208;
	_pt[13].x = 402;
	_pt[14].x = 657;
	_pt[15].x = 848;
	_pt[16].x = 271;
	_pt[17].x = 464;
	_pt[18].x = 594;
	_pt[19].x = 784;

	_pt[0].y = 175;
	_pt[1].y = 175;
	_pt[2].y = 175;
	_pt[3].y = 288;
	_pt[4].y = 348;
	_pt[5].y = 348;
	_pt[6].y = 348;
	_pt[7].y = 348;
	_pt[8].y = 400;
	_pt[9].y = 400;
	_pt[10].y = 400;
	_pt[11].y = 400;
	_pt[12].y = 514;
	_pt[13].y = 514;
	_pt[14].y = 514;
	_pt[15].y = 514;
	_pt[16].y = 570;
	_pt[17].y = 570;
	_pt[18].y = 570;
	_pt[19].y = 570;
	}
}
