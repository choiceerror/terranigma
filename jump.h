#pragma once
#include "gameNode.h"

class jump : public gameNode
{
public:
	jump();
	~jump();

	HRESULT init();
	void release();
	void update();
	void render();
};


