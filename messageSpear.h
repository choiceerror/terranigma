#pragma once
#include "gameNode.h"


class messageSpear : public gameNode
{
private:
	int _count;
public:
	messageSpear();
	~messageSpear();

	HRESULT init();
	void release();
	void update();
	void render();

	void grandfaMessage();
	void grandmaMessage();
	void birdMessage();
	void elderMessage();
	void elleMessage();
	void fishManMessage();
	void maidMessage();

};

