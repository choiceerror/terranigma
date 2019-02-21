#include "stdafx.h"
#include "npcManager.h"
#include "townMap.h"

npcManager::npcManager()
{
}


npcManager::~npcManager()
{
}

HRESULT npcManager::init()
{
	_randomFunction = new randomFunction;

	_aiDirectionPatten = _aiStatePatten = _aiIdleActionPatten = _aiStatePattenOldTime = 0;

	_randCheck = false;

	return S_OK;
}

void npcManager::release()
{
	SAFE_DELETE(_randomFunction);
	for (_viBird = _vBird.begin(); _viBird != _vBird.end(); _viBird++)
	{
		SAFE_DELETE((*_viBird));
	}
	for (_viElder = _vElder.begin(); _viElder != _vElder.end(); _viElder++)
	{
		SAFE_DELETE((*_viElder));
	}
	for (_viElle = _vElle.begin(); _viElle != _vElle.end(); _viElle++)
	{
		SAFE_DELETE((*_viElle));
	}
	for (_viTownHuman = _vTownHuman.begin(); _viTownHuman != _vTownHuman.end(); _viTownHuman++)
	{
		SAFE_DELETE((*_viTownHuman));
	}
}

void npcManager::update(int check)
{
	for (_viBird = _vBird.begin(); _viBird != _vBird.end(); _viBird++)
	{
		(*_viBird)->update();
	}
	for (_viElder = _vElder.begin(); _viElder != _vElder.end(); _viElder++)
	{
		(*_viElder)->update();
	}
	for (_viElle = _vElle.begin(); _viElle != _vElle.end(); _viElle++)
	{
		(*_viElle)->update();
	}
	for (_viTownHuman = _vTownHuman.begin(); _viTownHuman != _vTownHuman.end(); _viTownHuman++)
	{
		(*_viTownHuman)->update();
	}

	if (check == 2)
	{
		townCheck();
		npcCheck();
	}
}

void npcManager::render(float cameraX, float cameraY)
{
	for (_viBird = _vBird.begin(); _viBird != _vBird.end(); _viBird++)
	{
		(*_viBird)->render(cameraX, cameraY);
	}
	for (_viElder = _vElder.begin(); _viElder != _vElder.end(); _viElder++)
	{
		(*_viElder)->render(cameraX, cameraY);
	}
	for (_viElle = _vElle.begin(); _viElle != _vElle.end(); _viElle++)
	{
		(*_viElle)->render(cameraX, cameraY);
	}
	for (_viTownHuman = _vTownHuman.begin(); _viTownHuman != _vTownHuman.end(); _viTownHuman++)
	{
		(*_viTownHuman)->render(cameraX, cameraY);
	}
}

void npcManager::setBird()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Bird* bird;
			bird = new Bird;

			bird->init("birdAni", "bird", 704 + j * 100, 448 + i * 100, j, i);
			_vBird.push_back(bird);
		}
	}
}

void npcManager::setElder()
{
	Elder* elder;
	elder = new Elder;
	elder->init("elderAni", "elder", 1280, 512, 0, 0);
	_vElder.push_back(elder);

}

void npcManager::setElle()
{
	Elle* elle;
	elle = new Elle;
	elle->init("elleAni", "elle", 384, 1216, 0, 0);
	_vElle.push_back(elle);
}

void npcManager::setTownHuman(TOWNHUMAN townHumanName, float x, float y)
{
	TownHuman* townHuman;
	townHuman = new TownHuman;
	townHuman->init(townHumanName, "townHumanAni", "townHuman", x, y, 0, 0);
	_vTownHuman.push_back(townHuman);
}

void npcManager::aiBirdUpdate()
{
	if (GetTickCount() - _aiStatePattenOldTime >= 1 * 1000)
	{
		for (int i = 0; i < _vBird.size(); i++)
		{
			_aiDirectionPatten = _randomFunction->getRandomInt(0, 3);
			_aiIdleActionPatten = _randomFunction->getRandomInt(0, 2);

			_aiStatePatten = _randomFunction->getRandomInt(0, 2);
			_randCheck = _randomFunction->getRandomInt(0, 1);
			_aiStatePattenOldTime = GetTickCount();

			if (_randCheck)
			{
				switch (_aiDirectionPatten)
				{
				case 0:
					_vBird[i]->setNPCDirection(NPC_LEFT);
				case 1:
					_vBird[i]->setNPCDirection(NPC_RIGHT);
					break;
				case 2:
					_vBird[i]->setNPCDirection(NPC_UP);
					break;
				case 3:
					_vBird[i]->setNPCDirection(NPC_DOWN);
					break;
				}

				if (_aiStatePatten == 0)
				{
					_vBird[i]->setNPCState(BIRD_IDLE);
				}
				else
				{
					if (_aiIdleActionPatten == 0)
					{
						_vBird[i]->setNPCState(BIRD_PECK);
					}
					else _vBird[i]->setNPCState(BIRD_MOVE);
				}
			}
		}
	}
}

void npcManager::aiElderUpdate()
{
}

