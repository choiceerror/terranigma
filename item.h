#pragma once
#include "gameNode.h"
#include <vector>

struct tagItem
{
	const char* imageName;
	float x, y;
	int frameX, frameY;
	int itemType;
};

enum ITEMTYPE
{
	NONE,
	ARMOR,
	WEAPON,
	GOLD,
	POTION
};


class item : public gameNode
{
	vector<tagItem*>		_vItem;
	vector<tagItem*>::iterator	_viItem;



public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

	void dropItem(const char* imageName, float x, float y,int frameX,int frameY);
};

