#pragma once
#include "gameNode.h"

enum NPCDIRECTION
{
	NPC_LEFT = 0,
	NPC_RIGHT,
	NPC_UP,
	NPC_DOWN

};

enum NPCSTATE
{
	//꼬꼬
	BIRD_IDLE,
	BIRD_MOVE,
	BIRD_PECK,

	//할부지
	ELDER_IDLE,
	ELDER_SIT,
	ELDER_MOVE,

	//엘
	ELLE_IDLE,
	ELLE_MOVE,

	//마을주민(메이드)
	TOWNHUMAN_MAID_IDLE,
	TOWNHUMAN_MAID_MOVE,
	TOWNHUMAN_MAID_IDLEACTION,

	//마을주민(할무이)
	TOWNHUMAN_GRANDMA_IDLE,

	//마을주민(할부지)
	TOWNHUMAN_GRANDFA_IDLE,

	//마을주민(낚시꾼)
	TOWNHUMAN_FISHMAN_IDLE,

	//마을주민(평범)
	TOWNHUMAN_TOWNMAN_IDLE,
	TOWNHUMAN_TOWNMAN_MOVE
};

enum TOWNHUMAN
{
	TOWN_MAID = 0,
	TOWN_GRANDMA,
	TOWN_GRANDFA,
	TOWN_FISHMAN,
	TOWN_TOWNMAN,
	TOWN_BIRD,
	TOWN_ELDER,
	TOWN_ELLE
};

struct TagNPC
{
	string name;
	image* image;
	animation* ani;
	NPCDIRECTION direction;
	NPCSTATE state;
	TOWNHUMAN townNumber;
	RECT rc;
	float x, y;
	float speed;
	int idX, idY;
};

class npc : public gameNode
{
protected:
	TagNPC _npc;

public:
	npc();
	~npc();

	HRESULT init(string npcName, const char* imageName, float x, float y, int idX, int idY);
	void release();
	void update();
	void render();

	void npcMove();


public:   //접근자 설정자 모음

	void setNPCDirection(NPCDIRECTION direction) { _npc.direction = direction; }
	void setNPCState(NPCSTATE state) { _npc.state = state; }
	void setNPCPosX(float x) { _npc.x = x; }
	void setNPCPosY(float y) { _npc.y = y; }
	void setNPCSpeed(float speed) { _npc.speed = speed; }
	void setNPCIdX(int idX) { _npc.idX = idX; }
	void setNPCIdY(int idY) { _npc.idY = idY; }


	NPCDIRECTION getNPCDirection() { return _npc.direction; }
	NPCSTATE getNPCState() { return _npc.state; }
	RECT getRect() { return _npc.rc; }
	float getNPCPosX() { return _npc.x; };
	float getNPCPosY() { return _npc.y; };
	float getNPCSpeed() { return _npc.speed; }
	int getNPCIdX() { return _npc.idX; }
	int getNPCIdY() { return _npc.idY; }
};