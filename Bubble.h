#pragma once
#include "gameNode.h"

struct tagBubble
{
	image* image;
	float angle;
	float speed;
	float x;
	float y;
};


class Bubble : public gameNode
{
private:
	vector<tagBubble*> _vBubble;

public:
	Bubble();
	~Bubble();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(float cameraX,float cameraY);

	void createBubble();


};

