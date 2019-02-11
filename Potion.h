#pragma once
#include "item.h"

enum class TagPotion
{
	NONE,
	SMALL,
	MIDDLE,
	BIG
};

class Potion : public item
{
private:
	int _hpUpPoint;

	TagPotion _potionType;

public:
	Potion();
	~Potion();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX,float cameraY);

	int getHpUpPoint() { return _hpUpPoint; }
	void setHpUpPoint(int hpUpPoint) { _hpUpPoint = hpUpPoint; }

	TagPotion getTagPotion() { return _potionType; }
};

