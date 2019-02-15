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

	IMAGEMANAGER->addFrameImage("Å¸ÀÏ¸Ê", "tileimage\\terranigma3.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Å¸ÀÏ¸Ê2", "tileimage\\terranigma2.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Å¸ÀÏ¸Ê4", "tileimage\\terranigma4.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("townTile", "tileimage\\townTile.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("worldTile", "tileimage\\worldTile.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save", "tileimage\\save.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load", "tileimage\\load.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("terrain", "tileimage\\terrain.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object", "tileimage\\object.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eraser", "tileimage\\eraser.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player", "image/player_test.bmp", 0, 0, 2016, 5642, 12, 31, true, RGB(255, 0, 255));

	_worldMap = new worldMap;
	_ui = new ui;
	_town = new town;
	_intro = new intro;
	_mapTool = new mapTool;
	_dungeon = new dungeon;
	_introDungeon = new IntroDungeon;

	SCENEMANAGER->addScene("worldMap", _worldMap);
	SCENEMANAGER->addScene("ui", _ui);
	SCENEMANAGER->addScene("town", _town);
	SCENEMANAGER->addScene("menu", _intro);
	SCENEMANAGER->addScene("mapTool", _mapTool);
	SCENEMANAGER->addScene("dungeon", _dungeon);
	SCENEMANAGER->addScene("introDungeon", _introDungeon);

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
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostQuitMessage(0);

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("dungeon");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("ui");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("town");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("worldMap");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->changeScene("introDungeon");
	}

	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
	SCENEMANAGER->update();
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================

	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

