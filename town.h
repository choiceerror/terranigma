#pragma once
#include "gameNode.h"
#include "player.h"
#include "camera.h"
#include "townMap.h"
#include "npcManager.h"
#include "randomFunction.h"
#include "messageSpear.h"


class town : public gameNode
{
private:
	player* _player;
	camera* _camera;
	townMap* _town;

	image* _image;

	npcManager* _npcManager;

	messageSpear* _messageSpear;

	RECT _escape;
	RECT _house;

	int _alphaValue;
	bool _once;
	float _worldTime;

	bool _worldMapIn;

	bool _fadeOut;

	int _houseAlpha;
	int _bedAlpha;
	bool _houseAlphaBlend;

	int _index;
	int _count;

public:
	town();
	~town();

	HRESULT init();
	void release();
	void update();
	void render();

	void setWindowsSize(int x, int y, int width, int height);

	void worldMapIn();
	void townIn();
	void riverMove();
	void houseCollision();
	void playerSceneSave();
	void playerSceneLoad();

};

