#pragma once
#include "gameNode.h"
#include "mapTool.h"

class townMap : public gameNode
{
private:
	mapTool* _mapT;

	vector<vector<tagTile*>> _vvMap;
	unsigned int TILEX;
	unsigned int TILEY;

	DWORD* _attribute;

	image* _image;

	int tix;
	int tiy;
	int obx;
	int oby;

	int _index;
	int _count;

	int _index2;
	int _count2;
public:
	townMap();
	~townMap();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);
	void load();
	void tileDraw();
	void riverMove();
	void shirtMove();
	unsigned int getTileX() { return TILEX; }
	unsigned int getTileY() { return TILEY; }

	tagTile* getTile(int x, int y) { return _vvMap[y][x]; }
	DWORD getAttr(int x, int y) { return _attribute[x + y * TILEX]; }
};

