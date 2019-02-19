#include "stdafx.h"
#include "Elle.h"

Elle :: Elle()
{

}
Elle :: ~Elle()
{

}

HRESULT Elle::init(string npcName, const char* imageName, float x, float y, int idX, int idY)
{
	npc::init(npcName, imageName, x, y, idX, idY);

	_npc.x = x;
	_npc.y = y;
	_npc.name = npcName;
	_npc.state = ELLE_IDLE;
	_npc.direction = NPC_DOWN;

	int idleLeft[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleLeft", imageName, idleLeft, 1, 5, true);
	int idleRight[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleRight", imageName, idleRight, 1, 5, true);
	int idleUp[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleUp", imageName, idleUp, 1, 5, true);
	int idleDown[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleDown", imageName, idleDown, 1, 5, true);
	int moveLeft[] = { 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveLeft", imageName, moveLeft, 4, 5, true);
	int moveRight[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveRight", imageName, moveRight, 4, 5, true);
	int moveUp[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveUp", imageName, moveUp, 4, 5, true);
	int moveDown[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveDown", imageName, moveDown, 4, 5, true);


	_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "idleDown");

	_npc.rc = RectMakeCenter(_npc.x, _npc.y, 32, 32);

	return S_OK;
}

void Elle::release()
{
}

void Elle::update()
{
	npc::update();
	elleState();

	_npc.rc = RectMakeCenter(_npc.x, _npc.y + 10, 32, 62);
}

void Elle::render(float cameraX, float cameraY)
{
	//Rectangle(getMemDC(), _npc.rc);
	_npc.image->expandAniRenderCenter(getMemDC(), _npc.x - cameraX, _npc.y - cameraY, _npc.ani, 2, 2);
}

void Elle::elleState()
{
	switch (_npc.state)
	{
	case ELLE_IDLE:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "idleLeft");
			_npc.ani->start();
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "idleRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "idleUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "idleDown");
			_npc.ani->start();
			break;
		}
		break;
	case ELLE_MOVE:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveLeft");
			_npc.ani->start();
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveDown");
			_npc.ani->start();
			break;
		}
		break;
	}
}
