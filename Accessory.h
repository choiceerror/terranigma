#pragma once
#include "item.h"

enum class ACCESSORYTYPE
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
	ACCESSORYTYPE _accessoryType;

public:
	Accessory();
	~Accessory();

	virtual HRESULT init(const char* imageName, float x, float y, ACCESSORYTYPE accessoryType);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	int getAccesseryArmorPoint() { return _accesseryArmorPoint; }
	void setAccesseryArmorPoint(int armorPoint) { _accesseryArmorPoint = armorPoint; }

	ACCESSORYTYPE getTagAccessory() { return _accessoryType; }
};

