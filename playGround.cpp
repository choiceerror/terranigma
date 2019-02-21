#include "stdafx.h"
#include "playGround.h"
#pragma warning(disable:4996)

playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addFrameImage("타일맵", "tileimage\\terranigma3.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("타일맵2", "tileimage\\terranigma2.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("타일맵4", "tileimage\\terranigma4.bmp", 960, 512, basicTileX, basicTileY, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addFrameImage("boss", "image/보스.bmp", 1048, 239, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("bossBullet", "image/bullet.bmp", 104, 78, 4, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("shockAttack", "image/보스공격이펙트.bmp", 1600, 288, 8, 2, true, MAGENTA);
	EFFECTMANAGER->addEffect("deadEffect", "image/deadEffect2.bmp", 1496, 110, 136, 110, 5, 0.17f, 1000);
	EFFECTMANAGER->addEffect("bossDeadEffect", "image/deadEffect.bmp", 8160, 550, 680, 550, 3, 0.05f, 1000);
	IMAGEMANAGER->addImage("black", "image/black.bmp", 1024, 768, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("messageSpear", "image/massageSpear.bmp", 600, 179, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("talkPage", "image/talkPageNext.bmp", 75, 30, 3, 1, true, MAGENTA);
	EFFECTMANAGER->addEffect("damageEffect", "image/타격이펙트.bmp", 200, 100, 100, 100, 3, 0.04f, 1000);
	IMAGEMANAGER->addImage("인트로1", "image/인트로1.bmp", WINSIZEX, GAMESIZEY, true, MAGENTA);
	IMAGEMANAGER->addImage("인트로2", "image/인트로2.bmp", GAMESIZEX, GAMESIZEY, true, MAGENTA);
	IMAGEMANAGER->addImage("인트로3", "image/인트로3.bmp", GAMESIZEX, GAMESIZEY, true, MAGENTA);
	IMAGEMANAGER->addImage("인트로4", "image/인트로4.bmp", GAMESIZEX, GAMESIZEY, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("인트로5", "image/인트로5.bmp", 124, 125, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("인트로6", "image/인트로6.bmp", 318, 122, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("인트로7", "image/인트로7.bmp", GAMESIZEX, GAMESIZEY, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("인트로8", "image/인트로8.bmp", 290, 36, 1, 1, true, MAGENTA);

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

	soundFileInit();
	effectSoundInit();

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
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		fileDelete();
		PostQuitMessage(0);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("dungeon");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("ui");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("town");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("worldMap");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("introDungeon");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("dungeon2F");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("bossScene");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		allSoundStop();
		SCENEMANAGER->changeScene("menu");
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

void playGround::fileDelete()
{
	//deleteFile("saveFile/introDungeon.txt");
	deleteFile("saveFile/inventory.txt");
	deleteFile("saveFile/플레이어.txt");
	deleteFile("saveFile/playerScene.txt");
	deleteFile("saveFile/UiSave.txt");
	fileReset();
}

void playGround::deleteFile(const char * fileAddress)
{
	HANDLE file;
	DWORD read;

	char str[128];
	file = CreateFile(fileAddress, GENERIC_WRITE, NULL, NULL,
		TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	CloseHandle(file);
}

void playGround::fileReset()
{
	bool _twice;
	_twice = false;

	char temp[128];

	vector<string> vStr;

	vStr.push_back(itoa((int)_twice, temp, 10));

	TXTDATA->txtSave("saveFile/introDungeon.txt", vStr);
}

void playGround::soundFileInit()
{
	SOUNDMANAGER->addSound("bossSceneBGM", "sound/bossFight.mp3", true, true);
	SOUNDMANAGER->addSound("introDungeon", "sound/introDungeon.mp3", true, true);
	SOUNDMANAGER->addSound("introOpening", "sound/introOpening.mp3", true, true);
	SOUNDMANAGER->addSound("theTower", "sound/theTower.mp3", true, true);
	SOUNDMANAGER->addSound("theTown", "sound/theTown.mp3", true, true);
	SOUNDMANAGER->addSound("worldMap", "sound/worldMap.mp3", true, true);
}

void playGround::effectSoundInit()
{
	SOUNDMANAGER->addSound("goldGet", "sound/골드먹을때.mp3", false, false);
	SOUNDMANAGER->addSound("playerAttack", "sound/공격.mp3", false, false);
	SOUNDMANAGER->addSound("dashAttack", "sound/대쉬공격.mp3", false, false);
	SOUNDMANAGER->addSound("dashJumpAttack", "sound/대쉬점프공격.mp3", false, false);
	SOUNDMANAGER->addSound("comboAttack", "sound/연속공격.mp3", false, false);
	SOUNDMANAGER->addSound("yomiMove", "sound/요미무브.mp3", false, false);
	SOUNDMANAGER->addSound("playerJump", "sound/점프.mp3", false, false);
	SOUNDMANAGER->addSound("playerJumpAttack", "sound/점프공격.mp3", false, false);
	SOUNDMANAGER->addSound("textSound", "sound/텍스트사운드.mp3", false, true);
}

void playGround::allSoundStop()
{
	SOUNDMANAGER->stop("bossSceneBGM");
	SOUNDMANAGER->stop("introDungeon");
	SOUNDMANAGER->stop("introOpening");
	SOUNDMANAGER->stop("theTower");
	SOUNDMANAGER->stop("theTown");
	SOUNDMANAGER->stop("worldMap");
}

