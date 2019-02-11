#pragma once
#include "item.h"

enum class TagWeapon
{
	NONE,
	ICE_SPEAR,
	IRON_SPEAR,
	FIRE_SPEAR
};

class Weapon : public item
{
private:
	int _damagePoint;

	TagWeapon _weaponType;

public:
	Weapon();
	~Weapon();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	int getDamagePoint() { return _damagePoint; }
	void setDamagePoint(int damage) { _damagePoint = damage; }

	TagWeapon getTagWeapon() { return _weaponType; }
};

