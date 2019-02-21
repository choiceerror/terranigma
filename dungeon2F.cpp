#include "stdafx.h"
#include "dungeon2F.h"


dungeon2F::dungeon2F()
{
}


dungeon2F::~dungeon2F()
{
}

HRESULT dungeon2F::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	_enemyManager = new enemyManager;
	_player = new player;
	_camera = new camera;
	_dungeon2F = new dungeonMap;
	_itemManager = new ItemManager;
	_clockFade = new ClockFadeOut;

	_enemyManager->setPlayerMemoryAddressLink(_player);
	_player->setEnemyManagerAddressLink(_enemyManager);
	_player->setMapManagerAddressLink(_dungeon2F);
	_enemyManager->setDungeonMapAddressLink(_dungeon2F);

	_dungeon2F->setDungeonFloor(DUNGEON_FLOOR::SECOND_FLOOR);
	_dungeon2F->init(_dungeon2F->getDungeonFloor());
	_player->init(false);
	_enemyManager->init();
	_itemManager->init();
	_enemyManager->setEnemy();
	_clockFade->init();

	IMAGEMANAGER->findImage("black")->setAlpahBlend(true);

	_alphaValue = 0;
	_goal.x = 1000.f;
	_goal.y = 30.f;

	_camera->init(GAMESIZEX, GAMESIZEY, 2240, 1600);

	_clockFade->setClockFadeOut(false);
	_clockFade->setClockFadeIn(true);

	_dungeonUp = RectMake(832, 96 , 64, 64);
	_dungeonDown = RectMake(928 , 1568 , 192, 32);

	//_player->setPlayerDirection(UP);
	//_player->setPlayerPosX(1020);
	//_player->setPlayerPosY(1460);

	_sceneChange = false;
	_worldTime = 0;
	_once = false;
	_dungeonDownBool = false;
	_dungeonUpBool = false;
	_alphaBlendOut = false;

	_dungeonDownBool = false;
	_dungeonUpBool = false;

	_dungeDownJumpRc = RectMake(100, 350, 170, 100);
	_dungeUnMove = RectMake(100, 440, 180, 50);

	playerSceneLoad();

	_player->setPlayerCurrentScene(PLAYERSCENE::DUNGEON_2F);

	if (_player->getPlayerX() < 0 || _player->getPlayerX() > 2240 || _player->getPlayerY() < 0 || _player->getPlayerY() > 1600 || (_player->getPlayerX() == 0 && _player->getPlayerY() == 0))
	{
		_player->setPlayerPosX(1020);
		_player->setPlayerPosY(1460);
	}


	return S_OK;
}

void dungeon2F::release()
{
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_player);
	SAFE_DELETE(_dungeon2F);
	SAFE_DELETE(_camera);
	SAFE_DELETE(_itemManager);
	SAFE_DELETE(_clockFade);
}

void dungeon2F::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_enemyManager->update();
	_itemManager->update();
	itemRandomDrop();
	playerItemGet();
	_clockFade->update();
	alphaBlend();

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

	_dungeDownJumpRc = RectMake(100 - _camera->getCameraX(), 350 - _camera->getCameraY(), 170, 100);
	_dungeUnMove = RectMake(100 - _camera->getCameraX(), 440 - _camera->getCameraY(), 180, 50);

	_player->playerDungeonFall(_dungeDownJumpRc, _dungeUnMove);

	//==============밑에 작성 금지===============
	dungeonChange();
	if (!_sceneChange)
	{
		_player->update(true, 1);
	}

	EFFECTMANAGER->update();
}

void dungeon2F::render()
{
	_dungeon2F->render(_camera->getCameraX(), _camera->getCameraY());
	_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
	_itemManager->render(_camera->getCameraX(), _camera->getCameraY());
	playerDead();
	_player->render(_camera->getCameraX(), _camera->getCameraY(), true);

	if (_player->getPlayerHP() > 0)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				if (i == 0)
				{
					IMAGEMANAGER->findImage("타일맵2")->frameRender(getMemDC(), 896 - _camera->getCameraX(), 32 - _camera->getCameraY(), 7, 15);
				}
				else
				{
					IMAGEMANAGER->findImage("타일맵")->frameRender(getMemDC(), 896 + 32 * j - _camera->getCameraX(), 32 + 32 * i - _camera->getCameraY(), 24 + j, 8 + i);
				}
			}
		}
	}
	//Rectangle(getMemDC(), _dungeDownJumpRc);
	//Rectangle(getMemDC(), _dungeUnMove);

	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), _alphaValue);
	_clockFade->render();
	EFFECTMANAGER->render();
}

