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

	//_clockFade = new ClockFadeOut;
	//_clockFade->init();

	_iMgr = new ItemManager;
	_iMgr->init();

	_inventory = new Inventory;
	_inventory->init();

	
	dataLoad();

	//아이템 셋팅
	roomPointSetting();
	itemSetting();

	IMAGEMANAGER->addFrameImage("yomi", "image/NPC_yomi.bmp", 275, 112, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UI", "image/UI.bmp", 4096, 768, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UIIndex", "image/UIIndex.bmp", 4096, 768, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("blackRect", GAMESIZEX, GAMESIZEY);

	//변수 초기화
	_room = ROOMTYPE::MAIN_ROOM;
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
	SAFE_DELETE(_inventory);
	//SAFE_DELETE(_clockFade);
}

void ui::update()
{
	//_clockFade->update();
	_blackFade->update();
	_iMgr->update();
	_inventory->update();

	//요미이동 목표점 설정
	movePoint();
	//요미 프레임동작
	yomiFrame();
	//요미 이동
	yomiMove();
	//방이동
	placeChange();



	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
	{
		_inventory->inventorySave();
		SCENEMANAGER->changeScene("dungeon");
	}

	//===============지울것================
	_goal = RectMake(_goalX, _goalY, 20, 20);
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
		//배경 이미지
		IMAGEMANAGER->frameRender("UI", getMemDC(), 0, 0, (int)_room, 0);
	}
	else
	{
		//배경 인덱스 이미지
		IMAGEMANAGER->frameRender("UIIndex", getMemDC(), 0, 0, (int)_room, 0);
	}
	//아이템
	//_iMgr->render();
	//_inventory->render();
	itemDraw();


	//요미
	IMAGEMANAGER->expandRender("yomi", getMemDC(), _x - 30, _y - 36 * 3, _yomiFrameX, _yomiFrameY, 3.f, 3.f);
	//페이드아웃
	_blackFade->render();
	//_clockFade->render();


	//char str[100];
	//sprintf_s(str, "%d  %d", _inventory->getWeaponCount(),_inventory->getAccessoryCount());
	//TextOut(getMemDC(), 30, 100, str, strlen(str));
	//sprintf_s(str, "골 좌표 : %d  %d", _goalX, _goalY);
	//TextOut(getMemDC(), 30, 120, str, strlen(str));
	//sprintf_s(str, "%d", _placeFrameX);
	//TextOut(getMemDC(), 30, 140, str, strlen(str));

	Rectangle(getMemDC(), _goal);
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
	_goalX = _uiPoint[_yomiIndex].x;
	_goalY = _uiPoint[_yomiIndex].y;
	
	//각도와 거리는 계속 갱신
	_yomiAngle = getAngle(_x, _y, _goalX, _goalY);
	_yomiDistance = getDistance(_x, _y, _goalX, _goalY);

	//요미 이동
	if (_move)
	{
		if (_room == ROOMTYPE::MAIN_ROOM)
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
		else if (_room == ROOMTYPE::WEAPON_ROOM)
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
		else if (_room == ROOMTYPE::ACCESSERY_ROOM)
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
		else if (_room == ROOMTYPE::ARMOR_ROOM)
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
	if (_room == ROOMTYPE::MAIN_ROOM)
	{
		_uiPoint[0].x = 280;
		_uiPoint[1].x = 537;
		_uiPoint[2].x = 793;
		_uiPoint[3].x = 246;
		_uiPoint[4].x = 537;
		_uiPoint[5].x = 824;
		_uiPoint[6].x = 346;
		_uiPoint[7].x = 538;
		_uiPoint[8].x = 729;

		_uiPoint[0].y = 175;
		_uiPoint[1].y = 175;
		_uiPoint[2].y = 175;
		_uiPoint[3].y = 341;
		_uiPoint[4].y = 339;
		_uiPoint[5].y = 340;
		_uiPoint[6].y = 454;
		_uiPoint[7].y = 431;
		_uiPoint[8].y = 468;
	}
	else if (_room == ROOMTYPE::WEAPON_ROOM)
	{
		_uiPoint[0].x = 280;
		_uiPoint[1].x = 537;
		_uiPoint[2].x = 793;
		_uiPoint[3].x = 536;
		_uiPoint[4].x = 271;
		_uiPoint[5].x = 399;
		_uiPoint[6].x = 656;
		_uiPoint[7].x = 784;
		_uiPoint[8].x = 208;
		_uiPoint[9].x = 464;
		_uiPoint[10].x = 592;
		_uiPoint[11].x = 848;
		_uiPoint[12].x = 208;
		_uiPoint[13].x = 464;
		_uiPoint[14].x = 592;
		_uiPoint[15].x = 848;
		_uiPoint[16].x = 271;
		_uiPoint[17].x = 399;
		_uiPoint[18].x = 656;
		_uiPoint[19].x = 784;
		
		_uiPoint[0].y = 175;
		_uiPoint[1].y = 175;
		_uiPoint[2].y = 175;
		_uiPoint[3].y = 288;
		_uiPoint[4].y = 348;
		_uiPoint[5].y = 348;
		_uiPoint[6].y = 348;
		_uiPoint[7].y = 348;
		_uiPoint[8].y = 400;
		_uiPoint[9].y = 400;
		_uiPoint[10].y = 400;
		_uiPoint[11].y = 400;
		_uiPoint[12].y = 514;
		_uiPoint[13].y = 514;
		_uiPoint[14].y = 514;
		_uiPoint[15].y = 514;
		_uiPoint[16].y = 570;
		_uiPoint[17].y = 570;
		_uiPoint[18].y = 570;
		_uiPoint[19].y = 570;
	}
	else if (_room == ROOMTYPE::ACCESSERY_ROOM)
	{
		_uiPoint[0].x = 280;
		_uiPoint[1].x = 537;
		_uiPoint[2].x = 793;
		_uiPoint[3].x = 536;
		_uiPoint[4].x = 271;
		_uiPoint[5].x = 337;
		_uiPoint[6].x = 401;
		_uiPoint[7].x = 464;
		_uiPoint[8].x = 528;
		_uiPoint[9].x = 591;
		_uiPoint[10].x = 656;
		_uiPoint[11].x = 721;
		_uiPoint[12].x = 784;
		_uiPoint[13].x = 271;
		_uiPoint[14].x = 337;
		_uiPoint[15].x = 401;
		_uiPoint[16].x = 464;
		_uiPoint[17].x = 528;
		_uiPoint[18].x = 591;
		_uiPoint[19].x = 656;
		_uiPoint[20].x = 721;
		_uiPoint[21].x = 784;
		_uiPoint[22].x = 271;
		_uiPoint[23].x = 337;
		_uiPoint[24].x = 401;
		_uiPoint[25].x = 464;
		_uiPoint[26].x = 528;
		_uiPoint[27].x = 591;
		_uiPoint[28].x = 656;
		_uiPoint[29].x = 721;
		_uiPoint[30].x = 784;
		_uiPoint[31].x = 271;
		_uiPoint[32].x = 401;
		_uiPoint[33].x = 528;
		_uiPoint[34].x = 656;
		_uiPoint[35].x = 784;

		_uiPoint[0].y = 175;
		_uiPoint[1].y = 175;
		_uiPoint[2].y = 175;
		_uiPoint[3].y = 288;
		_uiPoint[4].y = 346;
		_uiPoint[5].y = 346;
		_uiPoint[6].y = 346;
		_uiPoint[7].y = 346;
		_uiPoint[8].y = 346;
		_uiPoint[9].y = 346;
		_uiPoint[10].y = 346;
		_uiPoint[11].y = 346;
		_uiPoint[12].y = 346;
		_uiPoint[13].y = 401;
		_uiPoint[14].y = 401;
		_uiPoint[15].y = 401;
		_uiPoint[16].y = 401;
		_uiPoint[17].y = 401;
		_uiPoint[18].y = 401;
		_uiPoint[19].y = 401;
		_uiPoint[20].y = 401;
		_uiPoint[21].y = 401;
		_uiPoint[22].y = 458;
		_uiPoint[23].y = 458;
		_uiPoint[24].y = 458;
		_uiPoint[25].y = 458;
		_uiPoint[26].y = 458;
		_uiPoint[27].y = 458;
		_uiPoint[28].y = 458;
		_uiPoint[29].y = 458;
		_uiPoint[30].y = 458;
		_uiPoint[31].y = 567;
		_uiPoint[32].y = 567;
		_uiPoint[33].y = 567;
		_uiPoint[34].y = 567;
		_uiPoint[35].y = 567;

	}
	else if (_room == ROOMTYPE::ARMOR_ROOM)
	{
	_uiPoint[0].x = 280;
	_uiPoint[1].x = 537;
	_uiPoint[2].x = 793;
	_uiPoint[3].x = 536;
	_uiPoint[4].x = 271;
	_uiPoint[5].x = 464;
	_uiPoint[6].x = 594;
	_uiPoint[7].x = 784;
	_uiPoint[8].x = 208;
	_uiPoint[9].x = 402;
	_uiPoint[10].x = 657;
	_uiPoint[11].x = 848;
	_uiPoint[12].x = 208;
	_uiPoint[13].x = 402;
	_uiPoint[14].x = 657;
	_uiPoint[15].x = 848;
	_uiPoint[16].x = 271;
	_uiPoint[17].x = 464;
	_uiPoint[18].x = 594;
	_uiPoint[19].x = 784;

	_uiPoint[0].y = 175;
	_uiPoint[1].y = 175;
	_uiPoint[2].y = 175;
	_uiPoint[3].y = 288;
	_uiPoint[4].y = 348;
	_uiPoint[5].y = 348;
	_uiPoint[6].y = 348;
	_uiPoint[7].y = 348;
	_uiPoint[8].y = 400;
	_uiPoint[9].y = 400;
	_uiPoint[10].y = 400;
	_uiPoint[11].y = 400;
	_uiPoint[12].y = 514;
	_uiPoint[13].y = 514;
	_uiPoint[14].y = 514;
	_uiPoint[15].y = 514;
	_uiPoint[16].y = 570;
	_uiPoint[17].y = 570;
	_uiPoint[18].y = 570;
	_uiPoint[19].y = 570;
	}
}

