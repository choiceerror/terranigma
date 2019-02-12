#pragma once
#include "gameNode.h"
#include "blackFadeOut.h"
#include "ItemManager.h"

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
	blackFadeOut* _blackFade;

	ItemManager* _iMgr;

	RECT _goal;
	POINT _pt[36];

	//방인덱스
	int _placeFrameX;

	//요미 프레임
	int _yomiFrameX;
	int _yomiFrameY;

	//요미의 오브젝트 인덱스
	int _yomiIndex;

	//요미 정보
	int _x, _y;
	int _goalX, _goalY;
	int _count;
	float _yomiAngle;
	float _yomiDistance;
	float _yomiSpeed;
	bool _move;
	bool _isRoomChanging;
	bool _onceTime;

	float _worldTime;

	//디버그용
	bool _isIndexMode;

public:
	ui();
	~ui();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setWindowsSize(int x, int y, int width, int height);
	void yomiFrame();
	void yomiMove();
	void movePoint();
	void placeChange();

	void dataLode();
	void itemSetting();
};

