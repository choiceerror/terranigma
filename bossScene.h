#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include "dungeonMap.h"
#include "camera.h"
#include "ItemManager.h"

enum ONCE //한번만 받기위함.
{
	LINEAR,
	CAMERA_LINEAR,
	BOSS_APPEAR,
};

class bossScene : public gameNode
{
private:
	enemyManager* _enemyManager;
	player* _player;
	camera* _camera;

	dungeonMap* _dungeonBossMap;
	ItemManager* _itemManager;

	float _worldTime;
	bool _isBossAppear; //보스 등장시점 판별해줄 불값
	bool _isOnce[3]; //업데이트부분에 한번만 받기위함.
	
	POINTFLOAT _goal;
	float _goalAngle;
	float _elapsedTime;
	float _goalDistance;
	float _moveSpeed;

	POINTFLOAT _moveGoal[10];
	float _moveGoalAngle;

public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void bossAppear(); //보스 등장
	void movePattern(); //보스 무브패턴

	void setWindowsSize(int x, int y, int width, int height);
};

