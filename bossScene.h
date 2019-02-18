#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include "dungeonMap.h"
#include "camera.h"
#include "ItemManager.h"
#include "fireMonsterBullet.h"

enum ONCE //한번만 받기위함.
{
	LINEAR_APPEAR,
	CAMERA_LINEAR,
	BOSS_APPEAR,
	WORLDTIME,
};

enum class BULLET_PATTERN
{
	NONE,
	GOLD_BULLET,
	BLUE_BULLET,
	RED_BULLET,
};

enum ATTACK_PATTERN
{
	ATTACK_NONE,
	ATTACK_ONE,
	ATTACK_TWO,
	ATTACK_THREE,

};

class bossScene : public gameNode
{
private:
	enemyManager* _enemyManager;
	player* _player;
	camera* _camera;

	dungeonMap* _dungeonBossMap;
	ItemManager* _itemManager;
	bossBullet* _bossBullet;
	BULLET_PATTERN _bulletPattern; //총알 나가는 종류
	ATTACK_PATTERN _attackPattern; //공격종류

	float _worldTime;
	bool _isBossAppear; //보스 등장시점 판별해줄 불값
	bool _isOnce[4]; //업데이트부분에 한번만 받기위함.
	
	POINTFLOAT _appearGoal;
	float _goalAngle;
	float _elapsedTime;
	float _goalDistance;
	float _appearSpeed; //등장 스피드

	POINTFLOAT _moveGoal[4];

	float _goalX;
	float _goalY;
	float _moveWorldTime;
	float _rndMoveWorldTime;
	float _attackWorldTime[4];
	float _bulletWorldTime;

	int _rndAttack; //3개중에 한개나갈타입
	int _rndAttackType; //1개 어택중에 다르게 나갈타입.

	float _moveSpeed;
	int _rndMove;
	float _bulletSpeed;

public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void bossAppear(); //보스 등장
	void movePattern(); //보스 무브패턴
	void attackPattern(); //보스 공격패턴

	void setWindowsSize(int x, int y, int width, int height);
};

