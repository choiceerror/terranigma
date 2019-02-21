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
	//townManMessage();

	_once = false;

	_talkCount = _talkCount2 = 0;

	_pageFrameX = 0;

	_pageOn = false;

	_birdTalk = _elderTalk = _elleTalk = _maidTalk = false;
	_grandfaTalk = _grandmaTalk = _fishManTalk = _townManTalk = _guardianTalk = false;

	_texOldTime = GetTickCount();

	_playerKey = _guardianPageNext = false;

	_soundOnce = 0;

	_guardianTalkCount[0] = _guardianTalkCount[1] = 0;

	_pageNext = 0;



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
		if (!_grandfaTalk) _grandfaTalk = true;
		else
		{
			_once = true;
			_grandfaTalk = false;
			_pageOn = false;
		}

	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		if (!_grandmaTalk) _grandmaTalk = true;
		else
		{
			_once = true;
			_grandmaTalk = false;
			_pageOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		if (!_elleTalk) _elleTalk = true;
		else
		{
			_once = true;
			_elleTalk = false;
			_pageOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		if (!_birdTalk) _birdTalk = true;

		else
		{
			_once = true;
			_birdTalk = false;
			_pageOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		if (!_fishManTalk) _fishManTalk = true;
		else
		{
			_once = true;
			_fishManTalk = false;
			_pageOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		if (!_elderTalk) _elderTalk = true;
		else
		{
			_once = true;
			_elderTalk = false;
			_pageOn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		if (!_elderTalk) _elderTalk = true;
		else
		{
			_once = true;
			_elderTalk = false;
			_pageOn = false;
		}
	}

	messageRender("messageFile/할아버지.txt", _grandfaTalk, 8, 26, 0);
	messageRender("messageFile/할머니.txt", _grandmaTalk, 33, 34, 0);
	messageRender("messageFile/엘.txt", _elleTalk, 24, 30, 1);
	messageRender("messageFile/꼬꼬.txt", _birdTalk, 14, 6, 0);
	messageRender("messageFile/낚시꾼.txt", _fishManTalk, 23, 15, 0);
	messageRender("messageFile/장로할아범.txt", _elderTalk, 4, 31, 2);
	messageRender("messageFile/메이드.txt", _maidTalk, 10, 10, 0);
	messageRender("messageFile/마을사람.txt", _townManTalk, 22,23, 0);

	if (_once)
	{
		_talkCount = _talkCount2 = 0;
		_once = false;
	}




	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		if (!_playerKey) _playerKey = true;
		else
		{

			_playerKey = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_guardianPageNext = true;
	}

	//char str[128];
	//sprintf_s(str, "%d", _guardianPageNext);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));

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

	message[0] = "안녕하세요";
	message[1] = "반갑습니다.";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/엘.txt", vStr);
}

void messageSpear::fishManMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "오늘은  잡고  말겠어..!";
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

void messageSpear::townManMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "동훈이는 하나를 만들면";
	message[1] = "다른 하나가 터집니다.";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/마을사람.txt", vStr);
}

void messageSpear::guardianMessage()
{
	string message[8];
	vector<string> vStr;


	message[0] = "나는  가디언이다";
	message[1] = "이  타워안에는  층이";
	message[2] = "층이 3개로 나뉘어져 있다";
	message[3] = "시련을  극복하여";
	message[4] = "세계를  조절하는   힘을  얻어라!";
	message[5] = "이것이  너의  운명이다!!";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	vStr.push_back(message[2]);
	vStr.push_back(message[3]);
	vStr.push_back(message[4]);
	vStr.push_back(message[5]);

	TXTDATA->txtSave("messageFile/가디언.txt", vStr);
}



void messageSpear::messageRender(const char* txtName, bool messageBool, int timeNum, int timeNum2, int nameTrue)
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
				if (_soundOnce == 0)
				{
					SOUNDMANAGER->play("textSound", 1);
					if (_soundOnce == 0)
					{
						_soundOnce++;
					}
				}
				_talkCount += 2;
			}
			else if (timeNum2 >= _talkCount2)
			{
				_talkCount2 += 2;
			}
			else
			{
				SOUNDMANAGER->stop("textSound");
				_soundOnce = 0;
				_pageOn = true;
			}
			_texOldTime = GetTickCount();

			if (_pageFrameX < 2)
			{
				_pageFrameX++;
			}
			else _pageFrameX = 0;
		}
		IMAGEMANAGER->findImage("messageSpear")->expandRender(getMemDC(), 0, GAMESIZEY / 2 + 80, 0, 0, 1.7, 1.7);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 70, 570, vStr[0].c_str(), _talkCount);
		TextOut(getMemDC(), 70, 620, vStr[1].c_str(), _talkCount2);
		if (_pageOn)
		{
			IMAGEMANAGER->findImage("talkPage")->expandRender(getMemDC(), GAMESIZEX - 100, GAMESIZEY - 100, _pageFrameX, 0, 1.5, 1.5);
		}

		string name;

		SetTextColor(getMemDC(), RGB(204, 215, 27));
		switch (nameTrue)
		{
		case 0:
			break;
		case 1:

			name = "엘 :";
			TextOut(getMemDC(), 70, 500, name.c_str(), strlen(name.c_str()));
			break;
		case 2:
			name = "장로할아범 :";
			TextOut(getMemDC(), 70, 500, name.c_str(), strlen(name.c_str()));
			break;
		case 3:
			name = "아크 :";
			TextOut(getMemDC(), 70, 500, name.c_str(), strlen(name.c_str()));
			break;
		}
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		SelectObject(getMemDC(), _oldFont);
		DeleteObject(_font);
	}
}
void messageSpear::guardianMessageRender(bool guardian, bool playerKey)
{
	if (guardian == false && _pageNext <= 3)
	{
		vector<string> vStr;
		_font = CreateFont(35, 25, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "Sam3KRFont");
		_oldFont = (HFONT)SelectObject(getMemDC(), _font);
		vStr = TXTDATA->txtLoad("messageFile/가디언.txt");

		_sizeNum[0] = 25;
		_sizeNum[1] = 23;
		_sizeNum[2] = 15;
		_sizeNum[3] = 19;
		_sizeNum[4] = 14;
		_sizeNum[5] = 15;
		_sizeNum[6] = 31;
		_sizeNum[7] = 21;

		if (GetTickCount() - _texOldTime >= 1 * 100)
		{
			if (_sizeNum[_num] >= _guardianTalkCount[0])
			{
				if (_soundOnce == 0)
				{
					SOUNDMANAGER->play("textSound", 1);
					if (_soundOnce == 0)
					{
						_soundOnce++;
					}
				}
				_guardianTalkCount[0] += 2;
			}
			else if (_sizeNum[_num + 1] >= _guardianTalkCount[1])
			{
				_guardianTalkCount[1] += 2;
			}
			else
			{
				_soundOnce = 0;
				SOUNDMANAGER->stop("textSound");
				_pageOn = true;
			}
			_texOldTime = GetTickCount();

			if (_pageFrameX < 2)
			{
				_pageFrameX++;
			}
			else _pageFrameX = 0;
		}

		bool _playerKey = playerKey;
		if (_playerKey && _pageOn)
		{
			if (_pageNext < 4)
			{
				_pageNext++;
			}
			if (_num < 6)
			{
				_num += 2;
			}
			else
			{
				_num = 0;
				_guardianTalkCount[0] = _guardianTalkCount[1] = 0;
				_pageOn = false;
			}
			_pageOn = false;
			_guardianTalkCount[0] = _guardianTalkCount[1] = 0;
		}
		string playerTalk[3];
		if (_pageNext != 0)
		{
			IMAGEMANAGER->findImage("messageSpear")->expandRender(getMemDC(), 0, GAMESIZEY / 2 + 80, 0, 0, 1.7, 1.7);
		}
		else
		{
			IMAGEMANAGER->findImage("messageSpear")->expandRender(getMemDC(), 0, 0, 0, 0, 1.7, 1.7);
		}

		switch (_pageNext)
		{
		case 0:
			playerTalk[0] = "아크 :";
			playerTalk[1] = "우와..  엄청큰  대가리다!";
			playerTalk[2] = "어이  뭐라고  말좀  해봐";
			SetTextColor(getMemDC(), RGB(204, 215, 27));
			TextOut(getMemDC(), 70, 50, playerTalk[0].c_str(), strlen(playerTalk[0].c_str()));
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 70, 120, playerTalk[1].c_str(), _guardianTalkCount[0]);
			TextOut(getMemDC(), 70, 170, playerTalk[2].c_str(), _guardianTalkCount[1]);
			break;
		case 1:
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 70, 570, vStr[0].c_str(), _guardianTalkCount[0]);
			TextOut(getMemDC(), 70, 620, vStr[1].c_str(), _guardianTalkCount[1]);
			break;
		case 2:
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 70, 570, vStr[2].c_str(), _guardianTalkCount[0]);
			TextOut(getMemDC(), 70, 620, vStr[3].c_str(), _guardianTalkCount[1]);
			break;
		case 3:
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 70, 570, vStr[4].c_str(), _guardianTalkCount[0]);
			TextOut(getMemDC(), 70, 620, vStr[5].c_str(), _guardianTalkCount[1]);
			break;
		}


		if (_pageOn)
		{
			if (_pageNext == 0)
			{
				IMAGEMANAGER->findImage("talkPage")->expandRender(getMemDC(), GAMESIZEX - 100, 200, _pageFrameX, 0, 1.5, 1.5); 
			}
			else IMAGEMANAGER->findImage("talkPage")->expandRender(getMemDC(), GAMESIZEX - 100, GAMESIZEY - 100, _pageFrameX, 0, 1.5, 1.5);
		}

		string name;
		name = "가디언대가리 :";
		SetTextColor(getMemDC(), RGB(204, 215, 27));
		if (_pageNext != 0)
		{
			TextOut(getMemDC(), 70, 500, name.c_str(), strlen(name.c_str()));
		}
		SetTextColor(getMemDC(), RGB(255, 255, 255));
	}
}
