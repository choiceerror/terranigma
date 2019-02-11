#pragma once
#include "item.h"

enum class TagAccessory
{
	NONE,
	RED_SCARF,
	TALISMAN,
	LEEF
};

class Accessory : public item
{
private:
	int _accesseryArmorPoint;
	TagAccessory _accessoryType;

public:
	Accessory();
	~Accessory();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	int getAccesseryArmorPoint() { return _accesseryArmorPoint; }
	void setAccesseryArmorPoint(int armorPoint) { _accesseryArmorPoint = armorPoint; }

	TagAccessory getTagAccessory() { return _accessoryType; }
};

