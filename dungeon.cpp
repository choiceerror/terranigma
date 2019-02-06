#include "stdafx.h"
#include "dungeon.h"


dungeon::dungeon()
{
}


dungeon::~dungeon()
{
}

HRESULT dungeon::init()
{
	IMAGEMANAGER->addFrameImage("ballMonster", "image/enemy1.bmp", 64, 64, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fireMonster", "image/enemy2.bmp", 90, 87, 5, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("knightMonster", "image/enemy3.bmp", 910, 800, 7, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss", "image/º¸½º.bmp", 1048, 239, 4, 1, true, RGB(255, 0, 255));

	_ballMonster = new ballMonster;
	_ballMonster->init("ball", "ballMonster", 100, 100, 1, 1);

	_fireMonster = new fireMonster;
	_fireMonster->init("fire", "fireMonster", 200, 200, 2, 2);
	return S_OK;
}

void dungeon::release()
{
}

void dungeon::update()
{
	_ballMonster->update(0, 0);
	_fireMonster->update(0, 0);
}

void dungeon::render()
{
	_ballMonster->render(_ballMonster->getViewX(), _ballMonster->getViewY());
	_fireMonster->render(100, 100);
}
