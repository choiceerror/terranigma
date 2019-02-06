#pragma once
#include "gameNode.h"

class mapTool : public gameNode
{
private:


public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();
};

