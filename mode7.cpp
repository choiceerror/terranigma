#include "stdafx.h"
#include "mode7.h"

mode7::mode7() { }

mode7::~mode7() { }

HRESULT mode7::init(image* img)
{
	_terrainMap = new image;
	_terrainMap = img;
	_totalMap = new image;
	_totalMap = IMAGEMANAGER->addImage("TOTALMAP", TOTALSIZEX, TOTALSIZEY);
	BitBlt(_totalMap->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY,
		_terrainMap->getMemDC(), 0, 0, SRCCOPY);
	_mode7Image = new image;
	_mode7Image->init(GAMESIZEX, GAMESIZEY);
	_mode7Image->setTransColor(true, RGB(255, 0, 255));

	_worldH = 100.0f;


	_foVHalf = PI / 5.0f;
	_foHHalf = PI / 8.0f;

	_far = 550.0f;
	_near = 0.0f;
	_line = 90.0f;
	_mapBitmap = _totalMap->getBitMap();
	_mode7Bitmap = CreateBitmap(GAMESIZEX, GAMESIZEY, 1, 32, NULL);

	_mapPattern = new unsigned int[TOTALSIZEX * TOTALSIZEY];
	_mode7Pattern = new unsigned int[GAMESIZEX * GAMESIZEY];

	GetBitmapBits(_mapBitmap, TOTALSIZEX * TOTALSIZEY * 4, _mapPattern);

	_kartPattern = new unsigned int[TOTALSIZEX * TOTALSIZEY];

	
	_mode7FlatMode = false;

	_once = false;

	return S_OK;
}

void mode7::release(void)
{

}

