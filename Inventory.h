#pragma once
#include "gameNode.h"

class Inventory : public gameNode
{
private:


public:
	Inventory();
	~Inventory();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

