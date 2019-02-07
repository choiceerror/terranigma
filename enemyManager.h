#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"
#include "knightMonster.h"

class enemyManager : public gameNode
{
private:
	vector<ballMonster*> _vBallMonster;
	vector<ballMonster*>::iterator _viBallMonster;

	vector<fireMonster*> _vFireMonster;
	vector<fireMonster*>::iterator _viFireMonster;

	vector<knightMonster*> _vKnightMonster;
	vector<knightMonster*>::iterator _viKnightMonster;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemy();

public:
	//접근자 설정자 모음
	vector<ballMonster*> getVBallMonster() {return _vBallMonster;}
	vector<ballMonster*>* setVBallMonster() {return &_vBallMonster;}

	vector<fireMonster*> getVFireMonster() {return _vFireMonster;}
	vector<fireMonster*>* setVFireMonster() {return &_vFireMonster;}

	vector<knightMonster*> getVKnightMonster() {return _vKnightMonster;}
	vector<knightMonster*>* setVKnightMonster() {return &_vKnightMonster;}
};

