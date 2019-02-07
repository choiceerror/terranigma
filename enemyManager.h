#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"
#include "knightMonster.h"

class enemyManager : public gameNode
{
private:
	//볼몬스터 벡터
	vector<ballMonster*> _vBallMonster;
	vector<ballMonster*>::iterator _viBallMonster;

	//파이어 몬스터 벡터
	vector<fireMonster*> _vFireMonster;
	vector<fireMonster*>::iterator _viFireMonster;

	//나이트 몬스터 벡터
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

