#pragma once
#include "gameNode.h"
#include "PlayerWorldMap.h"
#include "world.h"
#include "camera.h"
class worldMap : public gameNode
{
private:

	PlayerWorldMap* _playerWorldMap;
	world* _world;
	camera* _camera;

public:
	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);
};

