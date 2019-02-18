#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include "dungeonMap.h"
#include "camera.h"
#include "ItemManager.h"
#include "ClockFadeOut.h"


class dungeon : public gameNode
{
private:
	enemyManager* _enemyManager;
	player* _player;
	camera* _camera;
	ClockFadeOut* _clockFade;

	dungeonMap* _dungeon;
	ItemManager* _itemManager;

	RECT _temp;
	RECT _dungeonDown;
	RECT _dungeonUp;

	int _rndItemDrop; //아이템 랜덤으로 드랍할것
	int _rndItemTypeDrop; //아이템 타입 랜덤으로 드랍할것.

	float _worldTime;
	float _once;
	int _alphaValue;
	bool _changeScene;

public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();

	void dungeonChange();
	void playerSceneSave();
	void playerSceneLoad();

	void itemRandomDrop(); //랜덤 아이템드랍
	void playerItemGet(); //플레이어 아이템 얻는 함수

	void setWindowsSize(int x, int y, int width, int height);
};

