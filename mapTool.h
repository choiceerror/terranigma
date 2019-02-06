#pragma once
#include "gameNode.h"
#include "tileMap.h"
class mapTool : public gameNode
{
private:

	tileMap* _MapT;

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();
};

