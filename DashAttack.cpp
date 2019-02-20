#include "stdafx.h"
#include "DashAttack.h"


DashAttack::DashAttack()
{
}


DashAttack::~DashAttack()
{
}

HRESULT DashAttack::init()
{
	_isDashAttack = false;
	_speed = 0;
	return S_OK;
}

void DashAttack::release()
{
}

void DashAttack::update(float* x, float* y, bool objUnMove)
{
	if (_isDashAttack == false) return;

	if (!objUnMove)
	{
		switch (_direction)
		{
		case 0:
			*_x -= _speed;
			if (*_startX - *x >= 200)
			{
				_isDashAttack = false;
			}
			break;
		case 1:
			*_x += _speed;
			if (*x - *_startX >= 200)
			{
				_isDashAttack = false;
			}
			break;
		case 2:
			*_y -= _speed;
			if (*_startY - *y >= 200)
			{
				_isDashAttack = false;
			}
			break;
		case 3:
			*_y += _speed;
			if (*y - *_startY >= 200)
			{
				_isDashAttack = false;
			}
			break;
		}
	}
	else
	{
		switch (_direction)
		{
		case 0:
			
			_isDashAttack = false;
			
			break;
		case 1:
			
			
			_isDashAttack = false;
			
			break;
		case 2:
		
			_isDashAttack = false;
			
			break;
		case 3:
			
			_isDashAttack = false;
			
			break;
		}
	}
}

void DashAttack::render()
{
}

void DashAttack::dashAttacking(float* x, float* y, float* startX, float* startY, int direction, float speed)
{
	if (_isDashAttack == true) return;

	_isDashAttack = true;

	_x = x;
	_y = y;

	_speed = speed;

	_startX = startX;
	_startY = startY;
	
	_direction = direction;
}