void npcManager::townCheck()
{
	RECT rc;

	for (int i = 0; i < _vBird.size(); ++i)
	{
		RECT Collision = _vBird[i]->getRect();

		TileX = _vBird[i]->getRect().left / TileSIZE;
		TileY = _vBird[i]->getRect().top / TileSIZE;


		if (_vBird[i]->getNPCDirection() == NPC_LEFT)
		{
			tileIndex[0].x = TileX;
			tileIndex[0].y = TileY;

			for (int j = 0; j < 1; ++j)
			{
				if (_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WALL || _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WATER
					|| _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_SHIRT)
				{
					if (IntersectRect(&rc, &_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->rc, &Collision))
					{
						_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
					}
				}
			}
		}

		if (_vBird[i]->getNPCDirection() == NPC_RIGHT)
		{
			tileIndex[0].x = TileX + 1;
			tileIndex[0].y = TileY;

			for (int j = 0; j < 1; ++j)
			{
				if (_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WALL || _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WATER
					|| _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_SHIRT)
				{
					if (IntersectRect(&rc, &_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->rc, &Collision))
					{
						_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
					}
				}
			}
		}

		if (_vBird[i]->getNPCDirection() == NPC_UP)
		{
			tileIndex[0].x = TileX;
			tileIndex[0].y = TileY;

			for (int j = 0; j < 1; ++j)
			{
				if (_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WALL || _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WATER
					|| _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_SHIRT)
				{
					if (IntersectRect(&rc, &_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->rc, &Collision))
					{
						_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
					}
				}
			}
		}

		if (_vBird[i]->getNPCDirection() == NPC_DOWN)
		{
			tileIndex[0].x = TileX;
			tileIndex[0].y = TileY + 1;

			for (int j = 0; j < 1; ++j)
			{
				if (_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WALL || _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_WATER
					|| _townMap->getTile(tileIndex[j].x, tileIndex[j].y)->obj == OBJ_SHIRT)
				{
					if (IntersectRect(&rc, &_townMap->getTile(tileIndex[j].x, tileIndex[j].y)->rc, &Collision))
					{
						_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
					}
				}
			}
		}
	}
}

void npcManager::npcCheck()
{
	RECT rc;
	for (int i = 0; i < _vBird.size(); ++i)
	{
		for (int j = 0; j < _vElder.size(); ++j)
		{
			if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElder[j]->getRect()) && _vBird[i]->getNPCDirection() == NPC_DOWN)
			{
				_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
			}

			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElder[j]->getRect()) && _vBird[i]->getNPCDirection() == NPC_UP)
			{
				_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElder[j]->getRect()) && _vBird[i]->getNPCDirection() == NPC_RIGHT)
			{
				_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElder[j]->getRect()) && _vBird[i]->getNPCDirection() == NPC_LEFT)
			{
				_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
			}
		}


		for (int k = 0; k < _vElle.size(); ++k)
		{
			if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElle[k]->getRect()) && _vBird[i]->getNPCDirection() == NPC_DOWN)
			{
				_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
			}

			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElle[k]->getRect()) && _vBird[i]->getNPCDirection() == NPC_UP)
			{
				_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElle[k]->getRect()) && _vBird[i]->getNPCDirection() == NPC_RIGHT)
			{
				_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vElle[k]->getRect()) && _vBird[i]->getNPCDirection() == NPC_LEFT)
			{
				_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
			}
		}

		for (int l = 0; l < _vTownHuman.size(); ++l)
		{
			if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vTownHuman[l]->getRect()) && _vBird[i]->getNPCDirection() == NPC_DOWN)
			{
				_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
			}

			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vTownHuman[l]->getRect()) && _vBird[i]->getNPCDirection() == NPC_UP)
			{
				_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vTownHuman[l]->getRect()) && _vBird[i]->getNPCDirection() == NPC_RIGHT)
			{
				_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vTownHuman[l]->getRect()) && _vBird[i]->getNPCDirection() == NPC_LEFT)
			{
				_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
			}
		}


		for (int m = 0; m < _vBird.size(); ++m)
		{
			if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vBird[m]->getRect()) && _vBird[i]->getNPCDirection() == NPC_DOWN)
			{
				if (i == 0 && m == 1)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 0 && m == 2)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 0 && m == 3)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 1 && m == 0)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 1 && m == 2)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 1 && m == 3)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 2 && m == 0)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 2 && m == 1)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 2 && m == 3)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 3 && m == 0)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 3 && m == 1)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}
				else if (i == 3 && m == 2)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() - 2.0f);
				}

			}

			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vBird[m]->getRect()) && _vBird[i]->getNPCDirection() == NPC_UP)
			{
				if (i == 0 && m == 1)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				if (i == 0 && m == 2)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				if (i == 0 && m == 3)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 1 && m == 0)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 1 && m == 2)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 1 && m == 3)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 2 && m == 0)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 2 && m == 1)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 2 && m == 3)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 3 && m == 0)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 3 && m == 1)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
				else if (i == 3 && m == 2)
				{
					_vBird[i]->setNPCPosY(_vBird[i]->getNPCPosY() + 2.0f);
				}
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vBird[m]->getRect()) && _vBird[i]->getNPCDirection() == NPC_RIGHT)
			{
				if (i == 0 && m == 1)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				if (i == 0 && m == 2)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				if (i == 0 && m == 3)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 1 && m == 0)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 1 && m == 2)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 1 && m == 3)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 2 && m == 0)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 2 && m == 1)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 2 && m == 3)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 3 && m == 0)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 3 && m == 1)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
				else if (i == 3 && m == 2)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() - 2.0f);
				}
			}
			else if (IntersectRect(&rc, &_vBird[i]->getRect(), &_vBird[m]->getRect()) && _vBird[i]->getNPCDirection() == NPC_LEFT)
			{
				if (i == 0 && m == 1)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				if (i == 0 && m == 2)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				if (i == 0 && m == 3)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 1 && m == 0)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 1 && m == 2)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 1 && m == 3)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 2 && m == 0)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 2 && m == 1)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 2 && m == 3)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 3 && m == 0)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 3 && m == 1)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
				else if (i == 3 && m == 2)
				{
					_vBird[i]->setNPCPosX(_vBird[i]->getNPCPosX() + 2.0f);
				}
			}
		}
	}
}
