#pragma once
#include "gameNode.h"

struct tagItem
{
	const char* imageName;
	float x, y;
	float viewX, viewY;
	int frameX, frameY;
	int itemType;
};




class item : public gameNode
{
protected:
	tagItem* _item;



public:
	item();
	~item();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render();
};

