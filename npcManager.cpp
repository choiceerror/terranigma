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

	return S_OK;
}

void npcManager::release()
{
	for (_viBird = _vBird.begin(); _viBird != _vBird.end(); _viBird++)
	{
		SAFE_DELETE((*_viBird));
	}
}

void npcManager::update()
{

}

void npcManager::render(float cameraX, float cameraY)
{
	for (_viBird = _vBird.begin(); _viBird != _vBird.end(); _viBird++)
	{
		(*_viBird)->render(cameraX, cameraY);
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

			bird->init("birdAni", "bird", 100 + j * 100, 100 + i * 100, j, i);
			_vBird.push_back(bird);
		}
	}
}
