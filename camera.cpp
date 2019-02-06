#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init(float winSizeX, float winSizeY, float worldMapSizeX, float worldMapSizeY)
{
	_camera.x = 0;
	_camera.y = 0;

	_moveTime = 0;
	_stopTime = 0;

	_cameraMode = PLAYER_MODE;

	_winSizeX = winSizeX;
	_winSizeY = winSizeY;
	_worldMapSizeX = worldMapSizeX;
	_worldMapSizeY = worldMapSizeY;


	return S_OK;
}

void camera::release()
{
}

void camera::update(float playerX, float playerY)
{
	//카메라 모드
	switch (_cameraMode)
	{
	case PLAYER_MODE:
		playerMode(playerX, playerY);

		break;
	case LINEAR_INTERPOLATION_MODE:
		linearMoving();

		break;
	case LINEAR_INTERPOLATION_STOP_MODE:
		linearKeepMoving();

		break;
	default:
		break;
	}

	//카메라가 화면밖에 못가게
	exceptionPosition();
}

void camera::render()
{
	//char str[100];
	//sprintf_s(str, "카메라 x : %f", _camera.x);
	//TextOut(getMemDC(), 500, 20, str, strlen(str));
	//sprintf_s(str, "카메라 y : %f", _camera.y);
	//TextOut(getMemDC(), 500, 40, str, strlen(str));
}

void camera::playerMode(float playerX, float playerY)
{
	//4모서리에 있을때
	if (playerX < _winSizeX / 2 && playerY < _winSizeY / 2)
	{
		_camera.x = 0;
		_camera.y = 0;
	}
	else if (playerX > _worldMapSizeX - _winSizeX / 2 && playerY < _winSizeY / 2)
	{
		_camera.x = _worldMapSizeX - _winSizeX;
		_camera.y = 0;
	}
	else if (playerX < _winSizeX / 2 && playerY > _worldMapSizeY - _winSizeY / 2)
	{
		_camera.x = 0;
		_camera.y = _worldMapSizeY - _winSizeY;
	}
	else if (playerX > _worldMapSizeX - _winSizeX / 2 && playerY > _worldMapSizeY - _winSizeY / 2)
	{
		_camera.x = _worldMapSizeX - _winSizeX;
		_camera.y = _worldMapSizeY - _winSizeY;
	}
	//x좌표예외처리
	else if (playerX < _winSizeX / 2)
	{
		_camera.x = 0;
		_camera.y = playerY - _winSizeY / 2;
	}
	else if (playerX > _worldMapSizeX - _winSizeX / 2)
	{
		_camera.x = _worldMapSizeX - _winSizeX;
		_camera.y = playerY - _winSizeY / 2;
	}
	//y좌표예외처리
	else if (playerY < _winSizeY / 2)
	{
		_camera.x = playerX - _winSizeX / 2;
		_camera.y = 0;
	}
	else if (playerY > _worldMapSizeY - _winSizeY / 2)
	{
		_camera.x = playerX - _winSizeX / 2;
		_camera.y = _worldMapSizeY - _winSizeY;
	}
	//기본상태
	else
	{
		_camera.x = playerX - _winSizeX / 2;
		_camera.y = playerY - _winSizeY / 2;
	}
}

void camera::linearMove(float newX, float newY, float cameraMoveTime)
{
	_cameraMode = LINEAR_INTERPOLATION_MODE;

	_new = getCameraPos(newX, newY);

	_orizin.x = _camera.x;
	_orizin.y = _camera.y;

	_distance = getDistance(_orizin.x, _orizin.y, _new.x, _new.y);
	_angle = getAngle(_orizin.x, _orizin.y, _new.x, _new.y);
	_worldTime = TIMEMANAGER->getWorldTime();
	_moveTime = cameraMoveTime;
}

void camera::linearMoving()
{
	if (_cameraMode == PLAYER_MODE) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	if (_distance == 0)
	{
		_moveTime = 0.001f;
	}
	float moveSpeed = (elapsedTime / _moveTime) * _distance;

	if (moveSpeed != 0)
	{
		_camera.x += cosf(_angle) * moveSpeed;
		_camera.y += -sinf(_angle) * moveSpeed;
	}

	if (_moveTime + _worldTime <= TIMEMANAGER->getWorldTime())
	{
		_worldTime = TIMEMANAGER->getWorldTime();

		_camera.x = _new.x;
		_camera.y = _new.y;

		_cameraMode = PLAYER_MODE;
	}
}