void mode7::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
	{
		_worldY -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
	{
		_worldY += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
	{
		_worldX -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
	{
		_worldX += 5;
	}


	if (KEYMANAGER->isStayKeyDown('Q')) _foVHalf += 0.02f;
	if (KEYMANAGER->isStayKeyDown('W')) _foVHalf -= 0.02f;
	if (KEYMANAGER->isStayKeyDown('E')) _near += 5.f;
	if (KEYMANAGER->isStayKeyDown('R')) _near -= 5.f;
	if (KEYMANAGER->isStayKeyDown('A')) _far += 5.f;
	if (KEYMANAGER->isStayKeyDown('S')) _far -= 5.f;
	if (KEYMANAGER->isStayKeyDown('D')) _line += 5.f;
	if (KEYMANAGER->isStayKeyDown('F')) _line -= 5.f;
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		if (_mode7FlatMode)
		{
			_mode7FlatMode = false;
		}
		else
		{
			_mode7FlatMode = true;
		}
	}

	if (_mode7FlatMode)
	{
		for (int i = 0; i < GAMESIZEX * GAMESIZEY; ++i)
		{
			*(_mode7Pattern + i) = MAGENTA;
		}

		_farX1 = _worldX + cosf(_worldA + _foVHalf) * _far;
		_farY1 = _worldY - sinf(_worldA + _foVHalf) * _far;

		_farX2 = _worldX + cosf(_worldA - _foVHalf) * _far;
		_farY2 = _worldY - sinf(_worldA - _foVHalf) * _far;

		_nearX1 = _worldX + cosf(_worldA + _foVHalf) * _near;
		_nearY1 = _worldY - sinf(_worldA + _foVHalf) * _near;

		_nearX2 = _worldX + cosf(_worldA - _foVHalf) * _near;
		_nearY2 = _worldY - sinf(_worldA - _foVHalf) * _near;

		for (int y = 0; y < GAMESIZEY; ++y)
		{
			_sampleDepth = (float)y / (float)GAMESIZEY;

			_startX = (_farX1 - _nearX1) / (_sampleDepth)+_nearX1;
			_startY = (_farY1 - _nearY1) / (_sampleDepth)+_nearY1;

			_endX = (_farX2 - _nearX2) / (_sampleDepth)+_nearX2;
			_endY = (_farY2 - _nearY2) / (_sampleDepth)+_nearY2;

			for (int x = 0; x < GAMESIZEX; ++x)
			{
				_sampleWidth = (float)x / (float)GAMESIZEX;

				_sampleX = (_endX - _startX) * _sampleWidth + _startX;
				_sampleY = (_endY - _startY) * _sampleWidth + _startY;

				if ((int)_sampleX < 0 || (int)_sampleX > TOTALSIZEX - 1 ||
					(int)_sampleY < 0 || (int)_sampleY > TOTALSIZEY - 1) continue;

				*(_mode7Pattern + y * GAMESIZEX + x) = *(_mapPattern + (int)_sampleY * TOTALSIZEX + (int)_sampleX);
			}
		}
	}
	else
	{
		for (int i = 0; i < GAMESIZEX * GAMESIZEY; ++i)
		{
			*(_mode7Pattern + i) = MAGENTA;
		}

		_farX1 = _worldX + cosf(_worldA + _foVHalf) * _far;
		_farY1 = _worldY - sinf(_worldA + _foVHalf) * _far;

		_farX2 = _worldX + cosf(_worldA - _foVHalf) * _far;
		_farY2 = _worldY - sinf(_worldA - _foVHalf) * _far;

		_nearX1 = _worldX + cosf(_worldA + _foVHalf) * _near;
		_nearY1 = _worldY - sinf(_worldA + _foVHalf) * _near;

		_nearX2 = _worldX + cosf(_worldA - _foVHalf) * _near;
		_nearY2 = _worldY - sinf(_worldA - _foVHalf) * _near;

		for (int y = 0; y < GAMESIZEY; ++y)
		{
			_sampleDepth = (float)y / (float)GAMESIZEY;

			_startX = (_farX1 - _nearX1) * (1 - _sampleDepth)+_nearX1;
			_startY = (_farY1 - _nearY1) * (1 - _sampleDepth)+_nearY1;

			_endX = (_farX2 - _nearX2) * (1 - _sampleDepth)+_nearX2;
			_endY = (_farY2 - _nearY2) * (1 - _sampleDepth)+_nearY2;

			for (int x = 0; x < GAMESIZEX; ++x)
			{
				_sampleWidth = (float)x / (float)GAMESIZEX;

				_sampleX = (_endX - _startX) * _sampleWidth + _startX;
				_sampleY = (_endY - _startY) * _sampleWidth + _startY;

				if ((int)_sampleX < 0 || (int)_sampleX > TOTALSIZEX - 1 ||
					(int)_sampleY < 0 || (int)_sampleY > TOTALSIZEY - 1) continue;

				*(_mode7Pattern + y * GAMESIZEX + x) = *(_mapPattern + (int)_sampleY * TOTALSIZEX + (int)_sampleX);
			}
		}
	}
}

void mode7::render(HDC dc)
{
	SetBitmapBits(_mode7Bitmap, GAMESIZEX * GAMESIZEY * 4, _mode7Pattern);

	SelectObject(_mode7Image->getMemDC(), _mode7Bitmap);

	if (_mode7FlatMode)
	{
		_mode7Image->render(dc, 0, - 50);
	}
	else
	{
		_mode7Image->render(dc, 0, 75);
	}
	
}

void mode7::setMode7Point(float x, float y, float angle)
{
	_worldX = x + cos(angle + PI) * _line;
	_worldY = y - sin(angle + PI) * _line;

	_worldA = angle;
}

void mode7::setObjectImage(image* objectImage)
{
	BitBlt(_totalMap->getMemDC(), 0, 0, TOTALSIZEX, TOTALSIZEY,
		_terrainMap->getMemDC(), 0, 0, SRCCOPY);

	GdiTransparentBlt(_totalMap->getMemDC(),
		0, 0,
		TOTALSIZEX, TOTALSIZEY,
		objectImage->getMemDC(),
		0, 0,
		TOTALSIZEX, TOTALSIZEY,
		RGB(0, 0, 0));

	GetBitmapBits(_totalMap->getBitMap(), TOTALSIZEX * TOTALSIZEY * 4, _mapPattern);
}
