#include "stdafx.h"
#include "boss.h"


boss::boss()
{
}


boss::~boss()
{
}

HRESULT boss::init(string enemyName, const char * imageName, float x, float y, int idX, int idY, int hp)
{
	enemy::init(enemyName, imageName, x, y, idX, idY, hp);
	_enemy.name = enemyName;
	_enemy.currentHP = _enemy.maxHP = hp;

	_enemy.state = BOSS_STATE_MOVE;

	int move[] = {0, 1, 2, 3};
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "move", imageName, move, 4, 4, true);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "move");

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	enemy::update();
	move();
}

void boss::render(float cameraX, float cameraY)
{
	_enemy.viewX = _enemy.x - cameraX;
	_enemy.viewY = _enemy.y - cameraY;
	_enemy.image->expandAniRenderCenter(getMemDC(), _enemy.viewX, _enemy.viewY, _enemy.motion, 3.f, 3.f);
}

void boss::move()
{
	switch (_enemy.state)
	{
	case BOSS_STATE_IDLE:
	case BOSS_STATE_MOVE:
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "move");
		_enemy.motion->start();
		break;
	}

}
