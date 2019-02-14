#pragma once
#include "npc.h"

class Elle : public npc
{
public:
	Elle();
	~Elle();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

