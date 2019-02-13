#pragma once
#include "gameNode.h"
#include "player.h"
#include "PlayerWorldMap.h"

class town : public gameNode
{
private:
	player* _player;
	PlayerWorldMap* _playerWorldMap;
public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();
};

