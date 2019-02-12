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

	_blackFade = new blackFadeOut;
	_blackFade->init();

	_iMgr = new ItemManager;
	_iMgr->init();

	dataLode();


	IMAGEMANAGER->addFrameImage("yomi", "image/NPC_yomi.bmp", 275, 112, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UI", "image/UI.bmp", 4096, 768, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UIIndex", "image/UIIndex.bmp", 4096, 768, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("blackRect", GAMESIZEX, GAMESIZEY);


	//변수 초기화
	_placeFrameX = MAIN_ROOM;
	_yomiFrameX = _yomiFrameY = 0;
	_x = 537;
	_y = 339;
	_goalX = _x;
	_goalY = _y;
	_yomiAngle = 0;
	_yomiDistance = 0;
	_yomiSpeed = 14.f;
	_yomiIndex = 4;
	_count = 0;
	_worldTime = 0;

	_isRoomChanging = false;
	_move = true;
	_onceTime = false;
	_isIndexMode = false;
	return S_OK;
}

void ui::release()
{
	SAFE_DELETE(_blackFade);
	SAFE_DELETE(_iMgr);
}

void ui::update()
{
	_blackFade->update();
	_iMgr->update();

	//요미이동 목표점 설정
	movePoint();
	//요미 프레임동작
	yomiFrame();
	//요미 이동
	yomiMove();
	//방이동
	placeChange();


	//아이템 셋팅
	itemSetting();

	//===============지울것================
	//_goal = RectMake(_goalX, _goalY, 10, 10);
	//
	//if (KEYMANAGER->isOnceKeyDown('0'))
	//{
	//	if (_placeFrameX > 2) _placeFrameX = -1;
	//	_placeFrameX++;
	//}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	{
		if (_isIndexMode)
		{
			_isIndexMode = false;
		}
		else
		{
			_isIndexMode = true;
		}
	}


	//====================================
}

