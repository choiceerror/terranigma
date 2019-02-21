#include "stdafx.h"
#include "dungeon.h"
#pragma warning(disable:4996)

dungeon::dungeon()
{
}


dungeon::~dungeon()
{
}

HRESULT dungeon::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	_enemyManager = new enemyManager;
	_player = new player;
	_camera = new camera;
	_dungeon = new dungeonMap;
	_itemManager = new ItemManager;
	_clockFade = new ClockFadeOut;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	_player->setMapManagerAddressLink(_dungeon);
	_enemyManager->setDungeonMapAddressLink(_dungeon);

	_dungeon->setDungeonFloor(DUNGEON_FLOOR::FIRST_FLOOR);
	_dungeon->init(_dungeon->getDungeonFloor());
	_player->init(false);
	_enemyManager->init();
	_itemManager->init();
	_enemyManager->setEnemy();
	_clockFade->init();

	_camera->init(GAMESIZEX, GAMESIZEY, GAMESIZEX, 3200);

	_clockFade->setClockFadeOut(false);
	_clockFade->setClockFadeIn(true);

	SOUNDMANAGER->play("theTower", SOUNDSIZE);
	IMAGEMANAGER->findImage("black")->setAlpahBlend(true);
	_alphaValue = 0;
	_changeScene = false;

	_worldTime = 0;
	_once = false;

	_dungeonUpbool = false;
	_dungeonDownbool = false;

	_isPlayerDeadAlphaOn = false;
	_playerDeadAlpha = 0;
	_dungeonSound = 0;

	_dungeonUp = RectMake(416, 0, 192, 50);
	_dungeonDown = RectMake(352, 3200 - 180, 320, 64);

	//_player->setPlayerDirection(UP);
	//_player->setPlayerPosX(500);
	//_player->setPlayerPosY(2816);

	playerSceneLoad();

	_player->setPlayerCurrentScene(PLAYERSCENE::DUNGEON_1F);


	if (_player->getPlayerX() < 100 || _player->getPlayerX() > 924 || _player->getPlayerY() < 0 || _player->getPlayerY() > 3200 || (_player->getPlayerX() == 0 && _player->getPlayerY() == 0))
	{
		_player->setPlayerDirection(UP);
		_player->setPlayerPosX(500);
		_player->setPlayerPosY(2816);
	}

	return S_OK;
}

void dungeon::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
	SAFE_DELETE(_dungeon);
	SAFE_DELETE(_camera);
	SAFE_DELETE(_itemManager);
}

void dungeon::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_enemyManager->update();
	_itemManager->update();
	itemRandomDrop();
	playerItemGet();
	_clockFade->update();
	if (_player->getPlayerLevelUP() == true)
	{
		if (_dungeonSound == 0)
		{
			_dungeonSound++;
			SOUNDMANAGER->pause("theTower");
		}
	}
	else
	{
		if (_dungeonSound == 1)
		{
			_dungeonSound--;
			SOUNDMANAGER->resume("theTower");
		}
	}




	//==============밑에 작성 금지===============
	dungeonChange();
	if (!_changeScene)
	{
		_player->update(true, 1);
	}

	EFFECTMANAGER->update();
}

void dungeon::render()
{
	if (!_changeScene)
	{
		_dungeon->render(_camera->getCameraX(), _camera->getCameraY());
		_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
		_itemManager->render(_camera->getCameraX(), _camera->getCameraY());
		playerDead();
		_player->render(_camera->getCameraX(), _camera->getCameraY(), true);

		if (_player->getPlayerHP() > 0)
		{
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 6; ++j)
				{
					IMAGEMANAGER->findImage("타일맵4")->frameRender(getMemDC(), 416 + 32 * j, i * 32 - _camera->getCameraY(), 14, 3);

					if (i == 0)
					{
						IMAGEMANAGER->findImage("타일맵4")->frameRender(getMemDC(), 416 + 32 * j, 2 * 32 - _camera->getCameraY(), 15, 4);
					}
				}
			}
			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (i == 0)
					{
						IMAGEMANAGER->findImage("타일맵2")->frameRender(getMemDC(), 352 + 32 * j, 2976 + i * 32 - _camera->getCameraY(), 7, 13);
					}
					if (i != 0)
					{
						IMAGEMANAGER->findImage("타일맵2")->frameRender(getMemDC(), 352 + 32 * j, 2976 + i * 32 - _camera->getCameraY(), 7, 14);
					}
				}
			}
		}


		_clockFade->render();
		IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), _alphaValue);

		EFFECTMANAGER->render();
		//Rectangle(getMemDC(), _dungeonDown);
		//Rectangle(getMemDC(), _dungeonUp);

		char str[100];
		//sprintf_s(str, "%f   %f",_player->getPlayerX(),_player->getPlayerY());
		//TextOut(getMemDC(), 120, 520, str, strlen(str));
	}
}

