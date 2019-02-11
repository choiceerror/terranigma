#pragma once
#include "item.h"

class Weapon : public item
{
private:
	int _damagePoint;

public:
	Weapon();
	~Weapon();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY, int damagePoint);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);
};

