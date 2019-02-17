#include "stdafx.h"
#include "ClockFadeOut.h"


ClockFadeOut::ClockFadeOut()
{
}


ClockFadeOut::~ClockFadeOut()
{
}

HRESULT ClockFadeOut::init()
{
	IMAGEMANAGER->addImage("clockBuffer", GAMESIZEX, GAMESIZEY);

	_isClockFadeOut = false;
	_isClockFadeIn = false;

	_onceTime = false;
	_clockWorldTime = 0;
	_onceTimeIn = false;
	_clockWorldTimeIn = 0;

	for (int i = 0; i < 8; ++i)
	{
		_goalArrive[i] = false;
	}

	return S_OK;
}

void ClockFadeOut::release()
{
}

void ClockFadeOut::update()
{
	HBRUSH brush = CreateSolidBrush(MAGENTA);
	HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("clockBuffer")->getMemDC(), brush);
	_magentaBox = RectMake(0, 0, GAMESIZEX, GAMESIZEY);
	Rectangle(IMAGEMANAGER->findImage("clockBuffer")->getMemDC(), _magentaBox);
	SelectObject(IMAGEMANAGER->findImage("clockBuffer")->getMemDC(), oldBrush);
	DeleteObject(brush);

	_angleSpeed = 90 * (TIMEMANAGER->getElapsedTime() / 0.3f);

	if (_isClockFadeOut)
	{
		if (!_onceTime)
		{
			_clockWorldTime = TIMEMANAGER->getWorldTime();
		}

		//========================블랙========================

		if (0.3f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		{
			_clockBlackAngle[0] -= (PI / 180) * _angleSpeed;
			_clockBlackPt[2].x = GAMESIZEX / 2 + cosf(_clockBlackAngle[0]) * 1400;
			_clockBlackPt[2].y = GAMESIZEY / 2 + -sinf(_clockBlackAngle[0]) * 1400;
		}

		if (0.3f + _clockWorldTime <= TIMEMANAGER->getWorldTime() && 0.6f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		{
			_clockBlackPt[3].x = GAMESIZEX / 2;
			_clockBlackPt[3].y = GAMESIZEY / 2;
			_clockBlackPt[4].x = GAMESIZEX / 2 + cosf((PI/180)*360) * 1400;
			_clockBlackPt[4].y = GAMESIZEY / 2 + -sinf((PI / 180) * 360) * 1400;
			_clockBlackPt[5].x = GAMESIZEX / 2 + cosf(_clockBlackAngle[1]) * 1400;
			_clockBlackPt[5].y = GAMESIZEY / 2 + -sinf(_clockBlackAngle[1]) * 1400;

			_clockBlackAngle[1] -= (PI / 180) * _angleSpeed;
		}

		if (0.6f + _clockWorldTime <= TIMEMANAGER->getWorldTime() && 0.9f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		{
			_clockBlackPt[6].x = GAMESIZEX / 2;
			_clockBlackPt[6].y = GAMESIZEY / 2;
			_clockBlackPt[7].x = GAMESIZEX / 2 + cosf((PI / 180) * 279) * 1400;
			_clockBlackPt[7].y = GAMESIZEY / 2 + -sinf((PI / 180) * 270) * 1400;
			_clockBlackPt[8].x = GAMESIZEX / 2 + cosf(_clockBlackAngle[2]) * 1400;
			_clockBlackPt[8].y = GAMESIZEY / 2 + -sinf(_clockBlackAngle[2]) * 1400;

			_clockBlackAngle[2] -= (PI / 180) * _angleSpeed;
		}

		if (0.9f + _clockWorldTime < TIMEMANAGER->getWorldTime() && 1.25f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		{
			_clockBlackPt[9].x = GAMESIZEX / 2;
			_clockBlackPt[9].y = GAMESIZEY / 2;
			_clockBlackPt[10].x = GAMESIZEX / 2 + cosf((PI / 180) * 180) * 1400;
			_clockBlackPt[10].y = GAMESIZEY / 2 + -sinf((PI / 180) * 189) * 1400;
			_clockBlackPt[11].x = GAMESIZEX / 2 + cosf(_clockBlackAngle[3]) * 1400;
			_clockBlackPt[11].y = GAMESIZEY / 2 + -sinf(_clockBlackAngle[3]) * 1400;

			_clockBlackAngle[3] -= (PI / 180) * _angleSpeed;
		}

		////===========================마젠타================================
		//
		//if (1.2f + _clockWorldTime < TIMEMANAGER->getWorldTime() && 1.6f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		//{
		//	_clockMagentaPt[0].x = GAMESIZEX / 2;
		//	_clockMagentaPt[0].y = GAMESIZEY / 2;
		//	_clockMagentaPt[1].x = GAMESIZEX / 2 + cosf((PI / 180) * 90) * 1400;
		//	_clockMagentaPt[1].y = GAMESIZEY / 2 + -sinf((PI / 180) * 90) * 1400;
		//	_clockMagentaPt[2].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[0]) * 1400;
		//	_clockMagentaPt[2].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[0]) * 1400;
		//
		//	_clockMagentaAngle[0] -= (PI / 180) * _angleSpeed;
		//}
		//
		//if (1.5f + _clockWorldTime < TIMEMANAGER->getWorldTime() && 1.9f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		//{
		//	_clockMagentaPt[3].x = GAMESIZEX / 2;
		//	_clockMagentaPt[3].y = GAMESIZEY / 2;
		//	_clockMagentaPt[4].x = GAMESIZEX / 2 + cosf((PI / 180) * 360) * 1400;
		//	_clockMagentaPt[4].y = GAMESIZEY / 2 + -sinf((PI / 180) * 360) * 1400;
		//	_clockMagentaPt[5].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[1]) * 1400;
		//	_clockMagentaPt[5].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[1]) * 1400;
		//
		//	_clockMagentaAngle[1] -= (PI / 180) * _angleSpeed;
		//}
		//
		//if (1.8 + _clockWorldTime < TIMEMANAGER->getWorldTime() && 2.2f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		//{
		//	_clockMagentaPt[6].x = GAMESIZEX / 2;
		//	_clockMagentaPt[6].y = GAMESIZEY / 2;
		//	_clockMagentaPt[7].x = GAMESIZEX / 2 + cosf((PI / 180) * 270) * 1400;
		//	_clockMagentaPt[7].y = GAMESIZEY / 2 + -sinf((PI / 180) * 270) * 1400;
		//	_clockMagentaPt[8].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[2]) * 1400;
		//	_clockMagentaPt[8].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[2]) * 1400;
		//
		//	_clockMagentaAngle[2] -= (PI / 180) * _angleSpeed;
		//}
		//
		//if (2.1f + _clockWorldTime < TIMEMANAGER->getWorldTime() && 2.4f + _clockWorldTime >= TIMEMANAGER->getWorldTime())
		//{
		//	_clockMagentaPt[9].x = GAMESIZEX / 2;
		//	_clockMagentaPt[9].y = GAMESIZEY / 2;
		//	_clockMagentaPt[10].x = GAMESIZEX / 2 + cosf((PI / 180) * 180) * 1400;
		//	_clockMagentaPt[10].y = GAMESIZEY / 2 + -sinf((PI / 180) * 180) * 1400;
		//	_clockMagentaPt[11].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[3]) * 1400;
		//	_clockMagentaPt[11].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[3]) * 1400;
		//
		//	_clockMagentaAngle[3] -= (PI / 180) * _angleSpeed;
		//}

		if (1.5f + _clockWorldTime < TIMEMANAGER->getWorldTime())
		{
			_isClockFadeOut = false;
		}

		POINT _pt1[] = { _clockBlackPt[0],_clockBlackPt[1],_clockBlackPt[2] };
		POINT _pt2[] = { _clockBlackPt[3],_clockBlackPt[4],_clockBlackPt[5] };
		POINT _pt3[] = { _clockBlackPt[6],_clockBlackPt[7],_clockBlackPt[8] };
		POINT _pt4[] = { _clockBlackPt[9],_clockBlackPt[10],_clockBlackPt[11] };

		createColorObject3("clockBuffer", _pt1, BLACK);
		createColorObject3("clockBuffer", _pt2, BLACK);
		createColorObject3("clockBuffer", _pt3, BLACK);
		createColorObject3("clockBuffer", _pt4, BLACK);

		//POINT _pt5[] = { _clockMagentaPt[0],_clockMagentaPt[1],_clockMagentaPt[2] };
		//POINT _pt6[] = { _clockMagentaPt[3],_clockMagentaPt[4],_clockMagentaPt[5] };
		//POINT _pt7[] = { _clockMagentaPt[6],_clockMagentaPt[7],_clockMagentaPt[8] };
		//POINT _pt8[] = { _clockMagentaPt[9],_clockMagentaPt[10],_clockMagentaPt[11] };
		//
		//createColorObject3("clockBuffer", _pt5, MAGENTA);
		//createColorObject3("clockBuffer", _pt6, MAGENTA);
		//createColorObject3("clockBuffer", _pt7, MAGENTA);
		//createColorObject3("clockBuffer", _pt8, MAGENTA);

		_onceTime = true;
	}
	else
	{
		_clockBlackAngle[0] = (PI / 180) * 90;
		_clockBlackAngle[1] = (PI / 180) * 360;
		_clockBlackAngle[2] = (PI / 180) * 270;
		_clockBlackAngle[3] = (PI / 180) * 180;
	
		_clockBlackPt[0].x = GAMESIZEX / 2;
		_clockBlackPt[0].y = GAMESIZEY / 2;
		_clockBlackPt[1].x = GAMESIZEX / 2 + cosf(_clockBlackAngle[0]) * 1400;
		_clockBlackPt[1].y = GAMESIZEY / 2 + -sinf(_clockBlackAngle[0]) * 1400;
		_clockBlackPt[2].x = GAMESIZEX / 2 + cosf(_clockBlackAngle[0]) * 1400;
		_clockBlackPt[2].y = GAMESIZEY / 2 + -sinf(_clockBlackAngle[0]) * 1400;

		for (int i = 3; i < 12; ++i)
		{
			_clockBlackPt[i].x = -50;
			_clockBlackPt[i].y = -50;
		}
		

		_onceTime = false;
		_clockWorldTime = 0.f;
	}

	if (_isClockFadeIn)
	{
		if (!_onceTimeIn)
		{
			_clockWorldTimeIn = TIMEMANAGER->getWorldTime();
		}

		HBRUSH brush = CreateSolidBrush(BLACK);
		HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("clockBuffer")->getMemDC(), brush);
		_blackBox = RectMake(0, 0, GAMESIZEX, GAMESIZEY);
		Rectangle(IMAGEMANAGER->findImage("clockBuffer")->getMemDC(), _blackBox);
		SelectObject(IMAGEMANAGER->findImage("clockBuffer")->getMemDC(), oldBrush);
		DeleteObject(brush);

		////===========================마젠타================================
		if (0.35f + _clockWorldTimeIn > TIMEMANAGER->getWorldTime())
		{
			_clockMagentaPt[0].x = GAMESIZEX / 2;
			_clockMagentaPt[0].y = GAMESIZEY / 2;
			_clockMagentaPt[1].x = GAMESIZEX / 2 + cosf((PI / 180) * 90) * 1400;
			_clockMagentaPt[1].y = GAMESIZEY / 2 + -sinf((PI / 180) * 90) * 1400;
			_clockMagentaPt[2].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[0]) * 1400;
			_clockMagentaPt[2].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[0]) * 1400;

			_clockMagentaAngle[0] -= (PI / 180) * _angleSpeed;
		}

		if (0.3f + _clockWorldTimeIn < TIMEMANAGER->getWorldTime() && 0.7f + _clockWorldTimeIn >= TIMEMANAGER->getWorldTime())
		{
			_clockMagentaPt[3].x = GAMESIZEX / 2;
			_clockMagentaPt[3].y = GAMESIZEY / 2;
			_clockMagentaPt[4].x = GAMESIZEX / 2 + cosf((PI / 180) * 360) * 1400;
			_clockMagentaPt[4].y = GAMESIZEY / 2 + -sinf((PI / 180) * 360) * 1400;
			_clockMagentaPt[5].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[1]) * 1400;
			_clockMagentaPt[5].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[1]) * 1400;

			_clockMagentaAngle[1] -= (PI / 180) * _angleSpeed;
		}

		if (0.6f + _clockWorldTimeIn < TIMEMANAGER->getWorldTime() && 1.f + _clockWorldTimeIn >= TIMEMANAGER->getWorldTime())
		{
			_clockMagentaPt[6].x = GAMESIZEX / 2;
			_clockMagentaPt[6].y = GAMESIZEY / 2;
			_clockMagentaPt[7].x = GAMESIZEX / 2 + cosf((PI / 180) * 270) * 1400;
			_clockMagentaPt[7].y = GAMESIZEY / 2 + -sinf((PI / 180) * 270) * 1400;
			_clockMagentaPt[8].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[2]) * 1400;
			_clockMagentaPt[8].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[2]) * 1400;

			_clockMagentaAngle[2] -= (PI / 180) * _angleSpeed;
		}

		if (0.9f + _clockWorldTimeIn < TIMEMANAGER->getWorldTime() && 1.3f + _clockWorldTimeIn >= TIMEMANAGER->getWorldTime())
		{
			_clockMagentaPt[9].x = GAMESIZEX / 2;
			_clockMagentaPt[9].y = GAMESIZEY / 2;
			_clockMagentaPt[10].x = GAMESIZEX / 2 + cosf((PI / 180) * 180) * 1400;
			_clockMagentaPt[10].y = GAMESIZEY / 2 + -sinf((PI / 180) * 180) * 1400;
			_clockMagentaPt[11].x = GAMESIZEX / 2 + cosf(_clockMagentaAngle[3]) * 1400;
			_clockMagentaPt[11].y = GAMESIZEY / 2 + -sinf(_clockMagentaAngle[3]) * 1400;

			_clockMagentaAngle[3] -= (PI / 180) * _angleSpeed;
		}

		if (1.2f + _clockWorldTimeIn <= TIMEMANAGER->getWorldTime())
		{
			_isClockFadeIn = false;
		}


		POINT _pt5[] = { _clockMagentaPt[0],_clockMagentaPt[1],_clockMagentaPt[2] };
		POINT _pt6[] = { _clockMagentaPt[3],_clockMagentaPt[4],_clockMagentaPt[5] };
		POINT _pt7[] = { _clockMagentaPt[6],_clockMagentaPt[7],_clockMagentaPt[8] };
		POINT _pt8[] = { _clockMagentaPt[9],_clockMagentaPt[10],_clockMagentaPt[11] };

		createColorObject3("clockBuffer", _pt5, MAGENTA);
		createColorObject3("clockBuffer", _pt6, MAGENTA);
		createColorObject3("clockBuffer", _pt7, MAGENTA);
		createColorObject3("clockBuffer", _pt8, MAGENTA);


		_onceTimeIn = true;
	}
	else
	{
		_onceTimeIn = false;
		_clockWorldTimeIn = 0;

		for (int i = 3; i < 12; ++i)
		{
			_clockMagentaPt[i].x = -50;
			_clockMagentaPt[i].y = -50;
		}

		_clockMagentaAngle[0] = (PI / 180) * 90;
		_clockMagentaAngle[1] = (PI / 180) * 360;
		_clockMagentaAngle[2] = (PI / 180) * 270;
		_clockMagentaAngle[3] = (PI / 180) * 180;


		_clockMagentaPt[0].x = -50;
		_clockMagentaPt[0].y = -50;
		_clockMagentaPt[1].x = -50;
		_clockMagentaPt[1].y = -50;
		_clockMagentaPt[2].x = -50;
		_clockMagentaPt[2].y = -50;

	}





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

