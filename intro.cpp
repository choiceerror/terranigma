#include "stdafx.h"
#include "intro.h"


intro::intro()
{
}


intro::~intro()
{
}

HRESULT intro::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	_camera = new camera;

	_camera->init(GAMESIZEX, GAMESIZEY, WINSIZEX, GAMESIZEY);

	IMAGEMANAGER->findImage("black")->setAlpahBlend(true);

	_intro.image = IMAGEMANAGER->findImage("인트로1");

	_intro.alphaValue = 255;
	_intro.padeIn = _intro.padeOut = _intro.isIntroImageShow = false;

	_intro.cameraPos.x = WINSIZEX / 2;
	_intro.cameraPos.y = 0;

	return S_OK;
}

void intro::release()
{
	SAFE_DELETE(_camera);
}

void intro::update()
{

	opening();


	//이미지가 보여지면
	if (_intro.isIntroImageShow == true)
	{
		_intro.cameraPos.x -= 2;
		if (_intro.cameraPos.x <= 0)
		{
			_intro.cameraPos.x = 0;
			_intro.isIntroImageShow = false; //카메라 끝에 도달았으면 더이상 못들어오게
		}
	}
	
	_camera->update(_intro.cameraPos.x, _intro.cameraPos.y);
	
}

void intro::render()
{
	_intro.image->render(getMemDC(), 0, 0, _intro.cameraPos.x - _camera->getCameraX(), _intro.cameraPos.y - _camera->getCameraY(), GAMESIZEX, GAMESIZEY);

	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), _intro.alphaValue);

	char str[128];

	sprintf_s(str, "alpha : %d", _intro.alphaValue);
	TextOut(getMemDC(), 100, 100, str, strlen(str));

	sprintf_s(str, "show : %d", _intro.isIntroImageShow);
	TextOut(getMemDC(), 100, 120, str, strlen(str));

	sprintf_s(str, "cameraX : %f", _intro.cameraPos.x);
	TextOut(getMemDC(), 100, 140, str, strlen(str));
}

void intro::opening()
{
	if (_intro.alphaValue > 0)
	{
		_intro.alphaValue -= 1;
	}
	else if (_intro.alphaValue <= 0)
	{
		_intro.alphaValue = 0;
		_intro.isIntroImageShow = true;
	}



}

void intro::messageAll()
{
	string* message;
	message = new string;

	message[0] = "그 별은 가지고 있었다 두개의 마음을";
	message[1] = "밝은면과 어두운면의 두개의 얼굴이었다.....";
	message[2] = "이별이 태어난 후 46억년의 세월은..";
	message[3] = "커다란 두개의 의지에 의해 진화와 쇠퇴를 반복하고 있다.";
	message[4] = "밝은 면의 의지로 새로운 생명이 태어나고,";
	message[5] = "어두운 면의 의지로 빙하기가 온다.";
	message[6] = "밝은 면으로 새로운 기술이 만들어지고,";
	message[7] = "세월이 지난다음...";
	message[8] = "어두운 면의 의지에 의해 그 희생자가 나온다..";
	message[9] = "인류는 그 두개의 의지를 신과 악마 라고 불렀다";

	_vMessage.push_back(message);
	//TXTDATA->txtSave("messageFile/인트로.txt", &_vMessage);
	
}

void intro::messageDraw(const char* txtName)
{
}

void intro::setWindowsSize(int x, int y, int width, int height)
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
