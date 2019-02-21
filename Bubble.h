#pragma once
#include "gameNode.h"

struct tagBubble
{
	image* image;
	float angle;
	float speed;
	float x;
	float y;
	float startX;
	float startY;
	int frameX;
	int frameY;
	bool isLive;
	int count;
	const char* imageName;

};


class Bubble : public gameNode
{
private:
	vector<tagBubble*> _vBubble;

	int _count;

public:
	Bubble();
	~Bubble();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	void createBubble(float x, float y, int frameX, int frameY);

	void eraseBubble();
};