void ClockFadeOut::render()
{
	//색 지우기
	IMAGEMANAGER->findImage("clockBuffer")->setTransColor(true, MAGENTA);
	//백버퍼
	IMAGEMANAGER->render("clockBuffer", getMemDC());

	//char str[120];
	//sprintf_s(str, "%d %d    %d %d", _clockPt[4].x , _clockPt[4].y , _clockPt[5].x , _clockPt[5].y);
	//TextOut(getMemDC(), 300, 600, str, strlen(str));


	//백버퍼 초기화
	PatBlt(IMAGEMANAGER->findImage("clockBuffer")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
}

void ClockFadeOut::createColorObject3(const char * hdcName, POINT * point, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), brush);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), pen);

	POINT pt[3];

	for (int i = 0; i < 3; ++i)
	{
		pt[i] = point[i];
	}

	Polygon(IMAGEMANAGER->findImage(hdcName)->getMemDC(), pt, sizeof(pt) / sizeof(pt[0]));
	SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), oldPen);
	DeleteObject(pen);
	SelectObject(IMAGEMANAGER->findImage(hdcName)->getMemDC(), oldBrush);
	DeleteObject(brush);
}

void ClockFadeOut::pointSetting()
{
	if (_isClockFadeOut)
	{

	}
	else
	{

	}



}
