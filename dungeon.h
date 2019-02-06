#pragma once
#include "gameNode.h"

class dungeon : public gameNode
{
private:


public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();
};

