#pragma once
#include "enemy.h"

class ballMonster : public enemy
{
private:
	int _rndDirection; //랜덤으로 방향전환
	float _directionTime, _directionWorldTime;

public:
	ballMonster();
	~ballMonster();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY, int hp);
	virtual void release();
	virtual void update(float cameraX, float cameraY);
	virtual void render(float viewX, float viewY);

	void move();

public:
	//접근자 설정자 모음
};

