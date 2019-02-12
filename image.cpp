#include "stdafx.h"
#include "image.h"

//컴파일러 지시기 (나 라이브러리 쓸꺼야 msImg32 라이브러리)
#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL), _fileName(NULL),
	_trans(FALSE), _transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//알파블렌드 설정함.
	//진형 + 치영이는 집중해서 봐라
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이건 한 번 조사해보세요 여러분

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;



	if (_imageInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const DWORD resID, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//알파블렌드 설정함.
	//진형 + 치영이는 집중해서 봐라
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이건 한 번 조사해보세요 여러분

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//파일이름이 없으면 에러를  띄워라
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 초기화 되어있지 않으면 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 하나 생성해줌
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	//파일경로 및 이름을 받아온다
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//특정칼라 제외여부를 정함.
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정함.
	//진형 + 치영이는 집중해서 봐라
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이건 한 번 조사해보세요 여러분

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//파일이름이 없으면 에러를  띄워라
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 초기화 되어있지 않으면 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 하나 생성해줌
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	//파일경로 및 이름을 받아온다
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//특정칼라 제외여부를 정함.
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정함.
	//진형 + 치영이는 집중해서 봐라
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이건 한 번 조사해보세요 여러분

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//파일이름이 없으면 에러를  띄워라
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 초기화 되어있지 않으면 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 하나 생성해줌
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	//파일경로 및 이름을 받아온다
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//특정칼라 제외여부를 정함.
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정함.
	//진형 + 치영이는 집중해서 봐라
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이건 한 번 조사해보세요 여러분

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//파일이름이 없으면 에러를  띄워라
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 초기화 되어있지 않으면 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 하나 생성해줌
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	//파일경로 및 이름을 받아온다
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//특정칼라 제외여부를 정함.
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 설정함.
	//진형 + 치영이는 집중해서 봐라
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이건 한 번 조사해보세요 여러분

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::rotateInit(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	//rotate

	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);



	return S_OK;
}

