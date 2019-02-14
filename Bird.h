#pragma once
#include "npc.h"

class Bird : public npc
{
public:
	Bird();
	~Bird();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

