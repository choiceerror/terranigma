#include "stdafx.h"
#include "blackFadeOut.h"


blackFadeOut::blackFadeOut()
{
}


blackFadeOut::~blackFadeOut()
{
}

HRESULT blackFadeOut::init()
{
	IMAGEMANAGER->addImage("blackBox", GAMESIZEX, GAMESIZEY);

	HBRUSH brush = CreateSolidBrush(BLACK);
	HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("blackBox")->getMemDC(), brush);
	_blackBox = RectMake(0, 0, GAMESIZEX, GAMESIZEY);
	Rectangle(IMAGEMANAGER->findImage("blackBox")->getMemDC(), _blackBox);
	SelectObject(IMAGEMANAGER->findImage("blackBox")->getMemDC(), oldBrush);
	DeleteObject(brush);

	_isfadeOut = false;

	_angle = 0.f;

	_centerX = GAMESIZEX / 2.f;
	_centerY = GAMESIZEY / 2.f;

	_goal.x = 0;
	_goal.y = 0;

	_diagonalLength = sqrtf((512.f)*(512) + (384.f)*(384));
	_diagonalMaxLength = _diagonalLength;

	_worldTime = 0.f;
	_once = false;

	//_isClockFadeOut = false;
	//_onceTime = false;
	//_clockWorldTime = 0;

	return S_OK;
}

void blackFadeOut::release()
{
}

