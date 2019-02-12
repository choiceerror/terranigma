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
	KEYANIMANAGER->addArrayFrameAnimation("fireBullet", "fire", _imageName, fire, 4, 5, true);

	return S_OK;
}

void fireMonsterBullet::release()
{
}

void fireMonsterBullet::update()
{
	move();
}

void fireMonsterBullet::render(float cameraX, float cameraY)
{
	for (_viFireBullet = _vFireBullet.begin(); _viFireBullet != _vFireBullet.end(); _viFireBullet++)
	{
		//카메라 좌표에따라 가상좌표 계산
		_viFireBullet->viewX = _viFireBullet->x - cameraX;
		_viFireBullet->viewY = _viFireBullet->y - cameraY;
		_viFireBullet->image->expandAniRenderCenter(getMemDC(), _viFireBullet->viewX, _viFireBullet->viewY, _viFireBullet->fireBulletAni, 3.f, 3.f);
		//Rectangle(getMemDC(), _viFireBullet->rc);
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
	fireBullet.rc = RectMakeCenter(fireBullet.x, fireBullet.y, fireBullet.image->getFrameWidth(), fireBullet.image->getFrameHeight());
	fireBullet.isCollision = false;

	_vFireBullet.push_back(fireBullet);
}

void fireMonsterBullet::move()
{
	for (_viFireBullet = _vFireBullet.begin(); _viFireBullet != _vFireBullet.end();)
	{
		//총알 이동
		_viFireBullet->x += cosf(_viFireBullet->angle) * _viFireBullet->speed;
		_viFireBullet->y += -sinf(_viFireBullet->angle) * _viFireBullet->speed;

		_viFireBullet->rc = RectMakeCenter(_viFireBullet->x, _viFireBullet->y, _viFireBullet->image->getFrameWidth(), _viFireBullet->image->getFrameHeight());
		_viFireBullet->fireBulletAni->start();

		if ((_range < getDistance(_viFireBullet->x, _viFireBullet->y, _viFireBullet->fireX, _viFireBullet->fireY)) || (*_viFireBullet).isCollision == true)
		{
			_viFireBullet = _vFireBullet.erase(_viFireBullet);
		}
		else _viFireBullet++;
	}
}
