#pragma once
#include "gameNode.h"

class npc : public gameNode
{
public:
	npc();
	~npc();

	HRESULT init();
	void release();
	void update();
	void render();
};

