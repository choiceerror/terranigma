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

	IMAGEMANAGER->addFrameImage("yomi", "image/NPC_yomi.bmp", 275, 112, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UI", "image/UI.bmp", 4096, 768, 4, 1, true, MAGENTA);

	_frameX = 0;

	return S_OK;
}

void ui::release()
{
}

void ui::update()
{
}

void ui::render()
{
	IMAGEMANAGER->frameRender("UI", getMemDC(), 0, 0, _frameX, 0);



}

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
