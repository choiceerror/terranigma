#pragma once
#include "item.h"

class Armor : public item
{
private:
	int _armorPoint;


public:
	Armor();
	~Armor();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY, int armorPoint);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);
};

