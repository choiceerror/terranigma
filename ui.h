#pragma once
#include "gameNode.h"

enum UIROOM
{
	MAIN_ROOM,
	WEAPON_ROOM,
	ACCESSERY_ROOM,
	ARMOR_ROOM
};


class ui : public gameNode
{
private:
	RECT _goal;
	POINT _pt[36];

	int _placeFrameX;

	int _yomiFrameX;
	int _yomiFrameY;

	int _x, _y;
	int _goalX, _goalY;
	int _count;
	float _yomiAngle;
	float _yomiDistance;
	float _yomiSpeed;

	int _yomiPlace;

public:
	ui();
	~ui();

	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);
	void yomiFrame();
	void yomiMove();
	void movePoint();

};

