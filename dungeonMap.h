#pragma once
#include "gameNode.h"
#include "mapTool.h"

class dungeonMap : public  gameNode
{

private:

	mapTool* _mapT;

	vector<vector<tagTile*>> _vvMap;
	unsigned int TILEX;
	unsigned int TILEY;

	DWORD* _attribute;

public:
	dungeonMap();
	~dungeonMap();

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

