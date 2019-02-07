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
	IMAGEMANAGER->addFrameImage("knightMonster", "image/enemy_3.bmp", 910, 800, 7, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss", "image/º¸½º.bmp", 1048, 239, 4, 1, true, RGB(255, 0, 255));

	_enemyManager = new enemyManager;
	_enemyManager->init();
	_enemyManager->setEnemy();
	return S_OK;
}

void dungeon::release()
{
}

void dungeon::update()
{
	_enemyManager->update();
}

void dungeon::render()
{
	_enemyManager->render();
}
