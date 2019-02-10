#pragma once
#include "enemy.h"

class knightMonster : public enemy
{
public:
	knightMonster();
	~knightMonster();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY, int hp);
	virtual void release();
	virtual void update(float cameraX, float cameraY);
	virtual void render(float viewX, float viewY);

	void move();
	void attack();

	static void cbAttack(void* obj); //공격후 다른모션으로 돌아가기 위한 콜백함수

public:
	//접근자 설정자 모음

};

