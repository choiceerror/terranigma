#include "stdafx.h"
#include "knightMonster.h"


knightMonster::knightMonster()
{
}


knightMonster::~knightMonster()
{
}

HRESULT knightMonster::init(string enemyName, const char * imageName, float x, float y, int idX, int idY)
{
	enemy::init(enemyName, imageName, x, y, idX, idY);
	_enemy.name = enemyName;

	_enemy.direction = KNIGHTMONSTER_DOWN_MOVE;

	int downMove[] = { 0, 1, 2, 3, 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downMove", imageName, downMove, 5, 4, true);

	int upMove[] = { 7, 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upMove", imageName, upMove, 5, 4, true);

	int leftMove[] = { 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftMove", imageName, leftMove, 4, 4, true);

	int rightMove[] = { 21, 22, 23, 24 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightMove", imageName, rightMove, 4, 4, true);

	int downAttack[] = { 28, 29, 30, 31, 32, 33, 34 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "downAttack", imageName, downAttack, 7, 4, false, cbAttack, this);

	int upAttack[] = { 35, 36, 37, 38, 39 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "upAttack", imageName, upAttack, 5, 4, false, cbAttack, this);

	int leftAttack[] = { 42, 43, 44, 45, 46, 47, 48 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "leftAttack", imageName, leftAttack, 7, 4, false, cbAttack, this);

	int rightAttack[] = { 49, 50, 51, 52, 53, 54, 55 };
	KEYANIMANAGER->addArrayFrameAnimation(_enemy.name, "rightAttack", imageName, rightAttack, 7, 3, false, cbAttack, this);

	_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downMove");

	return S_OK;
}

void knightMonster::release()
{
}

void knightMonster::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);
	move();
}

void knightMonster::render(float viewX, float viewY)
{
	_enemy.image->aniRender(getMemDC(), viewX, viewY, _enemy.motion);
}

void knightMonster::move()
{

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_enemy.direction = KNIGHTMONSTER_DOWN_ATTACK;
	}
	else if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_enemy.direction = KNIGHTMONSTER_LEFT_ATTACK;
	}
	switch (_enemy.direction)
	{
	case KNIGHTMONSTER_DOWN_MOVE:
		_enemy.direction = KNIGHTMONSTER_DOWN_MOVE;
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downMove");
		_enemy.motion->start();
		break;
	case KNIGHTMONSTER_UP_MOVE:
		_enemy.direction = KNIGHTMONSTER_UP_MOVE;
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "upMove");
		_enemy.motion->start();
		break;
	case KNIGHTMONSTER_RIGHT_MOVE:
		_enemy.direction = KNIGHTMONSTER_RIGHT_MOVE;
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "rightMove");
		_enemy.motion->start();
		break;
	case KNIGHTMONSTER_LEFT_MOVE:
		_enemy.direction = KNIGHTMONSTER_LEFT_MOVE;
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "leftMove");
		_enemy.motion->start();
		break;
	case KNIGHTMONSTER_DOWN_ATTACK:
		_enemy.direction = KNIGHTMONSTER_DOWN_ATTACK;
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "downAttack");
		_enemy.motion->start();
		break;
	case KNIGHTMONSTER_LEFT_ATTACK:
		_enemy.direction = KNIGHTMONSTER_LEFT_ATTACK;
		_enemy.motion = KEYANIMANAGER->findAnimation(_enemy.name, "leftAttack");
		_enemy.motion->start();
		break;
	}
}

void knightMonster::cbAttack(void * obj)
{
	knightMonster* k = (knightMonster*)obj;

	if (k->getDirection() == KNIGHTMONSTER_DOWN_ATTACK)
	{
		k->setDirection(KNIGHTMONSTER_DOWN_MOVE);
		k->setMotion(KEYANIMANAGER->findAnimation(k->getName(), "downMove"));
		k->getMotion()->start();
	
	}
	else if (k->getDirection() == KNIGHTMONSTER_UP_ATTACK)
	{
		k->setDirection(KNIGHTMONSTER_UP_MOVE);
		k->setMotion(KEYANIMANAGER->findAnimation(k->getName(), "upMove"));
		k->getMotion()->start();
	}
	else if (k->getDirection() == KNIGHTMONSTER_RIGHT_ATTACK)
	{
		k->setDirection(KNIGHTMONSTER_RIGHT_MOVE);
		k->setMotion(KEYANIMANAGER->findAnimation(k->getName(), "rightMove"));
		k->getMotion()->start();
	}
	else if (k->getDirection() == KNIGHTMONSTER_LEFT_ATTACK)
	{
		k->setDirection(KNIGHTMONSTER_LEFT_MOVE);
		k->setMotion(KEYANIMANAGER->findAnimation(k->getName(), "leftMove"));
		k->getMotion()->start();
	}
}