HRESULT image::rotateInit(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 조금이라도 남아있으면 지워라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;			//알파블렌드를 사용하겠다고 초기화
	_blendFunc.AlphaFormat = 0;			//알파블렌드에 필요한 알파포맷 초기화
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이거말고도 몇개있으니 조사해봐염

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	int len = strlen(fileName);

	//파일경로 및 이름 받아온다
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//특정컬러 제외할지 여부 및 컬러 값
	_trans = trans;
	_transColor = transColor;

	//이미지가 제대로 불러져오지 않았다면
	if (_imageInfo->hBit == NULL)
	{
		//해제하고 에러를 띄워주자
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//각 init함수에 알파블렌드 처리할 이미지도 할당되고 있기 때문에
		//같이 해제해줘야합니다!!!!!!!!!!!!!!!
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = FALSE;
	}
}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::setAlpahBlend(BOOL alpha, BYTE alphaValue)
{
	_alpha = alpha;
	_alphaValue = alphaValue;

	HDC hdc = GetDC(_hWnd);

	//알파블렌드 설정함.
	//진형 + 치영이는 집중해서 봐라
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- 이건 한 번 조사해보세요 여러분

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 DC
			0,					//이미지 그려줄 시작X좌표(left)
			0,					//이미지 그려줄 시작Y좌표(top)
			_imageInfo->width,		//복사될 가로크기
			_imageInfo->height,		//복사될 세로크기
			_imageInfo->hMemDC,
			0, 0,					//복사시작할 XY좌표
			_imageInfo->width,		//복사할 가로/세로크기
			_imageInfo->height,
			_transColor				//복사때 제외할 칼라(뺄 칼라)
		);
	}
	else
	{
		BitBlt(hdc, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 DC
			destX,					//이미지 그려줄 시작X좌표(left)
			destY,					//이미지 그려줄 시작Y좌표(top)
			_imageInfo->width,		//복사될 가로크기
			_imageInfo->height,		//복사될 세로크기
			_imageInfo->hMemDC,
			0, 0,					//복사시작할 XY좌표
			_imageInfo->width,		//복사할 가로/세로크기
			_imageInfo->height,
			_transColor				//복사때 제외할 칼라(뺄 칼라)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 DC
			destX,					//이미지 그려줄 시작X좌표(left)
			destY,					//이미지 그려줄 시작Y좌표(top)
			sourWidth,				//복사될 가로크기
			sourHeight,				//복사될 세로크기
			_imageInfo->hMemDC,
			sourX, sourY,			//복사시작할 XY좌표
			sourWidth,				//복사할 가로/세로크기
			sourHeight,
			_transColor				//복사때 제외할 칼라(뺄 칼라)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 DC
			destX,					//이미지 그려줄 시작X좌표(left)
			destY,					//이미지 그려줄 시작Y좌표(top)
			_imageInfo->frameWidth,				//복사될 가로크기
			_imageInfo->frameHeight,				//복사될 세로크기
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사시작할 XY좌표
			_imageInfo->frameWidth,				//복사할 가로/세로크기
			_imageInfo->frameHeight,
			_transColor				//복사때 제외할 칼라(뺄 칼라)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 DC
			destX,					//이미지 그려줄 시작X좌표(left)
			destY,					//이미지 그려줄 시작Y좌표(top)
			_imageInfo->frameWidth,				//복사될 가로크기
			_imageInfo->frameHeight,				//복사될 세로크기
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//복사시작할 XY좌표
			_imageInfo->frameWidth,				//복사할 가로/세로크기
			_imageInfo->frameHeight,
			_transColor				//복사때 제외할 칼라(뺄 칼라)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	//화면에 루프이미지 그려줄 영역을 셋팅해보자
	int drawAreaX = drawArea->left;				//그려줄 영역의 Left
	int drawAreaY = drawArea->top;				//그려줄 영역의 top
	int drawAreaW = drawArea->right - drawAreaX; //그려줄 영역의 가로크기
	int drawAreaH = drawArea->bottom - drawAreaY;//그려줄 영역의 세로크기

	//세로부터 해봅시다
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//나머지 연산을 통해서 정확한 수치를 알아온다
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//밀려올라간 간격 계산
		sourHeight = rcSour.bottom - rcSour.top;

		//화면밖으로 이미지가 나갔다면
		if (y + sourHeight > drawAreaH)
		{
			//그만큼 보정해줘라 - 연산때문에 실제로 -빼면 위가 아니라 밑으로간다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//화면밖으로 나간영역을 다시 밀어올린다(다시 그려준다)
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//하영이가 원하는 X축
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//나머지 연산을 통한 정밀 보정
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}

}

//
void image::alphaRender(HDC hdc)
{
	alphaRender(hdc, _alphaValue);
}

//
void image::alphaRender(HDC hdc, BYTE alpha)
{
	//순서에 주의합시다
	//BYTE는 알파블렌드 수치값이다. 0 ~ 255의 범위를 가진다
	//값이 작을수록 투명도가 높다

	// 알파 설정 안하면 일반 렌더 사용
	if (!_alpha)
	{
		render(hdc);
		return;
	}

	_alphaValue = alpha;

	//이것을 해야 알파값이 적용됨!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사될 DC
			0,						//이미지 그려줄 시작X좌표(left)
			0,						//이미지 그려줄 시작Y좌표(top)
			_imageInfo->width,		//복사될 가로크기
			_imageInfo->height,		//복사될 세로크기
			_imageInfo->hMemDC,
			0, 0,					//복사시작할 XY좌표
			_imageInfo->width,		//복사할 가로/세로크기
			_imageInfo->height,
			_transColor				//복사때 제외할 칼라(뺄 칼라)
		);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY)
{
	//순서에 주의합시다
	//BYTE는 알파블렌드 수치값이다. 0 ~ 255의 범위를 가진다
	//값이 작을수록 투명도가 높다

	// 알파 설정 안하면 일반 렌더 사용
	if (!_alpha)
	{
		render(hdc, destX, destY);
		return;
	}

	//이것을 해야 알파값이 적용됨!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사될 DC
			0,						//이미지 그려줄 시작X좌표(left)
			0,						//이미지 그려줄 시작Y좌표(top)
			_imageInfo->width,		//복사될 가로크기
			_imageInfo->height,		//복사될 세로크기
			_imageInfo->hMemDC,
			0, 0,					//복사시작할 XY좌표
			_imageInfo->width,		//복사할 가로/세로크기
			_imageInfo->height,
			_transColor				//복사때 제외할 칼라(뺄 칼라)
		);

		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}

}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_alphaValue = alpha;
	alphaRender(hdc, destX, destY);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY)
{
	// 알파 설정 안하면 일반 프레임 렌더 사용
	if (!_alpha)
	{
		frameRender(hdc, destX, destY);
		return;
	}

	//이것을 해야 알파값이 적용됨!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC
			, 0, 0
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, hdc
			, destX, destY
			, SRCCOPY);

		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,								//복사될 DC
			0,												//이미지 그려줄 시작X좌표(left)
			0,												//이미지 그려줄 시작Y좌표(top)
			_imageInfo->frameWidth,								//복사될 가로크기
			_imageInfo->frameHeight,							//복사될 세로크기
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//복사시작할 XY좌표
			_imageInfo->frameWidth,								//복사할 가로/세로크기
			_imageInfo->frameHeight,
			_transColor											//복사때 제외할 칼라(뺄 칼라)
		);

		AlphaBlend(hdc
			, destX, destY
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendImage->hMemDC
			, 0, 0
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc
			, destX, destY
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendImage->hMemDC
			, 0, 0
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_alphaValue = alpha;
	alphaFrameRender(hdc, destX, destY);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	alphaFrameRender(hdc, destX, destY);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_alphaValue = alpha;
	alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
	// 알파 설정 안하면 일반 애니 렌더 사용
	if (!_alpha)
	{
		render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
		return;
	}

	_alphaValue = alpha;

	//이것을 해야 알파값이 적용됨!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, hdc
			, destX, destY
			, SRCCOPY);

		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,								//복사될 DC
			0,												//이미지 그려줄 시작X좌표(left)
			0,												//이미지 그려줄 시작Y좌표(top)
			ani->getFrameWidth(),							//복사될 가로크기
			ani->getFrameHeight(),							//복사될 세로크기
			_imageInfo->hMemDC,
			ani->getFramePos().x,
			ani->getFramePos().y,							//복사시작할 XY좌표
			ani->getFrameWidth(),							//복사할 가로/세로크기
			ani->getFrameHeight(),
			_transColor											//복사때 제외할 칼라(뺄 칼라)
		);

		AlphaBlend(hdc
			, destX, destY
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc
			, destX, destY
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}
}

