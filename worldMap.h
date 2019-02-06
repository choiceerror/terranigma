#pragma once
#include "gameNode.h"

class worldMap : public gameNode
{
private:


public:
	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();
};

