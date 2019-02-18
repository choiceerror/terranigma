#pragma once
#include "gameNode.h"
#include <vector>
#include "camera.h"
#include "MapNode.h"

enum class SaveAndLoad
{
	DUNGEON,
	DUNGEON2F,
	BOSS,
	TOWN,
	WORLDMAP
};
class mapTool : public gameNode
{
private:

	vector<vector<tagTile*>>	_vvMap;//¸Ê

	TileSetting _tilesetting[basicTileX * basicTileY];
	tilebox _tileBox;
	//	tagTile _tiles[tileX * tileY];
	//	DWORD _attribute[tileX * tileY];
	CTRL Click;

	POINT ptMouse2;
	POINT _leftStartDrag;
	POINT _leftLastDrag;
	POINT _leftSubtraction;

	RECT box[5];
	RECT tileBox[6];

	RECT viewRc;
	RECT rc;
	SaveAndLoad _SaveAndLoad;
	camera* _camera;


	RECT sizeButton[4];

	RECT tileSelect[2];

	RECT d[2];
	RECT e[2];
	unsigned int TILEX;
	unsigned int TILEY;

	int _tilePosX;
	int _TilePosY;

	int num;
	int tilenum;

	bool check;
	int a;
	bool _mouseUp;
	int ee;
	int b, c;
	int f,g;
	POINTFLOAT view;
	POINT _mouseIndex;

	bool _leftDragMode;

public:

	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();



	void setUp();
	void setMap();
	void ClickBox();
	void save(SaveAndLoad saveNum);
	void load(SaveAndLoad loadNum);
	void viewMove();
	void tileDrag();
	void tileLeftDrag();

	void tilePreview();

	TERRAIN terrainSelect(int frameX, int frameY);

	OBJECT objSelect(int frameX, int frameY);


	void mapSize();


	void setWindowsSize(int x, int y, int width, int height);



	void terrainPicking();
	void objPicking();

	void mapDraw();

	void mapSizeSet();
	void cameraMove();
};

