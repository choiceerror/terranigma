#pragma once
#include "gameNode.h"

class menu : public gameNode
{
private:


public:
	menu();
	~menu();

	HRESULT init();
	void release();
	void update();
	void render();
};

