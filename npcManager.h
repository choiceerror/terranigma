#pragma once
#include "gameNode.h"
#include "Bird.h"
#include "Elder.h"
#include "Elle.h"

class npcManager : public gameNode
{
private:
	//²¿²¿
	vector<Bird*> _vBird;
	vector<Bird*>::iterator _viBird;

public:
	npcManager();
	~npcManager();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);

	void setBird();
};

