#pragma once
#include "gameNode.h"

class intro : public gameNode
{
private:


public:
	intro();
	~intro();

	HRESULT init();
	void release();
	void update();
	void render();
};

