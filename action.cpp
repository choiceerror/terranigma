#include "stdafx.h"
#include "action.h"


action::action()
{
}


action::~action()
{
}

HRESULT action::init()
{
	_worldTimeCount = 0;
	_isMoving = false;

	return S_OK;
}

void action::release()
{
}

void action::update()
{
	moving();
}

void action::render()
{
}

void action::moveTo(image* image, float endX, float endY, float time)
{
	if (!_isMoving)
	{
		_image = image;

		_endX = endX;	//도달할 좌표를 받아두고
		_endY = endY;

		_startX = image->GetX();//이미지의 현재좌표를 받고
		_startY = image->GetY();

		//여행거리를 구해둔다
		_travelRange = getDistance(_startX, _startY, _endX, _endY);

		//각도도 구해준다
		_angle = getAngle(_startX, _startY, _endX, _endY);

		_worldTimeCount = TIMEMANAGER->getWorldTime();

		_time = time;

		_isMoving = true;
	}
}

void action::moving()
{
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//요곳이 핵심입뉘다!!! 요로분!!!
	float moveSpeed = (elapsedTime / _time) * _travelRange;

	_image->SetX(_image->GetX() + cosf(_angle) * moveSpeed);
	_image->SetY(_image->GetY() + -sinf(_angle) * moveSpeed);

	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		_image->SetX(_endX);
		_image->SetY(_endY);

		_isMoving = false;
	}
}
