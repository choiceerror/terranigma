#pragma once
#include "gameNode.h"

enum ENEMYDIRECTION
{
	//공몬스터 상태
	BALLMONSTER_LEFT_IDLE,
	BALLMONSTER_RIGHT_IDLE,
	BALLMONSTER_UP_IDLE,
	BALLMONSTER_DOWN_IDLE,
	BALLMONSTER_LEFT_MOVE,
	BALLMONSTER_RIGHT_MOVE,
	BALLMONSTER_UP_MOVE,
	BALLMONSTER_DOWN_MOVE,
	BALLMONSTER_LEFT_ATTACK,
	BALLMONSTER_RIGHT_ATTACK,
	BALLMONSTER_UP_ATTACK,
	BALLMONSTER_DOWN_ATTACK,

	//불몬스터 상태
	FIREMONSTER_IDLE,
	FIREMONSTER_DEAD,
	FIREMONSTER_LEFT_MOVE,
	FIREMONSTER_RIGHT_MOVE,
	FIREMONSTER_UP_MOVE,
	FIREMONSTER_DOWN_MOVE,
	FIREMONSTER_LEFT_ATTACK,
	FIREMONSTER_RIGHT_ATTACK,
	FIREMONSTER_UP_ATTACK,
	FIREMONSTER_DOWN_ATTACK,

	//나이트몬스터 상태
	KNIGHTMONSTER_LEFT_IDLE,
	KNIGHTMONSTER_RIGHT_IDLE,
	KNIGHTMONSTER_UP_IDLE,
	KNIGHTMONSTER_DOWN_IDLE,
	KNIGHTMONSTER_LEFT_MOVE,
	KNIGHTMONSTER_RIGHT_MOVE,
	KNIGHTMONSTER_UP_MOVE,
	KNIGHTMONSTER_DOWN_MOVE,
	KNIGHTMONSTER_LEFT_ATTACK,
	KNIGHTMONSTER_RIGHT_ATTACK,
	KNIGHTMONSTER_UP_ATTACK,
	KNIGHTMONSTER_DOWN_ATTACK,

	//보스상태
	BOSS_ATTACK,
};

struct tagEnemy
{
	RECT rc;
	float x, y;
	float viewX, viewY;
	int idX, idY;
	float speed;
	image* image;
	ENEMYDIRECTION direction;
	string name;
	animation* motion;
	float damage;
};

class enemy : public gameNode
{
protected:
	tagEnemy _enemy;

public:
	enemy();
	~enemy();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update(float cameraX, float cameraY);
	virtual void render(float viewX, float viewY);

	virtual void enemyMove(float cameraX, float cameraY);
};