void ui::roomPointSetting()
{
	//무기
	{
		_weaponPoint[0].x = 271;
		_weaponPoint[1].x = 399;
		_weaponPoint[2].x = 656;
		_weaponPoint[3].x = 784;
		_weaponPoint[4].x = 208;
		_weaponPoint[5].x = 464;
		_weaponPoint[6].x = 592;
		_weaponPoint[7].x = 848;
		_weaponPoint[8].x = 208;
		_weaponPoint[9].x = 464;
		_weaponPoint[10].x = 592;
		_weaponPoint[11].x = 848;
		_weaponPoint[12].x = 271;
		_weaponPoint[13].x = 399;
		_weaponPoint[14].x = 656;
		_weaponPoint[15].x = 784;

		_weaponPoint[0].y = 348;
		_weaponPoint[1].y = 348;
		_weaponPoint[2].y = 348;
		_weaponPoint[3].y = 348;
		_weaponPoint[4].y = 400;
		_weaponPoint[5].y = 400;
		_weaponPoint[6].y = 400;
		_weaponPoint[7].y = 400;
		_weaponPoint[8].y = 514;
		_weaponPoint[9].y = 514;
		_weaponPoint[10].y = 514;
		_weaponPoint[11].y = 514;
		_weaponPoint[12].y = 570;
		_weaponPoint[13].y = 570;
		_weaponPoint[14].y = 570;
		_weaponPoint[15].y = 570;
	}

	//방어구
	{
		_armorPoint[0].x = 271;
		_armorPoint[1].x = 464;
		_armorPoint[2].x = 594;
		_armorPoint[3].x = 784;
		_armorPoint[4].x = 208;
		_armorPoint[5].x = 399;
		_armorPoint[6].x = 654;
		_armorPoint[7].x = 848;
		_armorPoint[8].x = 208;
		_armorPoint[9].x = 401;
		_armorPoint[10].x = 656;
		_armorPoint[11].x = 848;
		_armorPoint[12].x = 271;
		_armorPoint[13].x = 464;
		_armorPoint[14].x = 594;
		_armorPoint[15].x = 784;

		_armorPoint[0].y = 348;
		_armorPoint[1].y = 348;
		_armorPoint[2].y = 348;
		_armorPoint[3].y = 348;
		_armorPoint[4].y = 405;
		_armorPoint[5].y = 400;
		_armorPoint[6].y = 400;
		_armorPoint[7].y = 405;
		_armorPoint[8].y = 514;
		_armorPoint[9].y = 506;
		_armorPoint[10].y = 506;
		_armorPoint[11].y = 514;
		_armorPoint[12].y = 570;
		_armorPoint[13].y = 570;
		_armorPoint[14].y = 570;
		_armorPoint[15].y = 570;
	}

	//악세서리
	{
		_accessoryPoint[0].x = 271;
		_accessoryPoint[1].x = 337;
		_accessoryPoint[2].x = 401;
		_accessoryPoint[3].x = 464;
		_accessoryPoint[4].x = 528;
		_accessoryPoint[5].x = 591;
		_accessoryPoint[6].x = 656;
		_accessoryPoint[7].x = 721;
		_accessoryPoint[8].x = 784;
		_accessoryPoint[9].x = 271;
		_accessoryPoint[10].x = 337;
		_accessoryPoint[11].x = 401;
		_accessoryPoint[12].x = 464;
		_accessoryPoint[13].x = 528;
		_accessoryPoint[14].x = 591;
		_accessoryPoint[15].x = 656;
		_accessoryPoint[16].x = 721;
		_accessoryPoint[17].x = 784;
		_accessoryPoint[18].x = 271;
		_accessoryPoint[19].x = 337;
		_accessoryPoint[20].x = 401;
		_accessoryPoint[21].x = 464;
		_accessoryPoint[22].x = 528;
		_accessoryPoint[23].x = 591;
		_accessoryPoint[24].x = 656;
		_accessoryPoint[25].x = 721;
		_accessoryPoint[26].x = 784;
		_accessoryPoint[27].x = 271;
		_accessoryPoint[28].x = 401;
		_accessoryPoint[29].x = 528;
		_accessoryPoint[30].x = 656;
		_accessoryPoint[31].x = 784;

		_accessoryPoint[0].y = 346;
		_accessoryPoint[1].y = 346;
		_accessoryPoint[2].y = 346;
		_accessoryPoint[3].y = 346;
		_accessoryPoint[4].y = 346;
		_accessoryPoint[5].y = 346;
		_accessoryPoint[6].y = 346;
		_accessoryPoint[7].y = 346;
		_accessoryPoint[8].y = 346;
		_accessoryPoint[9].y = 401;
		_accessoryPoint[10].y = 401;
		_accessoryPoint[11].y = 401;
		_accessoryPoint[12].y = 401;
		_accessoryPoint[13].y = 401;
		_accessoryPoint[14].y = 401;
		_accessoryPoint[15].y = 401;
		_accessoryPoint[16].y = 401;
		_accessoryPoint[17].y = 401;
		_accessoryPoint[18].y = 458;
		_accessoryPoint[19].y = 458;
		_accessoryPoint[20].y = 458;
		_accessoryPoint[21].y = 458;
		_accessoryPoint[22].y = 458;
		_accessoryPoint[23].y = 458;
		_accessoryPoint[24].y = 458;
		_accessoryPoint[25].y = 458;
		_accessoryPoint[26].y = 458;
		_accessoryPoint[27].y = 567;
		_accessoryPoint[28].y = 567;
		_accessoryPoint[29].y = 567;
		_accessoryPoint[30].y = 567;
		_accessoryPoint[31].y = 567;
	}
}

