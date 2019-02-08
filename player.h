#pragma once
#include "gameNode.h"
#define PLAYERFPS 4

enum PLAYERDIRECTION
{
	PLAYER_IDLE_LEFT,
	PLAYER_IDLE_RIGHT,
	PLAYER_IDLE_UP,
	PLAYER_IDLE_DOWN,
	PLAYER_IDLE_ACTION,
	PLAYER_WALK_LEFT,
	PLAYER_WALK_RIGHT,
	PLAYER_WALK_UP,
	PLAYER_WALK_DOWN,
	PLAYER_RUN_LEFT,
	PLAYER_RUN_RIGHT,
	PLAYER_RUN_UP,
	PLAYER_RUN_DOWN,
	PLAYER_TR_PUSH_UP,
	PLAYER_JUMP_LEFT,
	PLAYER_JUMP_RIGHT,
	PLAYER_JUMP_UP,
	PLAYER_JUMP_DOWN,
	PLAYER_LEVELUP,
	PLAYER_ATTACK_LEFT,
	PLAYER_ATTACK_RIGHT,
	PLAYER_ATTACK_UP,
	PLAYER_ATTACK_DOWN,
	PLAYER_COMBINATION_LEFT,
	PLAYER_COMBINATION_RIGHT,
	PLAYER_COMBINATION_UP,
	PLAYER_COMBINATION_DOWN,
	PLAYER_JUMP_ATTACK_LEFT,
	PLAYER_JUMP_ATTACK_RIGHT,
	PLAYER_JUMP_ATTACK_UP,
	PLAYER_JUMP_ATTACK_DOWN,
	PLAYER_DASH_JUMP_ATTACK_LEFT,
	PLAYER_DASH_JUMP_ATTACK_RIGHT,
	PLAYER_DASH_JUMP_ATTACK_UP,
	PLAYER_DASH_JUMP_ATTACK_DOWN,
	PLAYER_DEATH,
	PLAYER_DASH_ATTACK_LEFT,
	PLAYER_DASH_ATTACK_RIGHT,
	PLAYER_DASH_ATTACK_UP,
	PLAYER_DASH_ATTACK_DOWN,
	PLAYER_WORLDMAP_LEFT,
	PLAYER_WORLDMAP_RIGHT,
	PLAYER_WORLDMAP_UP,
	PLAYER_WORLDMAP_DOWN,
	PLAYER_FALL,
	PLAYER_OBJ_PICKUP_LEFT,
	PLAYER_OBJ_PICKUP_RIGHT,
	PLAYER_OBJ_PICKUP_UP,
	PLAYER_OBJ_PICKUP_DOWN,
	PLAYER_OBJ_WALK_LEFT,
	PLAYER_OBJ_WALK_RIGHT,
	PLAYER_OBJ_WALK_UP,
	PLAYER_OBJ_WALK_DOWN,
	PLAYER_OBJ_THROW_LEFT,
	PLAYER_OBJ_THROW_RIGHT,
	PLAYER_OBJ_THROW_UP,
	PLAYER_OBJ_THROW_DOWN

};

struct tagPlayer
{
	RECT rc;
	image* image;
	animation* ani;
	PLAYERDIRECTION direction;
	float x, y;
	float speed;
	int idX, idY;
	int HP;
	int power;
	int def;
	int money;

};

class player : public gameNode
{
private:
	tagPlayer _player;
	
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
};

