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
	RECT _dungeonDown;

	int _alphaValue;
	bool _isAlphaOut;
	bool _isAlphaOn;
	bool _isFireAlphaOn;

	bool _isDungeonDown;
	float _worldTime;
	bool _once;

	int _fireAlphaValue;
	int _fireIndex;
	bool _fireWallOn;

	int _count;
	float _tum;

	float _playerDeadAlpha;
	bool _isPlayerDeadAlphaOn;

	bool _soundOnce;

public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void bossAppear();
	void dungeonChange();
	void alphaBlend();

	void playerUnAttack();
	void playerUnDown();

	void playerSceneSave();
	void playerSceneLoad();

	void playerDead();

	void setWindowsSize(int x, int y, int width, int height);
};

