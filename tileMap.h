#pragma once
#include "MapNode.h"
#include "gameNode.h"
#include <vector>

class tileMap : public gameNode
{
private:
	

	TileSetting _tilesteeing[basicTileX * basicTileY];
	tilebox _tileBox;
	tagTile _tiles[tileX * tileY];
	DWORD _attribute[tileX * tileY];
	CTRL Click;
	
	POINT ptMouse2;

	RECT box[5];
	RECT tileBox[5];

	int num;
	int tilenum;
	

public:
	tileMap();
	~tileMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void setUp();
	void setMap();
	void ClickBox();
	void save();
	void load();

	TERRAIN terrainSelect(int frameX, int frameY);

	OBJECT objSelect(int frameX, int frameY);

	void terrainPicking();
	void objPicking();

	void mapDraw();

	void mapSizeSet();
	void cameraMove();
};