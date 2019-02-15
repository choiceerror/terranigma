#include "stdafx.h"
#include "Elder.h"

Elder::Elder()
{
}

Elder::~Elder()
{
}

HRESULT Elder::init(string npcName, const char* imageName, float x, float y, int idX, int idY)
{
	npc::init(npcName, imageName, x, y, idX, idY);

	_npc.x = x;
	_npc.y = y;
	_npc.name = npcName;
	_npc.state = ELDER_SIT;
	_npc.direction = NPC_DOWN;

	int idleDown[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleDown", imageName, idleDown, 1, 5, true);
	int idleUp[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleUp", imageName, idleUp, 1, 5, true);
	int moveUp[] = { 7, 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveUp", imageName, moveUp, 4, 5, true);
	int moveDown[] = { 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveDown", imageName, moveDown, 4, 5, true);
	int sitRight[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "sitRight", imageName, sitRight, 1, 5, true);
	int sitUp[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "sitUp", imageName, sitUp, 1, 5, true);
	int sitDown[] = {0 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "sitDown", imageName, sitDown, 1, 5, true);
	return S_OK;

	_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "sitDown");

	_npc.rc = RectMakeCenter(_npc.x, _npc.y, 32, 32);
}

void Elder::release()
{
}

void Elder::update()
{
	npc::update();
	elderState();

	_npc.rc = RectMakeCenter(_npc.x, _npc.y, 32, 32);
}

void Elder::render(float cameraX, float cameraY)
{
	//Rectangle(getMemDC(), _npc.rc);
	_npc.image->expandAniRenderCenter(getMemDC(), _npc.x - cameraX, _npc.y - cameraY, _npc.ani, 2, 2);
}

void Elder::elderState()
{
	switch (_npc.state)
	{
	case ELDER_IDLE:
		switch (_npc.direction)
		{
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
	case ELDER_MOVE:
		switch (_npc.direction)
		{
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "MoveUp");
			_npc.ani->start();
			_npc.y -= 1.0f;
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "MoveDown");
			_npc.ani->start();
			_npc.y += 1.0f;
			break;
		}
		break;
	case ELDER_SIT:
		switch (_npc.direction)
		{
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "sitRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "sitUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "sitDown");
			_npc.ani->start();
			break;
		}
		break;
	}
}