void dungeon::dungeonChange()
{
	

	//던전 나갈때
	if (!_changeScene)
	{
		if (IntersectRect(&_temp, &_player->getPlayerRc(), &_dungeonDown))
		{
			_dungeonDownbool = true;
		}
	}

	if (_dungeonDownbool)
	{
		_player->setPlayerUnMove(true);

		if (_player->getPlayerY() < _dungeonDown.top)
		{
			_player->setPlayerPosY(_player->getPlayerY() + 3);
		}

		if (!_once)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
		}

		if (_alphaValue < 255)
		{
			_alphaValue += 4;
		}
		if (_alphaValue > 255)
		{
			_alphaValue = 255;
		}

		if (1.4f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_changeScene = true;
			_player->playerSave();
			playerSceneSave();
			SOUNDMANAGER->stop("theTower");
			SCENEMANAGER->changeScene("introDungeon");
		}

		_once = true;
	}


	//던전 올라갈때
	if (!_changeScene)
	{
		if (IntersectRect(&_temp, &_player->getPlayerRc(), &_dungeonUp))
		{
			_dungeonUpbool = true;
		}
	}

	if (_dungeonUpbool)
	{
		_player->setTileCheck(false);
		_player->setPlayerUnMove(true);
		_clockFade->setClockFadeOut(true);
		_player->setPlayerPosY(_player->getPlayerY() - 3);

		if (!_once)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
		}

		if (1.3f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			_changeScene = true;
			_player->playerSave();
			playerSceneSave();
			SCENEMANAGER->changeScene("dungeon2F");
		}

		_once = true;
	}

}

void dungeon::playerSceneSave()
{
	HANDLE file;
	DWORD save;

	file = CreateFile("saveFile/playerScene.txt", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int scene = (int)_player->getPlayerCurrentScene();

	WriteFile(file, &scene, sizeof(int), &save, NULL);

	CloseHandle(file);
}

void dungeon::playerSceneLoad()
{
	HANDLE file;
	DWORD load;

	int scene;

	file = CreateFile("saveFile/playerScene.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &scene, sizeof(int), &load, NULL);

	if (scene > 7)
	{
		scene = (int)PLAYERSCENE::INTRO_DUNGEON;
	}

	_player->setPlayerCurrentScene((PLAYERSCENE)scene);

	if (_player->getPlayerCurrentScene() == PLAYERSCENE::INTRO_DUNGEON)
	{
		_player->setPlayerDirection(UP);
		_player->setPlayerPosX(500);
		_player->setPlayerPosY(2816);
	}

	if (_player->getPlayerCurrentScene() == PLAYERSCENE::DUNGEON_2F)
	{
		_player->setPlayerDirection(DOWN);
		_player->setPlayerPosX(500);
		_player->setPlayerPosY(224);
	}

	CloseHandle(file);

}

void dungeon::playerDead()
{
	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), _playerDeadAlpha);

	if (_player->getPlayerHP() <= 0)
	{
		_isPlayerDeadAlphaOn = true;
	}

	if (_isPlayerDeadAlphaOn)
	{
		if (_playerDeadAlpha < 255)
		{
			_playerDeadAlpha += 3;
		}

		if (_playerDeadAlpha > 255)
		{
			_playerDeadAlpha = 255;
			_isPlayerDeadAlphaOn = false;
		}
	}
}

