#pragma once
#include "gameNode.h"


class messageSpear : public gameNode
{
private:
	char _bird[128];
	char _birdTitle[128];
	char _birdMessage[256];

	char _elder[128];
	char _elderTitle[128];
	char _elderMessage[256];

	char _elle[128];
	char _elleTitle[128];
	char _elleMessage[256];

	char _grandfa[128];
	char _grandfaTitle[128];
	char _grandfaMessage[256];

	char _grandma[128];
	char _grandmaTitle[128];
	char _grandmaMessage[256];

	char _fishMan[128];
	char _fishManTitle[128];
	char _fishManMessage[256];

	char _maid[128];
	char _maidTitle[128];
	char _maidMessage[256];

	char _townMan[128];
	char _townManTitle[128];
	char _townManMessage[256];
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

