#pragma once
#include "enemy.h"
enum MOVETYPE
{
	BASIC_MOVE_TYPE, //기본 움직임상태
	FOLLOW_MOVE_TYPE, //따라가는 움직임 상태
};

class ballMonster : public enemy
{
private:
	int _rndDirection; //랜덤으로 방향전환
	float _directionTime, _directionWorldTime;
	float _moveAngle;
	int _moveType;
public:
	ballMonster();
	~ballMonster();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update(float cameraX, float cameraY);
	virtual void render(float viewX, float viewY);

	void move();

public:
	//접근자 설정자 모음
	float getX() { return _enemy.x; }
	float getY() { return _enemy.y; }
	float getViewX() { return _enemy.viewX; }
	float getViewY() { return _enemy.viewY; }

	void setX(float x) { _enemy.x = x; }
	void setY(float y) { _enemy.y = y; }
	void setViewX(float viewX) { _enemy.viewX = viewX; }
	void setViewY(float viewY) { _enemy.viewY = viewY; }

	RECT getRangeRect() { return _enemy.rangeRc; }
	ENEMYDIRECTION getDirection() { return _enemy.direction; }
	void setDirection(ENEMYDIRECTION direction) { _enemy.direction = direction; }
	float getMoveAngle() {return _moveAngle;}
};

