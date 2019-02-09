#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{

	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

image* imageManager::addImage(string strKey, int width, int height)
{
	image* img = findImage(strKey);

	//만약에 찾으려던 그 이미지가 있으면 그냥 그 이미지를 반환
	if (img) return img;

	//없단 얘기!
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}
	//map.insert(pair<first자료형, second자료형>(변수명1, 변수명2))
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 찾으려던 그 이미지가 있으면 그냥 그 이미지를 반환
	if (img) return img;

	//없단 얘기!
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}
	//map.insert(pair<first자료형, second자료형>(변수명1, 변수명2))
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 찾으려던 그 이미지가 있으면 그냥 그 이미지를 반환
	if (img) return img;

	//없단 얘기!
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}
	//map.insert(pair<first자료형, second자료형>(변수명1, 변수명2))
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addRotateImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 찾으려던 그 이미지가 있으면 그냥 그 이미지를 반환
	if (img) return img;

	//없단 얘기!
	img = new image;

	if (FAILED(img->rotateInit(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}
	//map.insert(pair<first자료형, second자료형>(변수명1, 변수명2))
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 찾으려던 그 이미지가 있으면 그냥 그 이미지를 반환
	if (img) return img;

	//없단 얘기!
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}
	//map.insert(pair<first자료형, second자료형>(변수명1, 변수명2))
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 찾으려던 그 이미지가 있으면 그냥 그 이미지를 반환
	if (img) return img;

	//없단 얘기!
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}
	//map.insert(pair<first자료형, second자료형>(변수명1, 변수명2))
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addRotateFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 찾으려던 그 이미지가 있으면 그냥 그 이미지를 반환
	if (img) return img;

	//없단 얘기!
	img = new image;

	if (FAILED(img->rotateInit(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}
	//map.insert(pair<first자료형, second자료형>(변수명1, 변수명2))
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//지우려는 이미지의 키 값을 찾았으면
	if (key != _mImageList.end())
	{
		//map<string, image*>
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL imageManager::deleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return true;
}

void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
	
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::expandRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY)
{
	image* img = findImage(strKey);

	if (img) img->expandRender(hdc, destX, destY, currentFrameX, currentFrameY, sizeX, sizeY);
}

void imageManager::expandRenderCenter(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY)
{
	image* img = findImage(strKey);

	if (img) img->expandRenderCenter(hdc, destX, destY, currentFrameX, currentFrameY, sizeX, sizeY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);

	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}

void imageManager::rotateRender(string strKey, HDC hdc, float centerX, float centerY, float angle)
{
	image* img = findImage(strKey);

	if (img) img->rotateRender(hdc, centerX, centerY, angle);
}

void imageManager::rotateFrameRender(string strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle)
{
	image* img = findImage(strKey);

	if (img) img->rotateFrameRender(hdc, centerX, centerY, currentFrameX, currentFrameY, angle);
}
