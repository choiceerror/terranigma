#pragma once
#include "gameNode.h"

enum NPCDIRECTION
{
	//部部
	BIRD_LEFT,
	BIRD_RIGHT,
	BIRD_UP,
	BIRD_DOWN,

	//且何瘤
	ELDER_LEFT,
	ELDER_RIGHT,
	ELDER_UP,
	ELDER_DOWN,

	//郡
	ELLE_LEFT,
	ELLE_RIGHT,
	ELLE_UP,
	ELLE_DOWN,

	//付阑林刮
	TOWNHUMAN_LEFT,
	TOWNHUMAN_RIGHT,
	TOWNHUMAN_UP,
	TOWNHUMAN_DOWN
};

enum NPCSTATE
{
	//部部
	BIRD_IDLE,
	BIRD_MOVE,
	BIRD_PECK,

	//且何瘤
	ELDER_IDLE,
	ELDER_SIT,
	ELDER_MOVE,

	//郡
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
};