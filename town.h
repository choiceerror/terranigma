#pragma once
#include "gameNode.h"
#include "player.h"
#include "PlayerWorldMap.h"
#include "camera.h"
#include "townMap.h"
#include "npcManager.h"
#include "randomFunction.h"



class town : public gameNode
{
private:
	player* _player;
	PlayerWorldMap* _playerWorldMap;
	camera* _camera;
	townMap* _town;

	npcManager* _npcManager;

public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);
};

