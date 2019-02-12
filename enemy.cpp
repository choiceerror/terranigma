#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(string enemyName, const char* imageName, float x, float y, int idX, int idY, int hp)
{
	_enemy.name = enemyName;
	_enemy.x = x;
	_enemy.y = y;
	_enemy.viewX = x;
	_enemy.viewY = y;
	_enemy.idX = idX;
	_enemy.idY = idY;
	_enemy.image = IMAGEMANAGER->findImage(imageName);
	_enemy.speed = 1.0f;
	_enemy.moveType = BASIC_MOVE_TYPE; //처음엔 기본움직임상태로
	_enemy.currentHP = _enemy.maxHP = hp;
	_enemy.isAttack = false; //처음엔 비공격상태
	_enemy.worldTime = TIMEMANAGER->getWorldTime();
	_enemy.attackWorldTime = TIMEMANAGER->getWorldTime();
	_enemy.alphaValue = 255;
	_directionTime = 2.0f;
	_directionWorldTime = TIMEMANAGER->getWorldTime();

	_enemy.rc = RectMakeCenter(x, y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	enemyMove();
}

void enemy::render(float cameraX, float cameraY)
{
	
}

void enemy::enemyMove()
{
	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight());
}
