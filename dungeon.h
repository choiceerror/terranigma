#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include "MapNode.h"

class dungeon : public gameNode
{
private:
	enemyManager* _enemyManager;
	player* _player;

	vector<vector<tagTile*>> _vvMap;
	unsigned int TILEX;
	unsigned int TILEY;

	DWORD* _attribute;

public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();
	void load();
	void tileDraw();

	void setWindowsSize(int x, int y, int width, int height);

	unsigned int getTileX() { return TILEX; }
	unsigned int getTileY() { return TILEY; }

	tagTile* getTile(int x, int y) { return _vvMap[y][x]; }
	DWORD getAttr(int x, int y) { return _attribute[x + y * TILEX]; }
};

