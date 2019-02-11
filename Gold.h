#pragma once
#include "item.h"

class Gold : public item
{
private:


public:
	Gold();
	~Gold();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY, int hpUpPoint);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);
};

