#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "ui.h"
#include "town.h"
#include "intro.h"
#include "mapTool.h"
#include "dungeon.h"
#include "dungeon2F.h"
#include "bossScene.h"
#include "IntroDungeon.h"

class playGround : public gameNode
{
private:
	worldMap*	_worldMap;
	ui*			_ui;
	town*		_town;
	intro*		_intro;
	mapTool*	_mapTool;
	dungeon*	_dungeon;
	dungeon2F*   _dungeon2F;
	bossScene*   _bossScene;
	IntroDungeon* _introDungeon;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

