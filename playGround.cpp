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
	IMAGEMANAGER->addFrameImage("worldTile", "tileimage\\worldTile2.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossTile", "tileimage\\bossTile.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save", "tileimage\\save.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load", "tileimage\\load.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("terrain", "tileimage\\terrain.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object", "tileimage\\object.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eraser", "tileimage\\eraser.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player", "image/player_test.bmp", 0, 0, 2016, 5642, 12, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ballMonster", "image/enemy1.bmp", 128, 128, 4, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("fireMonster", "image/enemy2.bmp", 180, 174, 5, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("knightMonster", "image/enemy3.bmp", 1820, 1600, 7, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("boss", "image/º¸½º.bmp", 1048, 239, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("bossBullet", "image/bullet.bmp", 104, 78, 4, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("shockAttack", "image/º¸½º°ø°ÝÀÌÆåÆ®.bmp", 1600, 288, 8, 2, true, MAGENTA);
	EFFECTMANAGER->addEffect("deadEffect", "image/deadEffect2.bmp", 1496, 110, 136, 110, 5, 0.17f, 1000);
	IMAGEMANAGER->addImage("black", "image/black.bmp", 1024, 768, true, MAGENTA);


	_worldMap = new worldMap;
	_ui = new ui;
	_town = new town;
	_intro = new intro;
	_mapTool = new mapTool;
	_dungeon = new dungeon;
	_introDungeon = new IntroDungeon;
	_dungeon2F = new dungeon2F;
	_bossScene = new bossScene;

	SCENEMANAGER->addScene("worldMap", _worldMap);
	SCENEMANAGER->addScene("ui", _ui);
	SCENEMANAGER->addScene("town", _town);
	SCENEMANAGER->addScene("menu", _intro);
	SCENEMANAGER->addScene("mapTool", _mapTool);
	SCENEMANAGER->addScene("dungeon", _dungeon);
	SCENEMANAGER->addScene("introDungeon", _introDungeon);
	SCENEMANAGER->addScene("bossScene", _bossScene);
	SCENEMANAGER->addScene("dungeon2F", _dungeon2F);

	SCENEMANAGER->changeScene("mapTool");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	
	//SAFE_DELETE(_worldMap);
	//SAFE_DELETE(_ui);
	//SAFE_DELETE(_town);
	//SAFE_DELETE(_intro);
	//SAFE_DELETE(_mapTool);
	//SAFE_DELETE(_dungeon);
	//SAFE_DELETE(_introDungeon);
	//SAFE_DELETE(_dungeon2F);
	//SAFE_DELETE(_bossScene);
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

	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene("dungeon2F");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene("bossScene");
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

