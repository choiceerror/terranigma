#pragma once
#include "gameNode.h"

class ui : public gameNode
{
private:

	int _frameX;




public:
	ui();
	~ui();

	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);
};

