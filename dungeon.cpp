#include "stdafx.h"
#include "dungeon.h"


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
	_player->init();
	_enemyManager->init();
	_itemManager->init();
	_enemyManager->setEnemy();
	_clockFade->init();

	_camera->init(GAMESIZEX, GAMESIZEY, GAMESIZEX, 3200);

	//_clockFade->setClockFadeIn(true);
	//_clockFade->setClockFadeOut(false);
	return S_OK;
}

void dungeon::release()
{
	//SAFE_DELETE(_enemyManager);
	//SAFE_DELETE(_player);
	//SAFE_DELETE(_dungeon);
	//SAFE_DELETE(_camera);
}

void dungeon::update()
{
	_camera->update(_player->getPlayerX(), _player->getPlayerY());
	_player->update(false, 1);
	_enemyManager->update();
	_itemManager->update();
	itemRandomDrop();
	playerItemGet();
	_clockFade->update();
}

void dungeon::render()
{
	_dungeon->render(_camera->getCameraX(), _camera->getCameraY());
	_enemyManager->render(_camera->getCameraX(), _camera->getCameraY());
	_itemManager->render(_camera->getCameraX(), _camera->getCameraY());
	_player->render(_camera->getCameraX(), _camera->getCameraY());
	_clockFade->render();
	//char str[100];
	//sprintf_s(str, "%d", _player->getInventory()->getPotionCount());
	//TextOut(getMemDC(), 120, 120, str, strlen(str));

}

void dungeon::itemRandomDrop()
{
	for (int i = 0; i < _enemyManager->getVEnemyDeadPoint().size(); i++)
	{
		_rndItemDrop = RND->getRandomInt(0, 300);
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
