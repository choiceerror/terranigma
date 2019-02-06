#pragma once
#include "gameNode.h"

class town : public gameNode
{
private:


public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();
};

