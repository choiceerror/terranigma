#include "stdafx.h"
#include "npc.h"


npc::npc()
{
}


npc::~npc()
{
}

HRESULT npc::init(string npcName, const char* imageName, float x, float y, int idX, int idY)
{
	_npc.name = npcName;
	_npc.x = x;
	_npc.y = y;
	_npc.speed = 2.0f;
	_npc.idX = idX;
	_npc.idY = idY;
	_npc.image = IMAGEMANAGER->findImage(imageName);

	return S_OK;
}

void npc::release()
{
}

void npc::update()
{

}

void npc::render()
{

}
