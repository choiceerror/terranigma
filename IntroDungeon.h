#pragma once
#include "gameNode.h"
#include "player.h"
#include "camera.h"
#include "ClockFadeOut.h"

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
	ClockFadeOut* _clock;
	player* _player;
	camera* _camera;
	POINT _dungeonPos;
	POINT _goal;

	image* _door;
	animation* _doorAni;
	POINT _doorPos;
	image* _guardian;
	animation* _guardianAni;

	RECT _escapeRc;
	bool _escape;

	RECT _introDungeonPlayerRc;

	GUARDIANDIRECTION _guardianDirection;
	int _doorDirection;

	int _count;

	int _probeX;
	int _pY;

	float _playerSizeX, _playerSizeY;

	bool _guardianOn;
	bool _guardianTalk;
	bool _playerAccept;
	bool _doorOpen;

	bool _playerSizeChange;
	bool _dungeonGo;

	float _time;
	float _worldTime;
	float _speed;
	float _angle;
	bool _isLinear;
	bool _once;

	float _indunTime;
	
	int _alphaValue;
	
public:
	IntroDungeon();
	~IntroDungeon();
	
	HRESULT init();
	void release();
	void update();
	void render();

	void linearMove();

	void escapeDungeon();

	void setWindowsSize(int x, int y, int width, int height);

	void setPlayerAccept(bool playerAccept) { _playerAccept = playerAccept; }
	void setGuardianTalk(bool guardianTalk) { _guardianTalk = guardianTalk; }
	// 플레이어가 동의를 누르면 가디언이 사라지고 문이 열립니다.
	bool getPlayerAccept() { return _playerAccept; }
	// 이걸 사용하면 가디언 말하는걸 설정할수있음
	bool getGuardianTalk() { return _guardianTalk; }		
	// 플레이어가 던전 다들어가면 이 불함수가 켜집니다 이걸이용해서 씬전환을 합시다
	bool getPlayerDungeonGo() { return _dungeonGo; }
};