void blackFadeOut::update()
{
	if (_isfadeOut)
	{
		pointSetting();
		diagonalLengthSize();
		linearInterPolation();
	}
	else
	{
		_angle = 0;
		_pt[0] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,0) + _angle) * _diagonalLength ,
				_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,0) + _angle) * _diagonalLength };
		_pt[1] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,0) + _angle) * _diagonalLength,
					_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,0) + _angle) * _diagonalLength };
		_pt[2] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,768) + _angle) * _diagonalLength ,
					_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,768) + _angle) * _diagonalLength };
		_pt[3] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,768) + _angle) * _diagonalLength ,
					_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,768) + _angle) * _diagonalLength };
		_diagonalLength = sqrtf((512.f)*(512) + (384.f)*(384));
		_worldTime = 0.f;
		_once = false;
		_centerX = GAMESIZEX / 2.f;
		_centerY = GAMESIZEY / 2.f;
		_goal.x = GAMESIZEX / 2.f;
		_goal.y = GAMESIZEY / 2.f;
	}
	POINT pt[] = { {_pt[0].x,_pt[0].y},{_pt[1].x,_pt[1].y} ,{_pt[2].x,_pt[2].y} ,{_pt[3].x,_pt[3].y} };
	createColorObject("blackBox", pt, MAGENTA);


	
	//_angleSpeed = 90 * (TIMEMANAGER->getElapsedTime() / 0.75f);
	//
	//if (_isClockFadeOut)
	//{
	//	if (!_onceTime)
	//	{
	//		_clockWorldTime = TIMEMANAGER->getWorldTime();
	//	}
	//
	//	if (0.75f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
	//	{
	//		_clockAngle[0] -= (PI / 180) * _angleSpeed;
	//	}
	//		
	//	if (0.75f + _clockWorldTime < TIMEMANAGER->getWorldTime() )
	//	{
	//		_clockAngle[1] -= (PI / 180) * _angleSpeed;
	//
	//	}
	//
	//	if (1.5f + _clockWorldTime < TIMEMANAGER->getWorldTime() )
	//	{
	//		_clockAngle[2] -= (PI / 180) * _angleSpeed;
	//	}
	//
	//	if (2.25f + _clockWorldTime < TIMEMANAGER->getWorldTime() )
	//	{
	//		_clockAngle[3] -= (PI / 180) * _angleSpeed;
	//	}
	//
	//	if (3.f + _clockWorldTime < TIMEMANAGER->getWorldTime())
	//	{
	//		_isClockFadeOut = false;
	//	}
	//
	//	_clockPt[2].x = GAMESIZEX / 2 + cosf(_clockAngle[0]) * 1400;
	//	_clockPt[2].y = GAMESIZEY / 2 + -sinf(_clockAngle[0]) * 1400;
	//
	//	_clockPt[5].x = GAMESIZEX / 2 + cosf(_clockAngle[1]) * 1400;
	//	_clockPt[5].y = GAMESIZEY / 2 + -sinf(_clockAngle[1]) * 1400;
	//
	//	_clockPt[8].x = GAMESIZEX / 2 + cosf(_clockAngle[2]) * 1400;
	//	_clockPt[8].y = GAMESIZEY / 2 + -sinf(_clockAngle[2]) * 1400;
	//
	//	_clockPt[11].x = GAMESIZEX / 2 + cosf(_clockAngle[3]) * 1400;
	//	_clockPt[11].y = GAMESIZEY / 2 + -sinf(_clockAngle[3]) * 1400;
	//
	//
	//	POINT _pt1[] = { _clockPt[0],_clockPt[1],_clockPt[2] };
	//	POINT _pt2[] = { _clockPt[3],_clockPt[4],_clockPt[5] };
	//	POINT _pt3[] = { _clockPt[6],_clockPt[7],_clockPt[8] };
	//	POINT _pt4[] = { _clockPt[9],_clockPt[10],_clockPt[11] };
	//
	//	createColorObject("blackBox", _pt1, MAGENTA);
	//	createColorObject("blackBox", _pt2, MAGENTA);
	//	createColorObject("blackBox", _pt3, MAGENTA);
	//	createColorObject("blackBox", _pt4, MAGENTA);
	//
	//
	//	_onceTime = true;
	//}
	//else 
	//{
	//
	//	_clockAngle[0] = (PI / 180) * 90;
	//	_clockAngle[1] = (PI / 180) * 360;
	//	_clockAngle[2] = (PI / 180) * 270;
	//	_clockAngle[3] = (PI / 180) * 180;
	//
	//	for (int i = 0; i < 12; i += 3)
	//	{
	//		_clockPt[i].x = GAMESIZEX / 2;
	//		_clockPt[i].y = GAMESIZEY / 2;
	//	}
	//	
	//	_clockPt[1].x = GAMESIZEX / 2 + cosf(_clockAngle[0]) * 1400;
	//	_clockPt[1].y = GAMESIZEY / 2 + -sinf(_clockAngle[0]) * 1400;
	//
	//	_clockPt[4].x = GAMESIZEX / 2 + cosf(_clockAngle[1]) * 1400;
	//	_clockPt[4].y = GAMESIZEY / 2 + -sinf(_clockAngle[1]) * 1400;
	//
	//	_clockPt[7].x = GAMESIZEX / 2 + cosf(_clockAngle[2]) * 1400;
	//	_clockPt[7].y = GAMESIZEY / 2 + -sinf(_clockAngle[2]) * 1400;
	//
	//	_clockPt[10].x = GAMESIZEX / 2 + cosf(_clockAngle[3]) * 1400;
	//	_clockPt[10].y = GAMESIZEY / 2 + -sinf(_clockAngle[3]) * 1400;
	//
	//	_clockPt[2].x = GAMESIZEX / 2 + cosf(_clockAngle[0]) * 1400;
	//	_clockPt[2].y = GAMESIZEY / 2 + -sinf(_clockAngle[0]) * 1400;
	//
	//	_clockPt[5].x = GAMESIZEX / 2 + cosf(_clockAngle[1]) * 1400;
	//	_clockPt[5].y = GAMESIZEY / 2 + -sinf(_clockAngle[1]) * 1400;
	//
	//	_clockPt[8].x = GAMESIZEX / 2 + cosf(_clockAngle[2]) * 1400;
	//	_clockPt[8].y = GAMESIZEY / 2 + -sinf(_clockAngle[2]) * 1400;
	//
	//	_clockPt[11].x = GAMESIZEX / 2 + cosf(_clockAngle[3]) * 1400;
	//	_clockPt[11].y = GAMESIZEY / 2 + -sinf(_clockAngle[3]) * 1400;
	//
	//	_onceTime = false;
	//	_clockWorldTime = 0.f;
	//}



	//if (KEYMANAGER->isStayKeyDown('O'))
	//{
	//	_angle += (PI / 180) * 5;
	//	_diagonalLength -= 10;
	//
	//}
	//if (KEYMANAGER->isStayKeyDown('P'))
	//{
	//	_angle -= (PI / 180) * 5;
	//	_diagonalLength += 10;
	//}
	//
	//
	//if (KEYMANAGER->isStayKeyDown('A'))
	//{
	//	_centerX -= 10;
	//}
	//if (KEYMANAGER->isStayKeyDown('D'))
	//{
	//	_centerX += 10;
	//}
	//if (KEYMANAGER->isStayKeyDown('W'))
	//{
	//	_centerY -= 10;
	//}
	//if (KEYMANAGER->isStayKeyDown('S'))
	//{
	//	_centerY += 10;
	//}

	//if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	//{
	//	if (_isfadeOut)
	//	{
	//		_isfadeOut = false;
	//	}
	//	else
	//	{
	//		_isfadeOut = true;
	//	}
	//}

	//if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	//{
	//	if (_isClockFadeOut)
	//	{
	//		_isClockFadeOut = false;
	//	}
	//	else
	//	{
	//		_isClockFadeOut = true;
	//	}
	//}
}

