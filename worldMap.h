#pragma once
#include "gameNode.h"
#include "PlayerWorldMap.h"
#include "world.h"
#include "camera.h"
#include "mode7.h"

class worldMap : public gameNode
{
private:

	PlayerWorldMap* _playerWorldMap;
	world* _world;
	camera* _camera;
	mode7* _mode7;

public:
	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void fake3DHighImage();

	void setWindowsSize(int x, int y, int width, int height);
};

