#pragma once
#include "item.h"

class Accessory : public item
{
private:


public:
	Accessory();
	~Accessory();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY, int hpUpPoint);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);
};

