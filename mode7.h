#pragma once
#include "gameNode.h"

class mode7 : public gameNode
{
private:
	HBITMAP			_mapBitmap;
	HBITMAP			_mode7Bitmap;
	unsigned int*	_mapPattern;
	unsigned int*	_mode7Pattern;

	unsigned int*	_kartPattern;
	HBITMAP			_kartMode7Bitmap;
	unsigned int*	_kartMode7Pattern;
private:
	image*		_terrainMap;
	image*		_totalMap;
	image*		_mode7Image;

	float		_worldX;
	float		_worldY;
	float		_worldH;

	float		_line;
	float		_worldA;

	float		_near;
	float		_far;
	float		_foVHalf;
	float		_foHHalf;

	float		_farX1;
	float		_farY1;

	float		_farX2;
	float		_farY2;

	float		_nearX1;
	float		_nearY1;

	float		_nearX2;
	float		_nearY2;

	float		_sampleDepth;

	float		_startX;
	float		_startY;

	float		_endX;
	float		_endY;

	float		_sampleWidth;

	float		_sampleX;
	float		_sampleY;



public:
	mode7();
	~mode7();

	virtual HRESULT init(image* img);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC dc);

	void setMode7Point(float x, float y, float angle);
	void setObjectImage(image* objectImage);
	void setKartBitmap(HBITMAP bitmap) { GetBitmapBits(bitmap, TOTALSIZEX * TOTALSIZEY * 4, _kartPattern); }
	HBITMAP getKartBitmap(void) { return _kartMode7Bitmap; }
};

