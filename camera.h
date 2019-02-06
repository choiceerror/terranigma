#pragma once
#include "gameNode.h"

enum CAMERAMOD
{
	PLAYER_MODE,
	LINEAR_INTERPOLATION_MODE,
	LINEAR_INTERPOLATION_STOP_MODE
};

//	LINEAR == 선형
//	INTERPOLATION == 보간

class camera : public gameNode
{
private:
	//카메라 좌표
	POINTFLOAT _camera;

	//enum 으로 모드 관리
	CAMERAMOD _cameraMode;

	float _distance;
	float _angle;
	float _moveSpeed;

	float _moveTime;
	float _stopTime;
	float _worldTime;
	float _worldTime2;

	//카메라 이동용 포인트
	POINTFLOAT _orizin;
	POINTFLOAT _new;

	//윈도우사이즈가 씬별로 다를경우 대비해서 변수로씀
	float _winSizeX;
	float _winSizeY;

	//전체맵 사이즈변수
	float _worldMapSizeX;
	float _worldMapSizeY;


public:
	camera();
	~camera();

	HRESULT init(float winSizeX,float winSizeY,float worldMapSizeX, float worldMapSizeY);
	void release();
	void update(float playerX, float playerY);
	void render();

	//플레이어가 중앙에오는 카메라
	void playerMode(float playerX, float playerY);

	//입력한 시간만큼 도달점까지 가는 카메라
	void linearMove(float newX, float newY, float cameraMoveTime);
	void linearMoving();

	//입력한 무브시간만큼 도달점까지 가서 스탑시간만큼 멈춰있는 카메라
	void linearKeepMove(float newX, float newY, float cameraMoveTime, float stopTime);
	void linearKeepMoving();

	//현재카메라 위치 뱉어내는 함수
	POINTFLOAT getCameraPos(float x, float y);

	void exceptionPosition();

	//======================접근자 설정자======================

	POINTFLOAT getCameraPos() { return _camera; }

	float getCameraX() { return _camera.x; }
	void setCameraX(float x) { _camera.x = x; }

	float getCameraY() { return _camera.y; }
	void setCameraY(float y) { _camera.y = y; }

	CAMERAMOD getCameraMode() { return _cameraMode; }
	void setCameraMode(CAMERAMOD v) { _cameraMode = v; }

	void setDistance(float v) { _distance = v; }

	void setAngle(float v) { _distance = v; }

};

