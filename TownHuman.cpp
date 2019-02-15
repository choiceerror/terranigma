#include "stdafx.h"
#include "TownHuman.h"

TownHuman::TownHuman()
{
}

TownHuman::~TownHuman()
{
}

HRESULT TownHuman::init(TOWNHUMAN townName, string npcName, const char* imageName, float x, float y, int idX, int idY)
{
	npc::init(npcName, imageName, x, y, idX, idY);

	_npc.x = x;
	_npc.y = y;
	_npc.name = npcName;
	_npc.townNumber = townName;
	_npc.direction = NPC_DOWN;
	
	//¸ŞÀÌµå
	int maidIdleLeft[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidIdleLeft", imageName, maidIdleLeft, 1, 5, true);
	int maidIdleRight[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidIdleRight", imageName, maidIdleRight, 1, 5, true);
	int maidIdleUp[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidIdleUp", imageName, maidIdleUp, 1, 5, true);
	int maidIdleDown[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidIdleDown", imageName, maidIdleDown, 1, 5, true);
	int maidMoveLeft[] = { 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidMoveLeft", imageName, maidMoveLeft, 3, 5, true);
	int maidMoveRight[] = { 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidMoveRight", imageName, maidMoveRight, 3, 5, true);
	int maidMoveUp[] = { 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidMoveUp", imageName, maidMoveUp, 3, 5, true);
	int maidMoveDown[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidMoveDown", imageName, maidMoveDown, 3, 5, true);
	int maidSleep[] = { 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "maidSleep", imageName, maidSleep, 2, 5, true);

	int mamaIdle[] = { 14, 15, 16 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "mamaIdle", imageName, mamaIdle, 3, 5, true);

	int fafaIdle[] = { 28, 29, 30 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "fafaIdle", imageName, fafaIdle, 3, 5, true);

	int fishIdle[] = { 42, 43, 44, 45, 46 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "fishIdle", imageName, fishIdle, 5, 5, true);

	int townManIdleLeft[] = { 63 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManIdleLeft", imageName, townManIdleLeft, 1, 5, true);
	int townManIdleRight[] = { 66 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManIdleRight", imageName, townManIdleRight, 1, 5, true);
	int townManIdleUp[] = { 60 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManIdleUp", imageName, townManIdleUp, 1, 5, true);
	int townManIdleDown[] = { 57 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManIdleDown", imageName, townManIdleDown, 1, 5, true);
	int townManMoveLeft[] = { 62, 63, 64 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManMoveLeft", imageName, townManMoveLeft, 3, 5, true);
	int townManMoveRight[] = { 65, 66, 67 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManMoveRight", imageName, townManMoveRight, 3, 5, true);
	int townManMoveUp[] = { 59, 60, 61 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManMoveUp", imageName, townManMoveUp, 3, 5, true);
	int townManMoveDown[] = { 56, 57, 58 };
	KEYANIMANAGER->addArrayFrameAnimation(_npc.name, "townManMoveDown", imageName, townManMoveDown, 3, 5, true);

	switch (townName)
	{
	case TOWN_MAID:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidIdleDown");
		break;
	case TOWN_GRANDMA:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "mamaIdle");
		break;
	case TOWN_GRANDFA:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "fafaIdle");
		break;
	case TOWN_FISHMAN:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "fishIdle");
		break;
	case TOWN_TOWNMAN:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManIdleDown");
		break;
	}


	_npc.rc = RectMakeCenter(_npc.x, _npc.y, 30, 30);


	return S_OK;
}

void TownHuman::release()
{
}

void TownHuman::update()
{
	npc::update();
	townHumanState();

	_npc.rc = RectMakeCenter(_npc.x, _npc.y, 32, 32);
}

void TownHuman::render(float cameraX, float cameraY)
{
	//Rantangle(getMemDC(), _npc.rc);
	_npc.image->expandAniRenderCenter(getMemDC(), _npc.x - cameraX, _npc.y - cameraY, _npc.ani, 2, 2);

}

void TownHuman::townHumanState()
{
	switch (_npc.state)
	{
	case TOWNHUMAN_MAID_IDLE:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidIdleLeft");
			_npc.ani->start();
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidIdleRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidIdleUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidIdleDown");
			_npc.ani->start();
			break;
		}
		break;
	case TOWNHUMAN_MAID_MOVE:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidMoveLeft");
			_npc.ani->start();
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidMoveRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidMoveUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidMoveDown");
			_npc.ani->start();
			break;
		}
		break;
	case TOWNHUMAN_MAID_IDLEACTION:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "maidSleep");
		_npc.ani->start();
		break;
	case TOWNHUMAN_GRANDMA_IDLE:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "mamaIdle");
		_npc.ani->start();
		break;
	case TOWNHUMAN_GRANDFA_IDLE:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "fafaIdle");
		_npc.ani->start();
		break;
	case TOWNHUMAN_FISHMAN_IDLE:
		_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "fishIdle");
		_npc.ani->start();
		break;
	case TOWNHUMAN_TOWNMAN_IDLE:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManIdleLeft");
			_npc.ani->start();
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManIdleRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManIdleUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManIdleDown");
			_npc.ani->start();
			break;
		}
		break;
	case TOWNHUMAN_TOWNMAN_MOVE:
		switch (_npc.direction)
		{
		case NPC_LEFT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManMoveLeft");
			_npc.ani->start();
			break;
		case NPC_RIGHT:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManMoveRight");
			_npc.ani->start();
			break;
		case NPC_UP:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManMoveUp");
			_npc.ani->start();
			break;
		case NPC_DOWN:
			_npc.ani = KEYANIMANAGER->findAnimation(_npc.name, "townManMoveDown");
			_npc.ani->start();
			break;
		}
		break;
	}
}