void camera::linearKeepMove(float newX, float newY, float cameraMoveTime, float stopTime)
{
	_cameraMode = LINEAR_INTERPOLATION_STOP_MODE;

	_new = getCameraPos(newX, newY);

	_orizin.x = _camera.x;
	_orizin.y = _camera.y;

	_distance = getDistance(_orizin.x, _orizin.y, _new.x, _new.y);
	_angle = getAngle(_orizin.x, _orizin.y, _new.x, _new.y);
	_worldTime = TIMEMANAGER->getWorldTime();
	_moveTime = cameraMoveTime;
	_stopTime = stopTime;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	_moveSpeed = (elapsedTime / _moveTime) * _distance;
}

void camera::linearKeepMoving()
{
	if (_cameraMode == PLAYER_MODE) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	if (_distance == 0)
	{
		_moveTime = 0.001f;
	}

	if (_moveTime + _worldTime <= TIMEMANAGER->getWorldTime())
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_angle = 0;
		_moveSpeed = 0;
		_camera.x = _new.x;
		_camera.y = _new.y;
	}

	if (_moveSpeed != 0)
	{
		_camera.x += cosf(_angle) * _moveSpeed;
		_camera.y += -sinf(_angle) * _moveSpeed;
	}


	if (_stopTime + _worldTime2 <= TIMEMANAGER->getWorldTime())
	{
		_worldTime2 = TIMEMANAGER->getWorldTime();

		_cameraMode = PLAYER_MODE;
	}
}

POINTFLOAT camera::getCameraPos(float x, float y)
{
	POINTFLOAT _point;

	//4모서리에 있을때
	if (x < _winSizeX / 2 && y < _winSizeY / 2)
	{
		_point.x = 0;
		_point.y = 0;

		return _point;
	}
	else if (x > _worldMapSizeX - _winSizeX / 2 && y < _winSizeY / 2)
	{
		_point.x = _worldMapSizeX - _winSizeX;
		_point.y = 0;

		return _point;
	}
	else if (x < _winSizeX / 2 && y > _worldMapSizeY - _winSizeY / 2)
	{
		_point.x = 0;
		_point.y = _worldMapSizeY - _winSizeY;

		return _point;
	}
	else if (x > _worldMapSizeX - _winSizeX / 2 && y > _worldMapSizeY - _winSizeY / 2)
	{
		_point.x = _worldMapSizeX - _winSizeX;
		_point.y = _worldMapSizeY - _winSizeY;

		return _point;
	}
	//x좌표예외처리
	else if (x < _winSizeX / 2)
	{
		_point.x = 0;
		_point.y = y - _winSizeY / 2;

		return _point;
	}
	else if (x > _worldMapSizeX - _winSizeX / 2)
	{
		_point.x = _worldMapSizeX - _winSizeX;
		_point.y = y - _winSizeY / 2;

		return _point;
	}
	//y좌표예외처리
	else if (y < _winSizeY / 2)
	{
		_point.x = x - _winSizeX / 2;
		_point.y = 0;

		return _point;
	}
	else if (y > _worldMapSizeY - _winSizeY / 2)
	{
		_point.x = x - _winSizeX / 2;
		_point.y = _worldMapSizeY - _winSizeY;

		return _point;
	}
	//기본상태
	else
	{
		_point.x = x - _winSizeX / 2;
		_point.y = y - _winSizeY / 2;

		return _point;
	}
}

void camera::exceptionPosition()
{
	//예외처리
	if (_camera.x <= 0)
	{
		_camera.x = 0;
	}

	if (_camera.x >= _worldMapSizeX - _winSizeX)
	{
		_camera.x = _worldMapSizeX - _winSizeX;
	}

	if (_camera.y <= 0)
	{
		_camera.y = 0;
	}

	if (_camera.y >= _worldMapSizeY - _winSizeY)
	{
		_camera.y = _worldMapSizeY - _winSizeY;
	}
}
