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

	vector<vector<tagTile*>>	_vvMap;//맵

	TileSetting _tilesetting[basicTileX * basicTileY];
	tilebox _tileBox;
	//	tagTile _tiles[tileX * tileY];
	//	DWORD _attribute[tileX * tileY];
	CTRL Click;

	POINT ptMouse2;
	POINT _leftStartDrag;
	POINT _leftLastDrag;
	POINT _leftSubtraction;
	POINT _mapEnd;

	RECT box[5];
	RECT tileBox[6];
	RECT tileMoveBox[6];
	RECT viewRc;
	RECT rc;
	RECT sizeButton[4];
	RECT tileSelect[2];
	RECT d[2];
	RECT e[2];

	image* _image;
	image* _image2;
	image* _image3;
	image* _image4;
	image* _image5;
	image* _image6;

	SaveAndLoad _SaveAndLoad;
	camera* _camera;

	unsigned int TILEX;
	unsigned int TILEY;

	int _tilePosX;
	int _TilePosY;

	int num;
	int tilenum;
	float tt;
	bool check;
	int a;
	bool _mouseUp;
	int ee;
	int b, c;
	//현재 마우스가 위치한 타일의 번호
	int x, y;

	int num1 , num2, num3, num4, num5, num6;
	POINTFLOAT view;
	POINT _mouseIndex;

	bool _leftDragMode;
	bool _tileMoveCheck;
	float _elapsedTime, _elapsedTime2, _elapsedTime3, _elapsedTime4, _elapsedTime5, _elapsedTime6;
	float _mapAngle;
	float _mapDistance;
	float _mapSpeed, _mapSpeed2, _mapSpeed3, _mapSpeed4, _mapSpeed5, _mapSpeed6;
	float _worldTime, _worldTime2, _worldTime3, _worldTime4, _worldTime5, _worldTime6;
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
	void tileimgMove();
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

