#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		(*_viBallMonster)->update(0, 0);
	}
	for (_viKnightMonster = _vKnightMonster.begin(); _viKnightMonster != _vKnightMonster.end(); _viKnightMonster++)
	{
		(*_viKnightMonster)->update(0, 0);
	}
}

void enemyManager::render()
{
	for (_viBallMonster = _vBallMonster.begin(); _viBallMonster != _vBallMonster.end(); _viBallMonster++)
	{
		(*_viBallMonster)->render((*_viBallMonster)->getViewX(), (*_viBallMonster)->getViewY());
	}
	for (_viKnightMonster = _vKnightMonster.begin(); _viKnightMonster != _vKnightMonster.end(); _viKnightMonster++)
	{
		(*_viKnightMonster)->render((*_viKnightMonster)->getViewX(), (*_viKnightMonster)->getViewY());
	}
}

void enemyManager::setEnemy()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ballMonster* bm;
			bm = new ballMonster;

			bm->init("ball", "ballMonster", 100 + j * 100, 100 + i * 100, j, i);
			_vBallMonster.push_back(bm);

			knightMonster* km;
			km = new knightMonster;

			km->init("knight", "knightMonster", 100 + j * 100, 200 + i * 100, j, i);
			_vKnightMonster.push_back(km);
		}
	}
}
