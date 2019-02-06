#include "stdafx.h"
#include "backBuffer.h"


backBuffer::backBuffer()
	: _backBuffer(NULL)
{
}


backBuffer::~backBuffer()
{
}

HRESULT backBuffer::init(int width, int height)
{
	//백버퍼가 생성되어 있으면 == 뭔가가 데이터가 남아있으면 해제를 시킨다.
	if (_backBuffer != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_backBuffer = new BACKBUFFER_INFO;
	_backBuffer->hMemDC = CreateCompatibleDC(hdc); //새로운 빈 DC공간을 생성해준다.
	_backBuffer->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_backBuffer->hOBit = (HBITMAP)SelectObject(_backBuffer->hMemDC, _backBuffer->hBit);
	_backBuffer->width = width;
	_backBuffer->height = height;

	if(_backBuffer->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void backBuffer::release()
{
	if (_backBuffer)
	{
		SelectObject(_backBuffer->hMemDC, _backBuffer->hOBit);
		DeleteObject(_backBuffer->hBit);
		DeleteDC(_backBuffer->hMemDC);

		SAFE_DELETE(_backBuffer);
	}
}

void backBuffer::render(HDC hdc, int destX, int destY)
{
	//DC 영역 간 고속복사 함수
	BitBlt(
		hdc,					//복사할 DC
		destX,					//복사할
		destY,					//복사할
		_backBuffer->width,		//복사할 크기 (가로크기)
		_backBuffer->height,	//복사할 크기 (세로크기)
		_backBuffer->hMemDC,	//복사될 DC
		0, 0,					//복사될 좌표 X, Y
		SRCCOPY);				//변형없이 복사한다.
}
