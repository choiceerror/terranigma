#pragma once
#include "item.h"

class Armor : public item
{
private:

	int _armorPoint;
	ARMORTYPE _armorType;



public:
	Armor();
	~Armor();



	virtual HRESULT init(const char* imageName, float x, float y,ARMORTYPE armorType);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	int getArmorPoint() { return _armorPoint; }
	void setArmorPoint(int armorPoint) { _armorPoint = armorPoint; }

	ARMORTYPE getTagArmor() { return _armorType; }
};