void ui::render()
{
	if (!_isIndexMode)
	{
		IMAGEMANAGER->frameRender("UI", getMemDC(), 0, 0, _placeFrameX, 0);
	}
	else
	{
		IMAGEMANAGER->frameRender("UIIndex", getMemDC(), 0, 0, _placeFrameX, 0);
	}
	_iMgr->render();
	IMAGEMANAGER->expandRender("yomi", getMemDC(), _x - 30, _y - 36 * 3, _yomiFrameX, _yomiFrameY, 3.f, 3.f);

	_blackFade->render();




	//char str[100];
	//sprintf_s(str, "_좌표 : %d  %d", _x,_y);
	//TextOut(getMemDC(), 30, 100, str, strlen(str));
	//sprintf_s(str, "골 좌표 : %d  %d", _goalX, _goalY);
	//TextOut(getMemDC(), 30, 120, str, strlen(str));
	//sprintf_s(str, "%d", _placeFrameX);
	//TextOut(getMemDC(), 30, 140, str, strlen(str));

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
	_goalX = _pt[_yomiIndex].x;
	_goalY = _pt[_yomiIndex].y;
	
	//각도와 거리는 계속 갱신
	_yomiAngle = getAngle(_x, _y, _goalX, _goalY);
	_yomiDistance = getDistance(_x, _y, _goalX, _goalY);

	//요미 이동
	if (_move)
	{
		if (_placeFrameX == MAIN_ROOM)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (_yomiIndex % 3 == 1 || _yomiIndex % 3 == 2)
				{
					_yomiIndex -= 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_yomiIndex % 3 == 0 || _yomiIndex % 3 == 1)
				{
					_yomiIndex += 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (_yomiIndex / 3 == 1 || _yomiIndex / 3 == 2)
				{
					_yomiIndex -= 3;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (_yomiIndex / 3 == 0 || _yomiIndex / 3 == 1)
				{
					_yomiIndex += 3;
				}
			}
		}
		else if (_placeFrameX == WEAPON_ROOM)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 5;
				}
				else if (_yomiIndex % 4 == 1 || _yomiIndex % 4 == 2 || _yomiIndex % 4 == 3)
				{
					_yomiIndex -= 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 6;
				}
				else if (_yomiIndex == 2)
				{

				}
				else if (_yomiIndex % 4 == 0 || _yomiIndex % 4 == 1 || _yomiIndex % 4 == 2)
				{
					_yomiIndex += 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (_yomiIndex == 5 || _yomiIndex == 6)
				{
					_yomiIndex = 3;
				}
				else if (_yomiIndex == 3)
				{
					_yomiIndex = 1;
				}
				else if (_yomiIndex == 4)
				{
					_yomiIndex = 0;
				}
				else if (_yomiIndex == 7)
				{
					_yomiIndex = 2;
				}
				else if (_yomiIndex / 4 == 1 || _yomiIndex / 4 == 2 || _yomiIndex / 4 == 3 || _yomiIndex / 4 == 4)
				{
					_yomiIndex -= 4;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 5;
				}
				else if (_yomiIndex == 1)
				{
					_yomiIndex = 3;
				}
				else if (_yomiIndex == 2)
				{
					_yomiIndex = 7;
				}
				else if (_yomiIndex / 4 == 0 || _yomiIndex / 4 == 1 || _yomiIndex / 4 == 2 || _yomiIndex / 4 == 3)
				{
					_yomiIndex += 4;
				}
			}
		}
		else if (_placeFrameX == ACCESSERY_ROOM)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 7;
				}
				else if (_yomiIndex != 0 && _yomiIndex % 9 != 4)
				{
					_yomiIndex -= 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 9;
				}
				else if (_yomiIndex != 2 && _yomiIndex != 35 && _yomiIndex % 9 != 3)
				{
					_yomiIndex += 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 1;
				}
				else if (_yomiIndex == 4 || _yomiIndex == 5 || _yomiIndex == 6)
				{
					_yomiIndex = 0;
				}
				else if (_yomiIndex == 7 || _yomiIndex == 8 || _yomiIndex == 9)
				{
					_yomiIndex = 3;
				}
				else if (_yomiIndex == 10 || _yomiIndex == 11 || _yomiIndex == 12)
				{
					_yomiIndex = 2;
				}
				else if (_yomiIndex == 32)
				{
					_yomiIndex = 24;
				}
				else if (_yomiIndex == 33)
				{
					_yomiIndex = 26;
				}
				else if (_yomiIndex == 34)
				{
					_yomiIndex = 28;
				}
				else if (_yomiIndex == 35)
				{
					_yomiIndex = 30;
				}
				else if (_yomiIndex != 0 && _yomiIndex != 1 && _yomiIndex != 2)
				{
					_yomiIndex -= 9;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 8;
				}
				else if (_yomiIndex == 0)
				{
					_yomiIndex = 4;
				}
				else if (_yomiIndex == 2)
				{
					_yomiIndex = 12;
				}
				else if (_yomiIndex == 1)
				{
					_yomiIndex = 3;
				}
				else if (_yomiIndex == 22 || _yomiIndex == 23)
				{
					_yomiIndex = 31;
				}
				else if (_yomiIndex == 24 || _yomiIndex == 25)
				{
					_yomiIndex = 32;
				}
				else if (_yomiIndex == 26 || _yomiIndex == 27)
				{
					_yomiIndex = 33;
				}
				else if (_yomiIndex == 28 || _yomiIndex == 29)
				{
					_yomiIndex = 34;
				}
				else if (_yomiIndex == 30)
				{
					_yomiIndex = 35;
				}
				else if (_yomiIndex < 31)
				{
					_yomiIndex += 9;
				}
			}
		}
		else if (_placeFrameX == ARMOR_ROOM)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 5;
				}
				else if (_yomiIndex % 4 == 1 || _yomiIndex % 4 == 2 || _yomiIndex % 4 == 3)
				{
					_yomiIndex -= 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 6;
				}
				else if ((_yomiIndex % 4 == 0 || _yomiIndex % 4 == 1 || _yomiIndex % 4 == 2) && _yomiIndex != 2)
				{
					_yomiIndex += 1;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (_yomiIndex == 5 || _yomiIndex == 6)
				{
					_yomiIndex = 3;
				}
				else if (_yomiIndex == 3)
				{
					_yomiIndex = 1;
				}
				else if (_yomiIndex == 4)
				{
					_yomiIndex = 0;
				}
				else if (_yomiIndex == 7)
				{
					_yomiIndex = 2;
				}
				else if (_yomiIndex / 4 == 1 || _yomiIndex / 4 == 2 || _yomiIndex / 4 == 3 || _yomiIndex / 4 == 4)
				{
					_yomiIndex -= 4;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (_yomiIndex == 3)
				{
					_yomiIndex = 5;
				}
				else if (_yomiIndex == 1)
				{
					_yomiIndex = 3;
				}
				else if (_yomiIndex == 2)
				{
					_yomiIndex = 7;
				}
				else if (_yomiIndex / 4 == 0 || _yomiIndex / 4 == 1 || _yomiIndex / 4 == 2 || _yomiIndex / 4 == 3)
				{
					_yomiIndex += 4;
				}
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

void ui::placeChange()
{
	//요미가 각방 앞에 있을때 X를 눌렀을때 불변수 트루로변경
	if (_x == _goalX && _y == _goalY)
	{
		if (_yomiIndex >= 0 && _yomiIndex <= 2)
		{
			if (!_isRoomChanging)
			{
				if (KEYMANAGER->isOnceKeyDown('X'))
				{
					_isRoomChanging = true;
					_worldTime = TIMEMANAGER->getWorldTime();
					_blackFade->setGoal(_x, _y);
					_blackFade->setIsFadeOut(true);
				}
			}
		}
	}

	if (_isRoomChanging)
	{
		_move = false;

		//1.5초후 방이 변경
		if (1.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			if (!_onceTime)
			{
				_onceTime = true;

				//중앙방일때
				if (_placeFrameX == MAIN_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_placeFrameX = WEAPON_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_placeFrameX = ACCESSERY_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_placeFrameX = ARMOR_ROOM;
					}
				}
				//무기방일떄
				else if (_placeFrameX == WEAPON_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_placeFrameX = MAIN_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_placeFrameX = ACCESSERY_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_placeFrameX = ARMOR_ROOM;
					}
				}
				//악세서리방일떄
				else if (_placeFrameX == ACCESSERY_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_placeFrameX = WEAPON_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_placeFrameX = MAIN_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_placeFrameX = ARMOR_ROOM;
					}
				}
				//방어구방일때
				else if (_placeFrameX == ARMOR_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_placeFrameX = WEAPON_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_placeFrameX = ACCESSERY_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_placeFrameX = MAIN_ROOM;
					}
				}
			}
		}

		//3초후 요미이동 가능
		if (3.0f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_move = true;
			_isRoomChanging = false;
			_onceTime = false;
			_worldTime = 0;
		}
	}
}

void ui::dataLode()
{
	//HANDLE file;
	//DWORD lode;
	//
	//file = CreateFile("", GENERIC_WRITE, NULL, NULL,
	//	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//
	//ReadFile(file, "", sizeof(""), &lode, NULL);
	//
	//CloseHandle(file);
}

void ui::itemSetting()
{
}