void blackFadeOut::render()
{
	if (_isfadeOut)
	{
		//색 지우기
		IMAGEMANAGER->findImage("blackBox")->setTransColor(true, MAGENTA);
		//백버퍼
		IMAGEMANAGER->render("blackBox", getMemDC());
	}

	//char str[120];
	//sprintf_s(str, "%d", _isClockFadeOut);
	//TextOut(getMemDC(), 300, 600, str, strlen(str));

	//백버퍼 초기화
	PatBlt(IMAGEMANAGER->findImage("blackBox")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
}

void blackFadeOut::createColorObject(const char* hdcName, POINT* point, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), brush);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), pen);

	POINT pt[4];

	for (int i = 0; i < 4; ++i)
	{
		pt[i] = point[i];
	}

	Polygon(IMAGEMANAGER->findImage(hdcName)->getMemDC(), pt, sizeof(pt) / sizeof(pt[0]));
	SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), oldPen);
	DeleteObject(pen);
	SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), oldBrush);
	DeleteObject(brush);
}

void blackFadeOut::pointSetting()
{
	_pt[0] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,0) + _angle) * _diagonalLength ,
				_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,0) + _angle) * _diagonalLength };
	_pt[1] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,0) + _angle) * _diagonalLength,
				_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,0) + _angle) * _diagonalLength };
	_pt[2] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,768) + _angle) * _diagonalLength ,
				_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,1024,768) + _angle) * _diagonalLength };
	_pt[3] = { _centerX + cosf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,768) + _angle) * _diagonalLength ,
				_centerY + -sinf(getAngle(GAMESIZEX / 2.f,GAMESIZEY / 2.f,0,768) + _angle) * _diagonalLength };
}

void blackFadeOut::diagonalLengthSize()
{
	if (_isfadeOut)
	{
		float elapsedTime = TIMEMANAGER->getElapsedTime();

		if (!_once)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
			_once = true;
		}

		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_diagonalLength -= _diagonalMaxLength * (elapsedTime / 1.0f);
			_angle += (PI / 180) * 6;
		}

		if (1.0f + _worldTime < TIMEMANAGER->getWorldTime() && 1.5f + _worldTime > TIMEMANAGER->getWorldTime())
		{
			_diagonalLength = 0.f;
		}

		if (1.5f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_diagonalLength += _diagonalMaxLength * (elapsedTime / 1.0f);
			_angle += (PI / 180) * 6;
		}

		if (3.0f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_isfadeOut = false;
		}
	}
}

void blackFadeOut::linearInterPolation()
{
	if (_isfadeOut)
	{
		float distance = getDistance(GAMESIZEX / 2.f, GAMESIZEY / 2.f, _goal.x + 5, _goal.y);
		float angle = getAngle(GAMESIZEX / 2.f, GAMESIZEY / 2.f, _goal.x + 5, _goal.y);

		float speed = distance * (TIMEMANAGER->getElapsedTime() / 1.0f);

		if (1.0f + _worldTime >= TIMEMANAGER->getWorldTime())
		{
			_centerX += cosf(angle) * speed;
			_centerY += -sinf(angle) * speed;
		}
	}
}
