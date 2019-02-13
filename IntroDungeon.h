#pragma once
#include "gameNode.h"
#include "player.h"
#include "camera.h"

enum GUARDIANDIRECTION
{
	GUARDIAN_CLOCKING = 0,
	GUARDIAN_COMEON,
	GUARDIAN_OUT,
	GUARDIAN_IDLE,
	GUARDIAN_TALK
};

class IntroDungeon : public gameNode
{
private:
	player* _player;
	camera* _camera;
	POINT _dungeonPos;

	image* _door;
	animation* _doorAni;
	POINT _doorPos;
	image* _guardian;
	animation* _guardianAni;

	GUARDIANDIRECTION _guardianDirection;
	int _doorDirection;

	int _count;

	bool _guardianOn;
	bool _guardianTalk;
	bool _playerAccept;
	bool _doorOpen;
public:
	IntroDungeon();
	~IntroDungeon();
	
	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);
	// 플레이어가 동의를 누르면 가디언이 사라지고 문이 열립니다.
	bool getPlayerAccept() { return _playerAccept; }
	// 이걸 사용하면 가디언 말하는걸 설정할수있음
	bool getGuardianTalk() { return _guardianTalk; }		
};

