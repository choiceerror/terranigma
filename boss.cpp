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

	_attackCount = 0;
	_enemy.state = BOSS_STATE_IDLE;

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
	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.image->getFrameWidth(), _enemy.image->getFrameHeight() + 100);
}

void boss::render(float cameraX, float cameraY)
{
	_enemy.viewX = _enemy.x - cameraX;
	_enemy.viewY = _enemy.y - cameraY;
	_enemy.image->expandAniRenderCenter(getMemDC(), _enemy.viewX, _enemy.viewY, _enemy.motion, 3.f, 3.f);
	Rectangle(getMemDC(), _enemy.rc.left - cameraX, _enemy.rc.top - cameraY, _enemy.rc.right - cameraX, _enemy.rc.bottom - cameraY);
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

	if (_enemy.isHit == true)
	{
		_attackCount++;
		if (_attackCount >= 30)
		{
			_enemy.isHit = false;
			_attackCount = 0;
		}
	}

}

bool boss::countAttack()
{
	_attackCount++;
	if (_attackCount % 50 == 0)
	{
		_attackCount = 0;
		return true;
	}

	return false;
}

