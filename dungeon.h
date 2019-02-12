#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include "dungeonMap.h"
#include "camera.h"

class dungeon : public gameNode
{
private:
	enemyManager* _enemyManager;
	player* _player;
	camera* _camera;

	dungeonMap* _dungeon;

	DWORD* _attribute;

public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);


};

