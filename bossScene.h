#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include "dungeonMap.h"
#include "camera.h"
#include "ItemManager.h"
#include "fireMonsterBullet.h"

class bossScene : public gameNode
{
private:
	enemyManager* _enemyManager;
	player* _player;
	camera* _camera;

	dungeonMap* _dungeonBossMap;
	ItemManager* _itemManager;


public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();


	void setWindowsSize(int x, int y, int width, int height);
};

