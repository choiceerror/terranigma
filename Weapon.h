#pragma once
#include "item.h"

enum class WEAPONTYPE
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

	WEAPONTYPE _weaponType;

public:
	Weapon();
	~Weapon();

	virtual HRESULT init(const char* imageName, float x, float y, WEAPONTYPE weaponType);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	int getDamagePoint() { return _damagePoint; }
	void setDamagePoint(int damage) { _damagePoint = damage; }

	WEAPONTYPE getTagWeapon() { return _weaponType; }
};

