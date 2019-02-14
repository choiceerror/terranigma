#pragma once
#include "npc.h"

class TownHuman : public npc
{
public:
	TownHuman();
	~TownHuman();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

