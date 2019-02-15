#pragma once
#include "gameNode.h"

enum NPCDIRECTION
{
	//²¿²¿
	BIRD_LEFT,
	BIRD_RIGHT,
	BIRD_UP,
	BIRD_DOWN,

	//ÇÒºÎÁö
	ELDER_LEFT,
	ELDER_RIGHT,
	ELDER_UP,
	ELDER_DOWN,

	//¿¤
	ELLE_LEFT,
	ELLE_RIGHT,
	ELLE_UP,
	ELLE_DOWN,

	//¸¶À»ÁÖ¹Î
	TOWNHUMAN_LEFT,
	TOWNHUMAN_RIGHT,
	TOWNHUMAN_UP,
	TOWNHUMAN_DOWN
};

enum NPCSTATE
{
	//²¿²¿
	BIRD_IDLE,
	BIRD_MOVE,
	BIRD_PECK,

	//ÇÒºÎÁö
	ELDER_IDLE,
	ELDER_SIT,
	ELDER_MOVE,

	//¿¤
	ELLE_IDLE,
	ELLE_MOVE
};

struct TagNPC
{
	string name;
	image* image;
	animation* ani;
	NPCDIRECTION direction;
	NPCSTATE state;
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


public:   //Á¢±ÙÀÚ ¼³Á¤ÀÚ ¸ðÀ½

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