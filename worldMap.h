#pragma once
#include "gameNode.h"
#include "PlayerWorldMap.h"
#include "world.h"
#include "camera.h"
#include "mode7.h"
#include "player.h"

class worldMap : public gameNode
{
private:
	player* _player;
	PlayerWorldMap* _playerWorldMap;
	world* _world;
	camera* _camera;
	mode7* _mode7;

	int _alphaValue;
	float _worldTime;
	bool _once;

	int _playerPosition;


public:
	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void fake3DHighImage();

	void worldMapIn();

	void setWindowsSize(int x, int y, int width, int height);

	void playerLoad();
};

