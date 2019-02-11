#pragma once
#include "item.h"

enum class TagArmor
{
	NONE,
	ICE_ARMOR,
	HOOD,
	IRON_ARMOR
};

class Armor : public item
{
private:

	int _armorPoint;
	TagArmor _armorType;



public:
	Armor();
	~Armor();



	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	int getArmorPoint() { return _armorPoint; }
	void setArmorPoint(int armorPoint) { _armorPoint = armorPoint; }

	TagArmor getTagArmor() { return _armorType; }
};

