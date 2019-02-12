#pragma once
#include "gameNode.h"

enum PLAYERWORLDMAP
{
	WORLDMAP_IDLE_LEFT,
	WORLDMAP_IDLE_RIGHT,
	WORLDMAP_IDLE_UP,
	WORLDMAP_IDLE_DOWN,
	WORLDMAP_MOVE_LEFT,
	WORLDMAP_MOVE_RIGHT,
	WORLDMAP_MOVE_UP,
	WORLDMAP_MOVE_DOWN
};

class PlayerWorldMap : gameNode
{
private:
	PLAYERWORLDMAP _playerDirection;
	image * _playerImage;
	animation* _ani;
	RECT _playerRc;
	float _x, _y;
	float _speed;

public:
	PlayerWorldMap();
	~PlayerWorldMap();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);
};

