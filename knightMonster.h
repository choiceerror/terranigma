#pragma once
#include "enemy.h"
class knightMonster : public enemy
{
public:
	knightMonster();
	~knightMonster();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update(float cameraX, float cameraY);
	virtual void render(float viewX, float viewY);

	void move();

	static void cbAttack(void* obj);

public:
	//접근자 설정자 모음
	float getX() { return _enemy.x; }
	float getY() { return _enemy.y; }
	float getViewX() { return _enemy.viewX; }
	float getViewY() { return _enemy.viewY; }

	ENEMYDIRECTION getDirection() { return _enemy.direction; }
	void setDirection(ENEMYDIRECTION direction) { _enemy.direction = direction; }

	animation* getMotion() { return _enemy.motion; }
	void setMotion(animation* motion) { _enemy.motion = motion; }

	string getName() { return _enemy.name; }
};

