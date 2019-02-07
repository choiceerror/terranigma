#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(string enemyName, const char* imageName, float x, float y, int idX, int idY)
{
	_enemy.name = enemyName;
	_enemy.x = x;
	_enemy.y = y;
	_enemy.viewX = x;
	_enemy.viewY = y;
	_enemy.idX = idX;
	_enemy.idY = idY;
	_enemy.image = IMAGEMANAGER->findImage(imageName);
	_enemy.speed = 1;

	_enemy.rc = RectMake(x, y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());

	return S_OK;
}

void enemy::release()
{
}

void enemy::update(float cameraX, float cameraY)
{
	enemyMove(cameraX, cameraY);
}

void enemy::render(float viewX, float viewY)
{
	
}

void enemy::enemyMove(float cameraX, float cameraY)
{
	_enemy.viewX = _enemy.x - cameraX;
	_enemy.viewY = _enemy.y - cameraY;
	_enemy.rc = RectMake(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
}
