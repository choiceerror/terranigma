#pragma once
#include "gameNode.h"

class ui : public gameNode
{
private:


public:
	ui();
	~ui();

	HRESULT init();
	void release();
	void update();
	void render();
};

