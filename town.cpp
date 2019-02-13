#include "stdafx.h"
#include "town.h"


town::town()
{
}


town::~town()
{
}

HRESULT town::init()
{
	_player = new player;
	_player->init();

	_playerWorldMap = new PlayerWorldMap;
	_playerWorldMap->init();
	return S_OK;
}

void town::release()
{
}

void town::update()
{
	_player->update();
	_playerWorldMap->update();
}

void town::render()
{
	_player->render(0 , 0);
	//_playerWorldMap->render(0, 0);
}
