#pragma once
#include "gameNode.h"

enum class ITEMTYPE
{
	NONE,
	WEAPON,
	ARMOR,
	ACCESSORY,
	GOLD,
	POTION
};

struct tagItem
{
	const char* imageName;
	float x, y;
	float viewX, viewY;
	int frameX, frameY;
	ITEMTYPE itemType;
	RECT rc;
	image* image;

	bool isLive;
};

class item : public gameNode
{
protected:
	tagItem _item;



public:
	item();
	~item();

	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();


	//================접근자 설정자================

	tagItem getTagItem() { return _item; }

	//x,y
	float getItemX() { return _item.x; }
	void setItemX(float x) { _item.x = x; }
	float getItemY() { return _item.y; }
	void setItemY(float y) { _item.y = y; }
	//viewX,viewY
	float getItemViewX() { return _item.viewX; }
	void setItemViewX(float viewX) { _item.viewX = viewX; }
	float getItemViewY() { return _item.viewY; }
	void setItemViewY(float viewY) { _item.viewY = viewY; }
	//frameX,frameY
	float getItemFrameX() { return _item.frameX; }
	void setItemFrameX(float frameX) { _item.frameX = frameX; }
	float getItemFrameY() { return _item.frameY; }
	void setItemFrameY(float frameY) { _item.frameY = frameY; }


};

