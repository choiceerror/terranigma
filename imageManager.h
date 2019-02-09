#pragma once

#include "singletonBase.h"
#include "image.h"
#include <map> //사실 안해도 되는데 선언해봄 ㅋ _ㅋ

class imageManager : public singletonBase<imageManager>
{
private:
	//map<string, image*> <-- 얘를          mapImageList라 부르겠다.
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;


public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	image* addRotateImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addRotateFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//이미지를 찾는 함수
	image* findImage(string strKey);

	//싱글톤화 되어있는 이미지 지워주는 함쓔
	BOOL deleteImage(string strKey);

	//싸그리..
	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void expandRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX = 1.0f, float sizeY = 1.0f);
	void expandRenderCenter(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX = 1.0f, float sizeY = 1.0f);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void rotateRender(string strKey, HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(string strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle);
};

