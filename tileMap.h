#pragma once
#include "MapNode.h"
#include "gameNode.h"
#include "camera.h"
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


	camera* _camera;

	int num;
	int tilenum;
	

	POINTFLOAT view;

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
	void viewMove();
	TERRAIN terrainSelect(int frameX, int frameY);

	OBJECT objSelect(int frameX, int frameY);

	void terrainPicking();
	void objPicking();

	void mapDraw();

	void mapSizeSet();
	void cameraMove();
};