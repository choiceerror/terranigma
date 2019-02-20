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
	_isJump = _jumpPower = _gravity = 0;

	return S_OK;
}

void DashJumpAttack::release()
{
}

void DashJumpAttack::update()
{

	if (_isJump == false) return;

	*_y -= _jumpPower;
	_jumpPower -= _gravity;

	if (*_startY < *_y)
	{
		_isJump = false;
		*_y = *_startY;
	}



}

void DashJumpAttack::render()
{

}

void DashJumpAttack::jumping(float* x, float* y, float* startX, float* startY, float jumpPower, float gravity)
{

	if (_isJump == true) return;
	_isJump = true;

	_x = x;
	_y = y;

	_startX = startX;
	_startY = startY;

	_gravity = gravity;
	_jumpPower = jumpPower;
}