void ui::placeChange()
{
	//요미가 각방 앞에 있을때 X를 눌렀을때 불변수 트루로변경
	if (_x == _goalX && _y == _goalY && _y == 175)
	{
		if (_yomiIndex >= 0 && _yomiIndex <= 2 )
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
				if (_room == ROOMTYPE::MAIN_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_room = ROOMTYPE::WEAPON_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_room = ROOMTYPE::ACCESSERY_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_room = ROOMTYPE::ARMOR_ROOM;
					}
				}
				//무기방일떄
				else if (_room == ROOMTYPE::WEAPON_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_room = ROOMTYPE::MAIN_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_room = ROOMTYPE::ACCESSERY_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_room = ROOMTYPE::ARMOR_ROOM;
					}
				}
				//악세서리방일떄
				else if (_room == ROOMTYPE::ACCESSERY_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_room = ROOMTYPE::WEAPON_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_room = ROOMTYPE::MAIN_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_room = ROOMTYPE::ARMOR_ROOM;
					}
				}
				//방어구방일때
				else if (_room == ROOMTYPE::ARMOR_ROOM)
				{
					if (_yomiIndex == 0)
					{
						_room = ROOMTYPE::WEAPON_ROOM;
					}
					else if (_yomiIndex == 1)
					{
						_room = ROOMTYPE::ACCESSERY_ROOM;
					}
					else if (_yomiIndex == 2)
					{
						_room = ROOMTYPE::MAIN_ROOM;
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

void ui::dataLoad()
{
	_inventory->inventoryLoad();
	
}

void ui::itemSetting()
{
	//무기
	for (int i = 0; i < WEAPON_MAX_ARR; ++i)
	{
		if (_inventory->getWeaponInv(i) != WEAPONTYPE::NONE)
		{
			_iMgr->dropWeapon(_weaponPoint[i].x - 10, _weaponPoint[i].y - 25, _inventory->getWeaponInv(i));
		}
	}

	//악세서리
	for (int i = 0; i < ACCESSORY_MAX_ARR; ++i)
	{
		if (_inventory->getAccessoryInv(i) != ACCESSORYTYPE::NONE)
		{
			_iMgr->dropAccessory(_accessoryPoint[i].x - 17, _accessoryPoint[i].y - 25, _inventory->getAccessoryInv(i));
		}
	}
	//포션
	for (int i = 0; i < POTION_MAX_ARR; ++i)
	{
		if (_inventory->getPotionInv(i) != POTIONTYPE::NONE)
		{
			_iMgr->dropPotion(_accessoryPoint[i].x - 16, _accessoryPoint[i].y - 28, _inventory->getPotionInv(i));
		}
	}

	//방어구
	for (int i = 0; i < ARMOR_MAX_ARR; ++i)
	{
		if (_inventory->getArmorInv(i) != ARMORTYPE::NONE)
		{
			_iMgr->dropArmor(_armorPoint[i].x - 16, _armorPoint[i].y - 25, _inventory->getArmorInv(i));
		}
	}
}

void ui::itemDraw()
{
	switch (_room)
	{
	case ui::ROOMTYPE::MAIN_ROOM:
		break;
	case ui::ROOMTYPE::WEAPON_ROOM:
		_iMgr->weaponDraw();

		break;
	case ui::ROOMTYPE::ACCESSERY_ROOM:
		_iMgr->accessoryDraw();
		_iMgr->potionDraw();
		break;
	case ui::ROOMTYPE::ARMOR_ROOM:
		_iMgr->armorDraw();

		break;
	default:
		break;
	}
}
