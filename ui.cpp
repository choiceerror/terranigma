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
	SetWindowPos(_hWnd, NULL, 0, 0,
		GAMESIZEX,
		GAMESIZEY,
		SWP_NOZORDER | SWP_NOMOVE);

	IMAGEMANAGER->addFrameImage("UI", "image/UI.bmp", 4000, 800, 4, 1, true, MAGENTA);


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
