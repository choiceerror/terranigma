#pragma once
#include "gameNode.h"
#define PLAYERFPS 6

enum PLAYERSTATE
{
	PLAYER_IDLE,
	PLAYER_IDLE_ACTION,
	PLAYER_WALK,
	PLAYER_RUN,
	PLAYER_TR_PUSH_UP,
	PLAYER_JUMP,
	PLAYER_LEVELUP,
	PLAYER_ATTACK,
	PLAYER_COMBINATION,
	PLAYER_JUMP_ATTACK,
	PLAYER_DASH_JUMP_ATTACK,
	PLAYER_DEATH,
	PLAYER_DASH_ATTACK,
	PLAYER_WORLDMAP,
	PLAYER_FALL,
	PLAYER_OBJ_PICKUP,
	PLAYER_OBJ_WALK,
	PLAYER_OBJ_THROW
};

enum PLAYERDIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct tagPlayer
{
	RECT rc;
	image* image_obj;
	image* image;
	animation* ani;
	PLAYERSTATE state;
	PLAYERDIRECTION direction;
	float x, y;
	float speed;
	int idX, idY;
	int HP;
	int str;
	int def;
	int money;

};

class player : public gameNode
{
private:
	tagPlayer _player;
	image* _image;

	int _doubleKey[4];
	int _curTime[4], _oldTime[4];
	
	bool _run, _jump;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyFrameInit();
	void keyInput();
	void playerState();
	void DoubleKeyIntVoid();
	void playerAniName(string targetName, string aniName);


	PLAYERSTATE getPlayerState() { return _player.state; }
	PLAYERDIRECTION getPlayerDirection() { return _player.direction; }
	float getPlayerX() { return _player.x; }
	float getPlayerY() { return _player.y; }
	int getPlayerMoney() { return _player.money; }
	int getPlayerHP() { return _player.HP; }
	int getPlayerStr() { return _player.str; }
	int getPlayerDef() { return _player.def; }
	RECT getPlayerRc() { return _player.rc;  }

};

