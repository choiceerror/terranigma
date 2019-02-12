#pragma once
#include "item.h"

class Potion : public item
{
private:
	int _hpUpPoint;

	POTIONTYPE _potionType;

public:
	Potion();
	~Potion();

	virtual HRESULT init(const char* imageName, float x, float y, POTIONTYPE potionType);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX,float cameraY);

	int getHpUpPoint() { return _hpUpPoint; }
	void setHpUpPoint(int hpUpPoint) { _hpUpPoint = hpUpPoint; }

	POTIONTYPE getTagPotion() { return _potionType; }
};

