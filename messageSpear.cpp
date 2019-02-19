#include "stdafx.h"
#include "messageSpear.h"


messageSpear::messageSpear()
{
}


messageSpear::~messageSpear()
{
}

HRESULT messageSpear::init()
{
	//grandfaMessage();
	//grandmaMessage();
	//birdMessage();
	//elderMessage();
	//elleMessage();
	//fishManMessage();
	//maidMessage();
	//guardianMessage();
	
	_once = false;

	_talkCount = _talkCount2 = 0;

	_pageFrameX = 0;

	_birdTalk = _elderTalk = _elleTalk = _maidTalk = false;
	_grandfaTalk = _grandmaTalk = _fishManTalk = _townManTalk = _guardianTalk = false;

	_texOldTime = GetTickCount();

	return S_OK;
}

void messageSpear::release()
{
}

void messageSpear::update()
{

}

void messageSpear::render()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		if(!_grandfaTalk) _grandfaTalk = true;
		else
		{
			_once = true;
			_grandfaTalk = false;
		}
			
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		if (!_grandmaTalk) _grandmaTalk = true;
		else
		{
			_once = true;
			_grandmaTalk = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		if (!_elleTalk) _elleTalk = true;
		else
		{
			_once = true;
			_elleTalk = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		if (!_birdTalk) _birdTalk = true;
		
		else 
		{
			_once = true;
			_birdTalk = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		if (!_fishManTalk) _fishManTalk = true;
		else
		{
			_once = true;
			_fishManTalk = false;
		}
	}
	messageRender("messageFile/할아버지.txt", _grandfaTalk, 8 , 26);
	messageRender("messageFile/할머니.txt", _grandmaTalk, 33, 34);
	messageRender("messageFile/엘.txt", _elleTalk, 14, 31);
	messageRender("messageFile/꼬꼬.txt", _birdTalk, 14, 6);
	messageRender("messageFile/낚시꾼.txt", _fishManTalk, 33, 34);


	if (_once)
	{
		_talkCount = _talkCount2 = 0;
		_once = false;
	}

}

void messageSpear::grandfaMessage()
{
	string message[2];
	
	vector<string> vStr;


	message[0].assign("뭐냐  아크");
	message[1].assign("다신  여기  오지  말라니깐!");

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);

	TXTDATA->txtSave("messageFile/할아버지.txt", vStr);
}

void messageSpear::grandmaMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "아크야  탑에는  절대  가지  말거라";
	message[1] = "위험한  몬스터들이  도사리고  있단다.";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/할머니.txt", vStr);
}

void messageSpear::birdMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "꼬꼬..  꼬꼬..";
	message[1] = "꼬꼬댁";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/꼬꼬.txt", vStr);
}

void messageSpear::elderMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "....";
	message[1] = "넌  왜  그렇게  항상  말썽이냐?";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/장로할아범.txt", vStr);
}

void messageSpear::elleMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "아크야  탑이..";
	message[1] = "무서워..  안좋은  예감이  들어..";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/엘.txt", vStr);
}

void messageSpear::fishManMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "....";
	message[1] = "나와랏  잉어킹!";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/낚시꾼.txt", vStr);
}

void messageSpear::maidMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "";
	message[1] = "";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/메이드.txt", vStr);
}

void messageSpear::guardianMessage()
{
	string message[8];
	vector<string> vStr;

	
	message[0] = "나는  가디언이다";
	message[1] = "이  타워안에는  층이";
	message[2] = "세개로 되어있다.";
	message[3] = "시련을  극복하여";
	message[4] = "세계를  조절하는   힘을  얻어라!";
	message[5] = "이것이 너의 운명이다!";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	vStr.push_back(message[2]);
	vStr.push_back(message[3]);
	vStr.push_back(message[4]);
	vStr.push_back(message[5]);

	TXTDATA->txtSave("messageFile/가디언.txt", vStr);
}

void messageSpear::messageRender(const char* txtName, bool messageBool, int timeNum, int timeNum2)
{
	

	if (messageBool)
	{
		vector<string> vStr;
		_font = CreateFont(35, 25, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "Sam3KRFont");
		_oldFont = (HFONT)SelectObject(getMemDC(), _font);
		vStr = TXTDATA->txtLoad(txtName);
		if (GetTickCount() - _texOldTime >= 1 * 100)
		{
			if (timeNum >= _talkCount)
			{
				_talkCount += 2;
			}
			else if (timeNum2 >= _talkCount2)
			{
				_talkCount2 += 2;
			}
			else
			{
				IMAGEMANAGER->findImage("talkPage")->expandRender(getMemDC(), GAMESIZEX - 100, GAMESIZEY - 100, _pageFrameX, 0, 1.5, 1.5);
			}
			_texOldTime = GetTickCount();
		}
		IMAGEMANAGER->findImage("messageSpear")->expandRender(getMemDC(), 0, GAMESIZEY / 2 + 80, 0, 0, 1.7, 1.7);
		TextOut(getMemDC(), 70, 550, vStr[0].c_str(), _talkCount);
		TextOut(getMemDC(), 70, 600, vStr[1].c_str(), _talkCount2);
		SelectObject(getMemDC(), _oldFont);
		DeleteObject(_font);
	}
}
