#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "ui.h"
#include "town.h"
#include "menu.h"
#include "mapTool.h"
#include "dungeon.h"

class playGround : public gameNode
{
private:
	worldMap*	_worldMap;
	ui*			_ui;
	town*		_town;
	menu*		_menu;
	mapTool*	_mapTool;
	dungeon*	_dungeon;




	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