void image::alphaAniRenderCenter(HDC hdc, int centerX, int centerY, animation * ani, BYTE alpha)
{
	// 알파 설정 안하면 일반 애니 렌더 사용
	if (!_alpha)
	{
		render(hdc, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
		return;
	}

	_alphaValue = alpha;

	//이것을 해야 알파값이 적용됨!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, hdc
			, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2
			, SRCCOPY);

		//특정칼라를 제외하고 DC -> DC 사이로 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,								//복사될 DC
			0,												//이미지 그려줄 시작X좌표(left)
			0,												//이미지 그려줄 시작Y좌표(top)
			ani->getFrameWidth(),							//복사될 가로크기
			ani->getFrameHeight(),							//복사될 세로크기
			_imageInfo->hMemDC,
			ani->getFramePos().x,
			ani->getFramePos().y,							//복사시작할 XY좌표
			ani->getFrameWidth(),							//복사할 가로/세로크기
			ani->getFrameHeight(),
			_transColor											//복사때 제외할 칼라(뺄 칼라)
		);

		AlphaBlend(hdc
			, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc
			, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}

}

void image::expandRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX,
		destY,
		_imageInfo->frameWidth * sizeX,
		_imageInfo->frameHeight * sizeY,
		_imageInfo->hMemDC,
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		_transColor
	);
}

void image::expandRenderCenter(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX - (sizeX *_imageInfo->frameWidth) / 2,
		destY - (sizeY * _imageInfo->frameHeight) / 2,
		_imageInfo->frameWidth * sizeX,
		_imageInfo->frameHeight * sizeY,
		_imageInfo->hMemDC,
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		_transColor
	);
}

void image::expandAniRender(HDC hdc, int destX, int destY, animation* ani, float sizeX, float sizeY)
{
	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX,
		destY,
		ani->getFrameWidth() * sizeX,
		ani->getFrameHeight() * sizeY,
		_imageInfo->hMemDC,
		ani->getFramePos().x,
		ani->getFramePos().y,
		ani->getFrameWidth(),
		ani->getFrameHeight(),
		_transColor
	);

}

void image::expandAniRenderCenter(HDC hdc, int destX, int destY, animation* ani, float sizeX, float sizeY)
{
	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX - (sizeX * ani->getFrameWidth()) / 2,
		destY - (sizeY * ani->getFrameHeight()) / 2,
		ani->getFrameWidth() * sizeX,
		ani->getFrameHeight() * sizeY,
		_imageInfo->hMemDC,
		ani->getFramePos().x,
		ani->getFramePos().y,
		ani->getFrameWidth(),
		ani->getFrameHeight(),
		_transColor
	);
}

void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_trans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			centerX, centerY,
			_imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_trans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		//
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);

		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, _imageInfo->currentFrameX, _imageInfo->currentFrameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

