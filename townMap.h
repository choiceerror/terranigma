#pragma once
#include "gameNode.h"
#include "mapTool.h"

class townMap : public gameNode
{
	mapTool* _mapT;

	vector<vector<tagTile*>> _vvMap;
	unsigned int TILEX;
	unsigned int TILEY;

	DWORD* _attribute;

	int tix;
	int tiy;
	int obx;
	int oby;

public:
	townMap();
	~townMap();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);
	void load();
	void tileDraw();

	unsigned int getTileX() { return TILEX; }
	unsigned int getTileY() { return TILEY; }

	tagTile* getTile(int x, int y) { return _vvMap[y][x]; }
	DWORD getAttr(int x, int y) { return _attribute[x + y * TILEX]; }
};

