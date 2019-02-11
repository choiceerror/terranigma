#pragma once
#include "gameNode.h"
#include "MapNode.h"


class worldMap : public gameNode
{
private:

	vector<vector<tagTile*>> _vvMap;
	unsigned int TILEX;
	unsigned int TILEY;

	DWORD* _attribute;


	RECT rc;

public:
	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	unsigned int getTileX() { return TILEX; }
	unsigned int getTileY() { return TILEY; }

	tagTile* getTile(int x, int y) { return _vvMap[y][x]; }
	DWORD getAttr(int x, int y) { return _attribute[x + y * TILEX]; }
};

