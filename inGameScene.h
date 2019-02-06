#pragma once
#include "gameNode.h"

//임의의 인게임을 보여줄 클라써

class inGameScene : public gameNode
{
public:
	inGameScene();
	~inGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

