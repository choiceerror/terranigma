#pragma once
#include "npc.h"

class Bird : public npc
{
public:
	Bird();
	~Bird();

	virtual HRESULT init(string npcName, const char* imageName, float x, float y, int idX, int idY);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	void birdState();

};