void dungeon::itemRandomDrop()
{
	for (int i = 0; i < _enemyManager->getVEnemyDeadPoint().size(); i++)
	{
		_rndItemDrop = RND->getRandomInt(0, 200);
		_rndItemTypeDrop = RND->getRandomInt(0, 100);

		//40퍼확률
		if (_rndItemDrop >= 0 && _rndItemDrop <= 40)
		{
			_itemManager->dropGold(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y);
		}
		//20퍼확률
		else if (_rndItemDrop > 40 && _rndItemDrop <= 60)
		{
			//40퍼 확률
			if (_rndItemTypeDrop >= 60 && _rndItemTypeDrop <= 100)
			{
				_itemManager->dropPotion(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, POTIONTYPE::SMALL);
			}
			//30퍼 확률
			else if (_rndItemTypeDrop >= 30 && _rndItemTypeDrop < 60)
			{
				_itemManager->dropPotion(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, POTIONTYPE::MIDDLE);
			}
			//20퍼확률
			else if (_rndItemTypeDrop >= 10 && _rndItemTypeDrop < 30)
			{
				_itemManager->dropPotion(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, POTIONTYPE::BIG);
			}
			//10퍼확률로 안나옴
			else
			{
				_itemManager->dropPotion(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, POTIONTYPE::NONE);
			}
		}
		//20퍼확률
		else if (_rndItemDrop > 60 && _rndItemDrop <= 80)
		{
			//40퍼 확률
			if (_rndItemTypeDrop >= 60 && _rndItemTypeDrop <= 100)
			{
				_itemManager->dropAccessory(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ACCESSORYTYPE::LEEF);
			}
			//30퍼 확률
			else if (_rndItemTypeDrop >= 30 && _rndItemTypeDrop < 60)
			{
				_itemManager->dropAccessory(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ACCESSORYTYPE::RED_SCARF);
			}
			//20퍼확률
			else if (_rndItemTypeDrop >= 10 && _rndItemTypeDrop < 30)
			{
				_itemManager->dropAccessory(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ACCESSORYTYPE::TALISMAN);
			}
			//10퍼확률로 안나옴
			else
			{
				_itemManager->dropAccessory(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ACCESSORYTYPE::NONE);
			}
		}
		else if (_rndItemDrop > 80 && _rndItemDrop <= 100)
		{
			//40퍼 확률
			if (_rndItemTypeDrop >= 60 && _rndItemTypeDrop <= 100)
			{
				_itemManager->dropArmor(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ARMORTYPE::HOOD);
			}
			//30퍼 확률
			else if (_rndItemTypeDrop >= 30 && _rndItemTypeDrop < 60)
			{
				_itemManager->dropArmor(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ARMORTYPE::ICE_ARMOR);
			}
			//20퍼확률
			else if (_rndItemTypeDrop >= 10 && _rndItemTypeDrop < 30)
			{
				_itemManager->dropArmor(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ARMORTYPE::IRON_ARMOR);
			}
			//10퍼확률로 안나옴
			else
			{
				_itemManager->dropArmor(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, ARMORTYPE::NONE);
			}
		}
		else if (_rndItemDrop > 100 && _rndItemDrop <= 120)
		{
			//40퍼 확률
			if (_rndItemTypeDrop >= 60 && _rndItemTypeDrop <= 100)
			{
				_itemManager->dropWeapon(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, WEAPONTYPE::FIRE_SPEAR);
			}
			//30퍼 확률
			else if (_rndItemTypeDrop >= 30 && _rndItemTypeDrop < 60)
			{
				_itemManager->dropWeapon(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, WEAPONTYPE::ICE_SPEAR);
			}
			//20퍼확률
			else if (_rndItemTypeDrop >= 10 && _rndItemTypeDrop < 30)
			{
				_itemManager->dropWeapon(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, WEAPONTYPE::IRON_SPEAR);
			}
			//10퍼확률로 안나옴
			else
			{
				_itemManager->dropWeapon(_enemyManager->getVEnemyDeadPoint()[i].x, _enemyManager->getVEnemyDeadPoint()[i].y, WEAPONTYPE::NONE);
			}
		}

		//아이템 계속생성하지 않기위해서 지움.
		_enemyManager->setVEnemyDeadPoint()->erase(_enemyManager->setVEnemyDeadPoint()->begin() + i);
	}

}

void dungeon::playerItemGet()
{
	RECT temp;
	//골드아이템
	for (int i = 0; i < _itemManager->getVGlod().size(); i++)
	{
		if (IntersectRect(&temp, &_player->getPlayerRc(), &_itemManager->getVGlod()[i]->getItemRect()))
		{
			_player->setPlayerMoney(_player->getPlayerMoney() + _itemManager->getVGlod()[i]->getGoldNum());
			_itemManager->getVGlod()[i]->setItemIsLive(false);
		}

	}

	//포션아이템
	for (int i = 0; i < _itemManager->getVPotion().size(); i++)
	{
		if (IntersectRect(&temp, &_player->getPlayerRc(), &_itemManager->getVPotion()[i]->getItemRect()))
		{
			_player->getInventory()->pickUpPotion(_itemManager->getVPotion()[i]->getTagPotion());
			_itemManager->getVPotion()[i]->setItemIsLive(false);

		}
	}

	//악세사리
	for (int i = 0; i < _itemManager->getVAccessory().size(); i++)
	{
		if (IntersectRect(&temp, &_player->getPlayerRc(), &_itemManager->getVAccessory()[i]->getItemRect()))
		{
			_player->getInventory()->pickUpAccessory(_itemManager->getVAccessory()[i]->getTagAccessory());
			_itemManager->getVAccessory()[i]->setItemIsLive(false);
		}
	}

	//방어구
	for (int i = 0; i < _itemManager->getVArmor().size(); i++)
	{
		if (IntersectRect(&temp, &_player->getPlayerRc(), &_itemManager->getVArmor()[i]->getItemRect()))
		{
			_player->getInventory()->pickUpArmor(_itemManager->getVArmor()[i]->getTagArmor());
			_itemManager->getVArmor()[i]->setItemIsLive(false);
		}
	}

	//무기
	for (int i = 0; i < _itemManager->getVWeapon().size(); i++)
	{
		if (IntersectRect(&temp, &_player->getPlayerRc(), &_itemManager->getVWeapon()[i]->getItemRect()))
		{
			_player->getInventory()->pickUpWeapon(_itemManager->getVWeapon()[i]->getTagWeapon());
			_itemManager->getVWeapon()[i]->setItemIsLive(false);
		}
	}

}

void dungeon::setWindowsSize(int x, int y, int width, int height)
{

	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅을 한다
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);

}
