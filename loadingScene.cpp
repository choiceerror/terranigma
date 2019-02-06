#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
	: _background(nullptr), _loadingBar(nullptr),
	_currentCount(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("로딩배경", "드래곤즈크라운.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);

	//싱글쓰레드를 사용한 로딩처리

	CreateThread
	(
		NULL,			//스레드의 보안속성(자식윈도우가 있을때) 핸들로 자식인지 부모인지 여부파악
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드와 스택크기는 동일)
		ThreadFunction,	//스레드 함수 명
		this,			//스레드의 매개변수 (this로 하면 본 클래스)
		NULL,			//스레드의 특성(NULL로 두면 바로 실행함)
		0				//스레드의 생성 후 스레드의 ID를 넘겨준다 보통은 NULL로 둠.
	);


	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("인게임씬");
	}


}

void loadingScene::render()
{
	_background->render(getMemDC(), 0, 0);
	_loadingBar->render();
}

DWORD CALLBACK ThreadFunction(LPVOID lpParameter)
{
	loadingScene* loadHelper = (loadingScene*)lpParameter;

	//로딩맥스가 1000이기 때문에 이미지는 임의로 1000개만 돌려봅시다
	while (loadHelper->_currentCount != LOADINGMAX)
	{
		IMAGEMANAGER->addImage("인게임", "캐릭터.bmp", 580, 565, false, RGB(0, 0, 0));
		Sleep(1); //이거 없으면 천장이고 뭐고 후다다닥 해버림

		loadHelper->_currentCount++;
	}

	return 0;
}
