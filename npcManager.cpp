#include "stdafx.h"
#include "npcManager.h"


npcManager::npcManager()
{
}


npcManager::~npcManager()
{
}

HRESULT npcManager::init()
{
	_randomFunction = new randomFunction;

	_aiDirectionPatten = _aiStatePatten = _aiIdleActionPatten = _aiDirectionPattenOldTime = _aiStatePattenOldTime =  0;


	return S_OK;
}

void npcManager::release()
{
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

void npcManager::update()
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

			bird->init("birdAni", "bird", 300 + j * 100, 300 + i * 100, j, i);
			_vBird.push_back(bird);
		}
	}
}

void npcManager::setElder()
{
	Elder* elder;
	elder = new Elder;
	elder->init("elderAni", "elder", 200, 200, 0, 0);
	_vElder.push_back(elder);
		
}

void npcManager::setElle()
{
	Elle* elle;
	elle = new Elle;
	elle->init("elleAni", "elle", 400, 400, 0, 0);
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

	for (int i = 0; i < _vBird.size(); i++)
	{

		if (GetTickCount() - _aiDirectionPattenOldTime >= 1 * 1000)
		{
			_aiDirectionPatten = _randomFunction->getRandomInt(0, 3);
			_aiIdleActionPatten = _randomFunction->getRandomInt(0, 2);
			_aiDirectionPattenOldTime = GetTickCount();

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
		}
		

		if (GetTickCount() - _aiStatePattenOldTime >= 2 * 1000)
		{
			_aiStatePatten = _randomFunction->getRandomInt(0, 2);
			_aiStatePattenOldTime = GetTickCount();

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

void npcManager::aiElderUpdate()
{
}