void dungeon2F::playerSceneSave()
{
	HANDLE file;
	DWORD save;

	file = CreateFile("saveFile/playerScene.txt", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int scene = (int)_player->getPlayerCurrentScene();

	WriteFile(file, &scene, sizeof(int), &save, NULL);

	CloseHandle(file);
}

void dungeon2F::playerSceneLoad()
{
	HANDLE file;
	DWORD load;

	int scene;

	file = CreateFile("saveFile/playerScene.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &scene, sizeof(int), &load, NULL);

	if (scene > 7)
	{
		scene = (int)PLAYERSCENE::DUNGEON_1F;
	}

	_player->setPlayerCurrentScene((PLAYERSCENE)scene);

	if (_player->getPlayerCurrentScene() == PLAYERSCENE::DUNGEON_1F)
	{
		_player->setPlayerDirection(UP);
		_player->setPlayerPosX(1020);
		_player->setPlayerPosY(1460);
	}

	if (_player->getPlayerCurrentScene() == PLAYERSCENE::BOSS)
	{
		_player->setPlayerDirection(DOWN);
		_player->setPlayerPosX(862);
		_player->setPlayerPosY(192);
		_clockFade->setClockFadeIn(false);
		_alphaValue = 255;
		_alphaBlendOut = true;
	}

	CloseHandle(file);
}

void dungeon2F::dungeonChange()
{
	RECT temp;

	//보스룸갈때
	if (IntersectRect(&temp, &_player->getPlayerRc(), &_dungeonUp))
	{
		_dungeonUpBool = true;
	}
	if (_dungeonUpBool)
	{
		if (!_once)
		{
			_worldTime = TIMEMANAGER->getWorldTime();
			_angle = getAngle(_player->getPlayerX(), _player->getPlayerY(), _goal.x, _goal.y);
			_distance = getDistance(_player->getPlayerX(), _player->getPlayerY(), _goal.x, _goal.y);
			_speed = _distance * (TIMEMANAGER->getElapsedTime() / 3.3f);
		}
		

		//_clockFade->setClockFadeOut(true);

		if (_alphaValue < 255)
		{
			_alphaValue += 3;
		}

		if (_alphaValue > 255)
		{
			_alphaValue = 255;
		}

		_player->setTileCheck(false);
		_player->setPlayerUnMove(true);
		_player->setPlayerDirection(UP);
		_player->setPlayerPosX(_player->getPlayerX() + cosf(_angle) * _speed);
		_player->setPlayerPosY(_player->getPlayerY() - sinf(_angle) * _speed);



		if (1.4f + _worldTime <= TIMEMANAGER->getWorldTime())
		{
			playerSceneSave();
			_sceneChange = true;
			_player->playerSave();
			SOUNDMANAGER->stop("theTower");
			SCENEMANAGER->changeScene("bossScene");
		}

		_once = true;
	}


	if (!_sceneChange)
	{
		//1층갈때
		if (IntersectRect(&temp, &_player->getPlayerRc(), &_dungeonDown))
		{
			_dungeonDownBool = true;
		}

		if (_dungeonDownBool)
		{
			_player->setTileCheck(false);
			_player->setPlayerUnMove(true);
			_player->setPlayerDirection(DOWN);
			_player->setPlayerPosY(_player->getPlayerY() + 3);

			if (!_once)
			{
				_worldTime = TIMEMANAGER->getWorldTime();
			}
			_clockFade->setClockFadeOut(true);


			if (1.4f + _worldTime <= TIMEMANAGER->getWorldTime())
			{
				playerSceneSave();
				_sceneChange = true;
				_player->playerSave();
				SCENEMANAGER->changeScene("dungeon");
			}

			_once = true;
		}
	}

}

void dungeon2F::alphaBlend()
{
	if (_alphaBlendOut)
	{
		if (_alphaValue > 0)
		{
			_alphaValue -= 3;
		}

		if (_alphaValue <= 0)
		{
			_alphaValue = 0;
			_alphaBlendOut = false;
		}
	}

	if (_alphaBlendOut && _dungeonUpBool)
	{
		_alphaValue += 3;
	}
}

void dungeon2F::playerDead()
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

void dungeon2F::itemRandomDrop()
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

void dungeon2F::playerItemGet()
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

void dungeon2F::setWindowsSize(int x, int y, int width, int height)
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
