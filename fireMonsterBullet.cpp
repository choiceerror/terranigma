#include "stdafx.h"
#include "fireMonsterBullet.h"


fireMonsterBullet::fireMonsterBullet()
{
}


fireMonsterBullet::~fireMonsterBullet()
{
}

HRESULT fireMonsterBullet::init(const char * imageName, float range, int fireBulletMax)
{
	_imageName = imageName;
	_range = range;
	_fireBulletMax = fireBulletMax;
	int fire[] = { 10, 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("fireBullet", "fire", _imageName, fire, 4, 4, true);

	return S_OK;
}

void fireMonsterBullet::release()
{
}

void fireMonsterBullet::update()
{
	move();
}

void fireMonsterBullet::render(float viewX, float viewY)
{
	for (_viFireBullet = _vFireBullet.begin(); _viFireBullet != _vFireBullet.end(); _viFireBullet++)
	{
		_viFireBullet->image->aniRender(getMemDC(), viewX, viewY, _viFireBullet->fireBulletAni);
	//	Rectangle(getMemDC(), _viFireBullet->rc);
	}
}

void fireMonsterBullet::fire(float x, float y, float angle, float speed)
{
	if(_fireBulletMax <_vFireBullet.size()) return;

	tagFireBullet fireBullet;
	fireBullet.image = IMAGEMANAGER->findImage(_imageName);
	fireBullet.fireBulletAni = KEYANIMANAGER->findAnimation("fireBullet", "fire");
	fireBullet.x = fireBullet.fireX = fireBullet.viewX = x;
	fireBullet.y = fireBullet.fireY = fireBullet.viewY = y;
	fireBullet.angle = angle;
	fireBullet.speed = speed;
	fireBullet.radius = fireBullet.image->getFrameWidth() / 2;
	fireBullet.rc = RectMake(fireBullet.x, fireBullet.y, fireBullet.image->getFrameWidth(), fireBullet.image->getFrameHeight());

	_vFireBullet.push_back(fireBullet);
}

void fireMonsterBullet::move()
{
	for (_viFireBullet = _vFireBullet.begin(); _viFireBullet != _vFireBullet.end();)
	{
		_viFireBullet->x += cosf(_viFireBullet->angle) * _viFireBullet->speed;
		_viFireBullet->y += -sinf(_viFireBullet->angle) * _viFireBullet->speed;

		_viFireBullet->rc = RectMake(_viFireBullet->x, _viFireBullet->y, _viFireBullet->image->getFrameWidth(), _viFireBullet->image->getFrameHeight());
		_viFireBullet->fireBulletAni->start();

		if (_range < getDistance(_viFireBullet->x, _viFireBullet->y, _viFireBullet->fireX, _viFireBullet->fireY))
		{
			_viFireBullet = _vFireBullet.erase(_viFireBullet);
		}
		else _viFireBullet++;
	}
}
