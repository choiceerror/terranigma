#pragma once
#include "gameNode.h"



class messageSpear : public gameNode
{
private:
	int _count;
	HFONT _font;
	HFONT _oldFont;

	int _talkCount, _talkCount2;

	int _texOldTime;

	int _pageFrameX;

	bool _once;

	bool _pageOn;

	bool _birdTalk, _elderTalk, _elleTalk, _maidTalk,
		_grandfaTalk, _grandmaTalk, _fishManTalk, _townManTalk, _guardianTalk; 

	int _guardianTalkCount[2], _pageNext = 0;
	int _sizeNum[8], _num = 0;
	bool _playerKey, _guardianPageNext;

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
	void townManMessage();
	void guardianMessage(); 


	void messageRender(const char* txtName, bool messageBool, int timeNum, int timeNum2, int nameTrue);
	void guardianMessageRender(bool guardian, bool playeyKey);

public:
	
	void getPlayerKey(bool playerKey) { _playerKey = playerKey; }
	void getGuardianPageNext(bool pageNext) { _guardianPageNext = pageNext;  }
};

