#pragma once
#include "item.h"

class Gold : public item
{
private:
	int _goldNum;

public:
	Gold();
	~Gold();

	virtual HRESULT init(const char* imageName, float x, float y, int frameX, int frameY);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	int getGoldNum() { return _goldNum; }
	void setGoldNum(int goldNum) { _goldNum = goldNum; }
};

