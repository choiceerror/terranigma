#include "stdafx.h"
#include "Bird.h"

Bird::Bird()
{
}

Bird::~Bird()
{
}

HRESULT Bird::init(string npcName, const char* imageName, float x, float y, int idX, int idY)
{
	npc::init(npcName, imageName, x, y, idX, idY);

	_npc.x = x;
	_npc.y = y;
	_npc.name = npcName;
	_npc.state = BIRD_IDLE;
	_npc.direction = NPC_DOWN;

	int idleLeft[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleLeft", imageName, idleLeft, 1, 5, true);
	int idleRight[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleRight", imageName, idleRight, 1, 5, true);
	int idleUp[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleUp", imageName, idleUp, 1, 5, true);
	int idleDown[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "idleDown", imageName, idleDown, 1, 5, true);
	int peckLeft[] = { 8, 9 ,10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "peckLeft", imageName, peckLeft, 4, 5, false);
	int peckRight[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "peckRight", imageName, peckRight, 4, 5, true);
	int peckUp[] = { 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "peckUp", imageName, peckUp, 2, 5, true);
	int peckDown[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "peckDown", imageName, peckDown, 4, 5, true);
	int moveLeft[] = { 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveLeft", imageName, moveLeft, 4, 5, true);
	int moveRight[] = { 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveRight", imageName, moveRight, 4, 5, true);
	int moveUp[] = { 24, 25, 26 , 27 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveUp", imageName, moveUp, 4, 5, true);
	int moveDown[] = { 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "moveDown", imageName, moveDown, 4, 5, true);

	_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "idleDown");

	_npc.rc = RectMakeCenter(_npc.x, _npc.y, 30, 30);


	return S_OK;
}

void Bird::release()
{
}

void Bird::update()
{
	npc::update();
	birdState();

	_npc.rc = RectMakeCenter(_npc.x, _npc.y, 32, 32);
}

void Bird::render(float cameraX, float cameraY)
{
	//Rectangle(getMemDC(), _npc.rc);
	//_npc.image->aniRender(getMemDC(), _npc.x - cameraX, _npc.y - cameraY, _npc.ani);
	_npc.image->expandAniRenderCenter(getMemDC(), _npc.x - cameraX, _npc.y - cameraY, _npc.ani, 2, 2);
}

void Bird::birdState()
{
	switch (_npc.state)
	{
	case BIRD_IDLE:
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
	case BIRD_MOVE:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveLeft");
			_npc.ani->start();
			_npc.x -= 1.0f;
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveRight");
			_npc.ani->start();
			_npc.x += 1.0f;
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveUp");
			_npc.ani->start();
			_npc.y -= 1.0f;
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "moveDown");
			_npc.ani->start();
			_npc.y += 1.0f;
			break;
		}
		break;
	case BIRD_PECK:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "peckLeft");
			_npc.ani->start();
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "peckRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "peckUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "peckDown");
			_npc.ani->start();
			break;
		}
		break;
	}
}
