#include "stdafx.h"
#include "IntroDungeon.h"


IntroDungeon::IntroDungeon()
{
}


IntroDungeon::~IntroDungeon()
{
}

HRESULT IntroDungeon::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	IMAGEMANAGER->addImage("dungeonBackground", "image/introDungeonBackground.bmp", GAMESIZEX, GAMESIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dungeon", "image/introDungeon.bmp", 1024, 2490 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door", "image/문.bmp", 4165, 392, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("guardian", "image/가디언.bmp", 3135, 166, 33, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixelMap", "image/introDungeonPixel.bmp", 1024, 2490, true, RGB(255, 0 ,255));

	_camera = new camera;
	_player = new player;

	_camera->init(GAMESIZEX, GAMESIZEY, GAMESIZEX, 2490);
	_player->init();

	_door = IMAGEMANAGER->findImage("door");
	_guardian = IMAGEMANAGER->findImage("guardian");

	int doorClosed[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("doorAnime", "doorClosed", "door", doorClosed, 1, 10, false);
	int doorOpen[] = { 0, 1, 2, 3, 4, 5, 6, 7 , 8, 9, 10, 11, 12, 13, 14, 15, 16};
	KEYANIMANAGER->addArrayFrameAnimation("doorAnime", "doorOpen", "door", doorOpen, 17, 10, false);

	int guardianClocking[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("guardianAnime", "guardianClocking", "guardian", guardianClocking, 1, 5, true);
	int guardianComeOn[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 , 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("guardianAnime", "guardianComeOn", "guardian", guardianComeOn, 30, 20, false);
	int guardianOut[] = { 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	KEYANIMANAGER->addArrayFrameAnimation("guardianAnime", "guardianOut", "guardian", guardianOut, 30, 20, false);
	int guardianIdle[] = { 29 };
	KEYANIMANAGER->addArrayFrameAnimation("guardianAnime", "guardianIdle", "guardian", guardianIdle, 1, 5, true);
	int guardianTalk[] = { 29, 30, 31, 32 };
	KEYANIMANAGER->addArrayFrameAnimation("guardianAnime", "guardianTalk", "guardian", guardianTalk, 4, 5, true);

	_count = 0;
	_doorDirection = 0;
	_doorPos.x = GAMESIZEX / 2 - 105;
	_doorPos.y = 1675;
	_guardianDirection = GUARDIAN_CLOCKING;

	_player->setPlayerPosX(GAMESIZEX / 2 + 20);
	_player->setPlayerPosY(2300);
	_player->setPlayerState(PLAYER_IDLE);
	_player->setPlayerDirection(UP);
	_player->setPlayerUnMove(true);

	_dungeonGo = false;

	_playerSizeX = _playerSizeY = 1;

	_dungeonPos.x = GAMESIZEX / 2;
	_dungeonPos.y = GAMESIZEY / 2;

	_probeX = _player->getPlayerX() - (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2;
	
	//_camera->linearKeepMove(_dungeonPos.x, 2490 - GAMESIZEY / 2, 2, 100000);

	_playerAccept = _guardianTalk = _doorOpen = false;
	_guardianOn = false;
	_playerSizeChange = false;

	_introDungeonPlayerRc = RectMakeCenter(_player->getPlayerX(), _player->getPlayerY(), 40, 50);

	_escapeRc = RectMakeCenter(GAMESIZEX / 2, 1950, 200, 100);
	_escape = false;

	_camera->linearKeepMove(_dungeonPos.x, 2490 - GAMESIZEY / 2, 0.1f, 100000);
	return S_OK;
}

void IntroDungeon::release()
{
}

void IntroDungeon::update()
{
	
	_camera->update(0, 0);

	_count++;
	if(_count < 250)
	{
		_camera->linearKeepMove(_dungeonPos.x, 2490 - GAMESIZEY / 2, 2, 100000);
	}
	
	
	if (!_playerAccept)
	{
		if (_camera->getCameraY() == 1722 && !_guardianOn)
		{
			_guardianDirection = GUARDIAN_COMEON;
			if (KEYANIMANAGER->findAnimation("guardianAnime", "guardianComeOn")->getFramePosArrOnce() == 29)
			{
				_guardianOn = true;
			}
		}
		else if (_guardianTalk)
		{
			_guardianDirection = GUARDIAN_TALK;
		}
		else if (!_guardianTalk && _guardianOn) _guardianDirection = GUARDIAN_IDLE;
	}
	else if (_playerAccept)
	{
		_guardianDirection = GUARDIAN_OUT;
		if (KEYANIMANAGER->findAnimation("guardianAnime", "guardianOut")->getFramePosArrOnce() == 1)
		{
			_doorDirection = 1;
		}
	}
	
	

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if(!_guardianTalk) _guardianTalk = true;
		else  _guardianTalk = false;
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (!_playerAccept) _playerAccept = true;
		else _playerAccept = false;
	}


	switch (_guardianDirection)
	{
	case GUARDIAN_CLOCKING:
		_guardianAni = KEYANIMANAGER->findAnimation("guardianAnime", "guardianClocking");
		_guardianAni->start();
		break;
	case GUARDIAN_COMEON:
		_guardianAni = KEYANIMANAGER->findAnimation("guardianAnime", "guardianComeOn");
		_guardianAni->start();
		break;
	case GUARDIAN_OUT:
		_guardianAni = KEYANIMANAGER->findAnimation("guardianAnime", "guardianOut");
		_guardianAni->start();
		break;
	case GUARDIAN_IDLE:
		_guardianAni = KEYANIMANAGER->findAnimation("guardianAnime", "guardianIdle");
		_guardianAni->start();
		break;
	case GUARDIAN_TALK:
		_guardianAni = KEYANIMANAGER->findAnimation("guardianAnime", "guardianTalk");
		_guardianAni->start();
		break;
	}

	switch (_doorDirection)
	{
	case 0:
		_doorAni = KEYANIMANAGER->findAnimation("doorAnime", "doorClosed");
		_doorAni->start();
		break;
	case 1:
		_doorAni = KEYANIMANAGER->findAnimation("doorAnime", "doorOpen");
		_doorAni->start();
		break;
	}

	if (_doorDirection == 1 && !_playerSizeChange)
	{
		_player->setPlayerUnMove(false);
	}
	_player->update(0, 0);


	_probeX = _player->getPlayerX() + 28;
	for (int i = _probeX + 50; i > _probeX - 50; i--)
	{
		if (_player->getPlayerDirection() == LEFT || _player->getPlayerDirection() == UP || _player->getPlayerDirection() == DOWN)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixelMap")->getMemDC(), i, _player->getPlayerY());

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_player->setPlayerPosX(i + 20);
				break;
			}
		}
		else
		{
			break;
		}
	}
	_probeX = _player->getPlayerX() - 60;
	for (int i = _probeX - 50; i < _probeX + 50; i++)
	{
		if (_player->getPlayerDirection() == RIGHT || _player->getPlayerDirection() == UP || _player->getPlayerDirection() == DOWN)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixelMap")->getMemDC(), i, _player->getPlayerY());

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->setPlayerPosX(i + 10);
				break;
			}
		}
		else
		{
			break;
		}
	}
	
	RECT rc;
	if (IntersectRect(&rc, &_introDungeonPlayerRc, &_escapeRc) && _player->getPlayerDirection() == UP)
	{
		_player->setPlayerUnMove(true);
		_player->setPlayerState(PLAYER_WALK);

		_playerSizeChange = true;

		if (_playerSizeX > 0 || _playerSizeY > 0)
		{
			_playerSizeX -= 0.01;
			_playerSizeY -= 0.01;
		}
		else
		{
			_dungeonGo = true;
		}
	}

	_escapeRc = RectMakeCenter(GAMESIZEX / 2 + 20 - _camera->getCameraX(), 1925 - _camera->getCameraY(), 200, 100);
	_introDungeonPlayerRc = RectMakeCenter(_player->getPlayerX() - _camera->getCameraX(), _player->getPlayerY() + 10 - _camera->getCameraY(), 40, 50);
}

void IntroDungeon::render()
{
	IMAGEMANAGER->findImage("dungeonBackground")->render(getMemDC());
	IMAGEMANAGER->findImage("dungeon")->render(getMemDC(), 0, 0, _camera->getCameraX(), _camera->getCameraY(), GAMESIZEX, GAMESIZEY);
	//IMAGEMANAGER->findImage("pixelMap")->render(getMemDC(), 0, 0, _camera->getCameraX(), _camera->getCameraY(), GAMESIZEX, GAMESIZEY);

	_door->aniRender(getMemDC(), _doorPos.x - _camera->getCameraX(), _doorPos.y - _camera->getCameraY(), _doorAni);

	if (_doorDirection == 0)
	{
		_guardian->aniRender(getMemDC(), (_doorPos.x + 75) - _camera->getCameraX(), (_doorPos.y + 200) - _camera->getCameraY(), _guardianAni);
	}

	
	if (!_playerSizeChange)
	{
		_player->render(_camera->getCameraX(), _camera->getCameraY());
	}
	else
	{
		IMAGEMANAGER->findImage("player")->expandAniRenderCenter(getMemDC(), _player->getPlayerX() - _camera->getCameraX(),
			_player->getPlayerY() - _camera->getCameraY(), _player->getPlayerAni(), _playerSizeX, _playerSizeY);
	}
	//Rectangle(getMemDC(), _escapeRc);
	//Rectangle(getMemDC(), _introDungeonPlayerRc);

	char str[128];
	sprintf_s(str, "%d", _dungeonGo);
	TextOut(getMemDC(), 100, 80, str, strlen(str));

	//sprintf_s(str, "플레이어X :%f, 플레이어Y : %f", _player->getPlayerX(), _player->getPlayerY());
	//TextOut(getMemDC(), 120, 100, str, strlen(str));
}

void IntroDungeon::setWindowsSize(int x, int y, int width, int height)
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
