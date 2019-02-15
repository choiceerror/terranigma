#pragma once
#include "npc.h"

class TownHuman : public npc
{
public:
	TownHuman();
	~TownHuman();

	virtual HRESULT init(TOWNHUMAN townName ,string npcName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	void townHumanState();
};

