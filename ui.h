#pragma once
#include "gameNode.h"
#include "blackFadeOut.h"
#include "ItemManager.h"
#include "Inventory.h"
#include "ClockFadeOut.h"
#include "player.h"

class ui : public gameNode
{
private:
	enum class ROOMTYPE
	{
		MAIN_ROOM,
		WEAPON_ROOM,
		ACCESSERY_ROOM,
		ARMOR_ROOM
	};

	blackFadeOut* _blackFade;
	ItemManager* _iMgr;
	Inventory* _inventory;
	player* _player;

	//=====테스트용====
	ClockFadeOut* _clockFade;


	//================

	RECT _goal;
	POINT _uiPoint[36];

	POINT _weaponPoint[16];
	POINT _accessoryPoint[32];
	POINT _armorPoint[16];

	//방인덱스
	ROOMTYPE _room;

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

	//시간관련
	float _worldTime;
	float _roomVisitTime;


	//디버그용
	bool _isIndexMode;

	//환경설정
	bool _preferences;

	float _backgroundSoundSize;
	float _effectSoundSize;

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
	void roomPointSetting();
	void placeChange();

	void dataLoad();
	void itemSetting();
	void itemDraw();

	void uiIndexNameMessageBox();
	void uiReferencesRender();

	void yomiMoveSound();

public:

	float getBackgroundSoundSize() { return _backgroundSoundSize; }
	float getEffectSoundSize() { return _effectSoundSize; }
};

