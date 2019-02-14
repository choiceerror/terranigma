#pragma once
#include "npc.h"

class Elder : public npc
{
public:
	Elder();
	~Elder();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

