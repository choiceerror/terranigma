#pragma once
#include "gameNode.h"
#define ATTACKFPS 5
#define MOVEFPS 5
//몬스터들의 방향
enum ENEMYDIRECTION
{
	//공몬스터 방향
	BALLMONSTER_DIRECTION_LEFT,
	BALLMONSTER_DIRECTION_RIGHT,
	BALLMONSTER_DIRECTION_UP,
	BALLMONSTER_DIRECTION_DOWN,

	//불몬스터 방향
	FIREMONSTER_DIRECTION_LEFT,
	FIREMONSTER_DIRECTION_RIGHT,
	FIREMONSTER_DIRECTION_UP,
	FIREMONSTER_DIRECTION_DOWN,


	//나이트몬스터 방향
	KNIGHTMONSTER_DIRECTION_LEFT,
	KNIGHTMONSTER_DIRECTION_RIGHT,
	KNIGHTMONSTER_DIRECTION_UP,
	KNIGHTMONSTER_DIRECTION_DOWN,

	//보스방향
	BOSS_DIRECTION_LEFT,
	BOSS_DIRECTION_RIGHT,
	BOSS_DIRECTION_UP,
	BOSS_DIRECTION_MOVE,
};
//몬스터들의 상태
enum ENEMYSTATE
{
	//공몬스터 상태
	BALLMONSTER_STATE_IDLE,
	BALLMONSTER_STATE_MOVE,
	BALLMONSTER_STATE_ATTACK,
	BALLMONSTER_STATE_DEAD,

	//불몬스터 상태
	FIREMONSTER_STATE_IDLE,
	FIREMONSTER_STATE_MOVE,
	FIREMONSTER_STATE_ATTACK,
	FIREMONSTER_STATE_DEAD,

	//나이트몬스터 상태
	KNIGHTMONSTER_STATE_IDLE,
	KNIGHTMONSTER_STATE_MOVE,
	KNIGHTMONSTER_STATE_ATTACK,
	KNIGHTMONSTER_STATE_DEAD,

	//보스 상태
	BOSS_STATE_IDLE,
	BOSS_STATE_MOVE,
	BOSS_STATE_ATTACK,
	BOSS_STATE_DEAD,

};

enum ENEMYMOVETYPE
{
	BASIC_MOVE_TYPE, //기본 움직임상태
	FOLLOW_MOVE_TYPE, //따라가는 움직임 상태
};

struct tagEnemy
{
	RECT rc;
	RECT attackRc; //공격렉트
	RECT rangeRc; //플레이어가 범위안에 들어올시 공격을할 판별해줄 렉트
	float x, y;
	float viewX, viewY;
	int idX, idY;
	float speed;
	image* image;
	ENEMYDIRECTION direction;
	ENEMYSTATE state;
	ENEMYMOVETYPE moveType;
	string name;
	animation* motion;
	int damage; //데미지
	int def; //방어력
	int currentHP, maxHP; //현재, 최대 체력
	float moveAngle; //움직임 각도
	float targetAngle;
	float targetDistance;
	bool isAttack;
	float attackAngle;
	float attackWorldTime;
	float worldTime;
	bool isOneTime;
	int tileIndex[2];
};

class enemy : public gameNode
{
protected:
	tagEnemy _enemy;
	int _rndDirection; //랜덤으로 방향전환
	int _rndState; //랜덤으로 상태전환
	float _directionTime, _directionWorldTime;

public:
	enemy();
	~enemy();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY, int hp);
	virtual void release();
	virtual void update();
	virtual void render(float viewX, float viewY, float cameraX, float cameraY);

	virtual void enemyMove();

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

	int getIdX() { return _enemy.idX; }
	int getIdY() { return _enemy.idY; }

	RECT getRect() { return _enemy.rc; }
	RECT getRangeRect() { return _enemy.rangeRc; }
	RECT getAttackRect() { return _enemy.attackRc; }

	ENEMYDIRECTION getDirection() { return _enemy.direction; }
	void setDirection(ENEMYDIRECTION direction) { _enemy.direction = direction; }

	ENEMYSTATE getState() {return _enemy.state;}
	void setState(ENEMYSTATE state) {_enemy.state = state;}

	void setMoveType(ENEMYMOVETYPE type) {_enemy.moveType = type;}
	float getMoveAngle() {return _enemy.moveAngle;}

	int getCurrentHP() {return _enemy.currentHP;}
	int getMaxHP() {return _enemy.maxHP;}

	void setCurrentHP(int hp) {_enemy.currentHP = hp;}
	void setMaxHP(int maxHp) {_enemy.maxHP = maxHp;}

	float getTargetAngle() {return _enemy.targetAngle;}
	void setTargetAngle(float angle) {_enemy.targetAngle = angle;}

	float getTargetDistance() {return _enemy.targetDistance;}
	void setTargetDistance(float distance) {_enemy.targetDistance = distance;}

	float getSpeed() {return _enemy.speed;}
	void setSpeed(float speed) { _enemy.speed = speed; }

	bool getIsAttack() { return _enemy.isAttack; }
	void setIsAttack(bool attack) { _enemy.isAttack = attack; }

	float getAttackAngle() { return _enemy.attackAngle; }
	void setAttackAngle(float angle) { _enemy.attackAngle = angle; }
	animation* getMotion() { return _enemy.motion; }
	void setMotion(animation* motion) { _enemy.motion = motion; }

	string getName() { return _enemy.name; }

	float getWorldTime() { return _enemy.worldTime; }
	float getAttackWorldTime() { return _enemy.attackWorldTime; }

	void setWorldTime(float worldTime) { _enemy.worldTime = worldTime; }
	void setAttackWorldTime(float attackWorldTime) { _enemy.attackWorldTime = attackWorldTime; }

	tagEnemy getEnemy() {return _enemy;}


	
};

