#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"
#include "knightMonster.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
private:
	vEnemy _vBallMonster;
	viEnemy _viBallMonster;

	vEnemy _vFireMonster;
	viEnemy _viFireMonster;

	vEnemy _vKnightMonster;
	viEnemy _viKnightMonster;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemy();
};

