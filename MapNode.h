#pragma once

#define tileX 60
#define tileY 60 
#define TileMainSIZE 32

#define TileSIZE 32

#define basicTileX 30  //타일 x축 나눈 갯수
#define basicTileY 16  //타일 y축 나눈 갯수

#define ATTR_UNMOVE		0x00000001
#define ATTR_ENEMY		0x00000002
#define ATTR_START		0x00000004
#define ATTR_END		0x00000008


//지형
enum TERRAIN
{
	TR_TILE_ONE, TR_TILE_TWO, TR_TILE_THREE, TR_TILE_FOUR, TR_TILE_FIVE, TR_END,
};

enum OBJECT
{

	OBJ_WALL, OBJ_ENEMY1, OBJ_ENEMY2, OBJ_ENEMY3,
	OBJ_PLAYER1, OBJ_PLAYER2,
	OBJ_NONE,
};

enum CTRL
{
	CTRL_SAVE,				//세이브 버튼
	CTRL_LOAD,				//로드  버튼
	CTRL_TERRAINDRAW,		//지형 버튼
	CTRL_OBJDRAW,			//오브젝트 버튼
	CTRL_ERASER,			//지우개 버튼
	CTRL_END
};

struct tagTile
{
	RECT rc;
	int FrameX;
	int FrameY;
	TERRAIN terrain; //지형
	OBJECT obj; //오브젝트
	int objFrameX; //오브젝트 번호
	int objFrameY;
	int a;
};


//타일 세팅
struct TileSetting
{
	RECT tilerc;
	int tilex;
	int tiley;
};

// 클릭한 타일 담기
struct tilebox
{
	//첫타일 변수
	int x;
	int y;
	//마지막 변수
	int lastX;
	int lastY;

	// 마지막 - 첫타일 뺀 변수
	int q;
	int w;





};

