#pragma once
#include "gameNode.h"
#include "enemyManager.h"

class dungeon : public gameNode
{
private:
	enemyManager* _enemyManager;

public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();
};

