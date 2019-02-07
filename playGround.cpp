#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);

	_worldMap = new worldMap;
	_ui = new ui;
	_town = new town;
	_menu = new menu;
	_mapTool = new mapTool;
	_dungeon = new dungeon;

	SCENEMANAGER->addScene("worldMap", _worldMap);
	SCENEMANAGER->addScene("ui", _ui);
	SCENEMANAGER->addScene("town", _town);
	SCENEMANAGER->addScene("menu", _menu);
	SCENEMANAGER->addScene("mapTool", _mapTool);
	SCENEMANAGER->addScene("dungeon", _dungeon);

	SCENEMANAGER->changeScene("mapTool");


	return S_OK;
}


void playGround::release()
{
	gameNode::release();

}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	KEYANIMANAGER->update();
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===========================================================

	SCENEMANAGER->render();

	
	//===========================================================
	IMAGEMANAGER->findImage("backBuffer")->render(getHDC(), 0, 0);
}

