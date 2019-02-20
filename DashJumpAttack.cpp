#include "stdafx.h"
#include "DashJumpAttack.h"


DashJumpAttack::DashJumpAttack()
{
}


DashJumpAttack::~DashJumpAttack()
{
}

HRESULT DashJumpAttack::init()
{
	_isJumpAttack = _jumpPower = _gravity = 0;

	return S_OK;
}

void DashJumpAttack::release()
{
}

void DashJumpAttack::update(float* x, float* y)
{

	if (_isJumpAttack == false) return;
	switch (_direction)
	{
	case 0:
		*_x -= _speed;
		if (*_startX - *x >= 280)
		{
			_isJumpAttack = false;
		}
		break;
	case 1:
		*_x += _speed;
		if (*x - *_startX >= 280)
		{
			_isJumpAttack = false;
		}
		break;
	case 2:
		*_y -= _speed;
		if (*_startY - *y >= 280)
		{
			_isJumpAttack = false;
		}
		break;
	case 3:
		*_y += _speed;
		if (*y - *_startY >= 280)
		{
			_isJumpAttack = false;
		}
		break;
	}


}

void DashJumpAttack::render()
{

}

void DashJumpAttack::dashJumpAttack(float* x, float* y, float* startX, float* startY, float jumpPower, float gravity, int direction, float speed)
{

	if (_isJumpAttack == true) return;
	_isJumpAttack = true;

	_x = x;
	_y = y;

	_startX = startX;
	_startY = startY;

	_gravity = gravity;
	_jumpPower = jumpPower;

	_direction = direction;

	_speed = speed;

}






