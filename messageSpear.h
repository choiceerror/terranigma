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

	int _soundOnce;

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
	void getGuardianPageNext(bool pageNext) { _guardianPageNext = pageNext; }

	bool getElder() { return _elderTalk; }
	void setElder(bool a) { _elderTalk = a; }

	bool getBird() { return _birdTalk; }
	void setBird(bool a) { _birdTalk = a; }

	bool getElle() { return _elleTalk; }
	void setElle(bool a) { _elleTalk = a; }

	bool getGrandFa() { return _grandfaTalk; }
	void setGrandFa(bool a) { _grandfaTalk = a; }

	bool getFishMan() { return _fishManTalk; }
	void setFishMan(bool a) { _fishManTalk = a; }

	bool getGrandMa() { return _grandmaTalk; }
	void setGrandMa(bool a) { _grandmaTalk = a; }

	bool getOn() { return _once; }
	void setOn(bool a) { _once = a; }

	bool getPage() { return _pageOn; }
	void setPage(bool a) { _pageOn = a; }

};

