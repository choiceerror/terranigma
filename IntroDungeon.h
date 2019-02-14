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
	
public:
	IntroDungeon();
	~IntroDungeon();
	
	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);

	void setPlayerAccept(bool playerAccept) { _playerAccept = playerAccept; }
	void setGuardianTalk(bool guardianTalk) { _guardianTalk = guardianTalk; }
	// �÷��̾ ���Ǹ� ������ ������� ������� ���� �����ϴ�.
	bool getPlayerAccept() { return _playerAccept; }
	// �̰� ����ϸ� ����� ���ϴ°� �����Ҽ�����
	bool getGuardianTalk() { return _guardianTalk; }		
	// �÷��̾ ���� �ٵ��� �� ���Լ��� �����ϴ� �̰��̿��ؼ� ����ȯ�� �սô�
	bool getPlayerDungeonGo() { return _dungeonGo; }
};
