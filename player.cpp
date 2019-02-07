#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{

	IMAGEMANAGER->addFrameImage("player", "image/player.bmp", 0, 0, 1008, 2821, 12, 31, true, RGB(255,0, 255));
	IMAGEMANAGER->addFrameImage("ark_obj", "image/player_obj.bmp", 0, 0, 1540, 800, 10, 10, true, RGB(255, 0, 255));

	int idleLeft[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleLeft", "player", idleLeft, 1, 3, true);
	int idleRight[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleRight", "player", idleRight, 1, 3, true);
	int idleUp[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleUp", "player", idleUp, 1, 3, true);
	int idleDown[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleDown", "player", idleDown, 1, 3, true);
	int idleAction[] = {4, 5, 6, 7, 6, 7, 5, 4};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleAction", "player", idleAction, 8, 3, true);
	int moveLeft[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveLeft", "player", moveLeft, 6, 3, true);

	_player.ani = KEYANIMANAGER->findAnimation("ark", "idleLeft");


	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_player.ani->start();
}

void player::render()
{
	//_player.ani->re
}
