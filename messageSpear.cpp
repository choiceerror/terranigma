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
	grandfaMessage();
	grandmaMessage();
	birdMessage();
	elderMessage();
	elleMessage();
	fishManMessage();
	maidMessage();
	guardianMessage();
	

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
	vector<string> vStr;

	if (KEYMANAGER->isStayKeyDown('V'))
	{
		IMAGEMANAGER->findImage("messageSpear")->expandRender(getMemDC(), 0, GAMESIZEY / 2 + 80, 0, 0, 1.7, 1.7);
		_font = CreateFont(40, 25, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "Sam3KRFont");
		_oldFont = (HFONT)SelectObject(getMemDC(), _font);
		vStr = TXTDATA->txtLoad("messageFile/할아버지.txt");
		TextOut(getMemDC(), 80, 500, vStr[0].c_str(), strlen(vStr[0].c_str()));
		TextOut(getMemDC(), 80, 550, vStr[1].c_str(), strlen(vStr[1].c_str()));
	}
	SelectObject(getMemDC(), _oldFont);
	DeleteObject(_font);
}

void messageSpear::grandfaMessage()
{
	string message[2];
	
	vector<string> vStr;

	message[0] = "뭐냐  ark";
	message[1] = "다신  여기  오지  말라니깐!";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/할아버지.txt", vStr);
}

void messageSpear::grandmaMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "ark야  탑에는  절대  가지  말거라";
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

	message[0] = "장로 :";
	message[1] = "넌  왜  그렇게  항상  말썽이냐?";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/장로할아범.txt", vStr);
}

void messageSpear::elleMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "엘";
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

	message[0] = "타워문 대가리";
	message[1] = "나는  가디언이다";
	message[2] = "용건이  무엇이냐?";
	message[3] = "이  타워안에는  층이";
	message[4] = "세개로 되어있다.";
	message[5] = "시련을  극복하여";
	message[6] = "세계를  조절하는   힘을  얻어라!";
	message[7] = "이것이  너의  운명이다!";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	vStr.push_back(message[2]);
	vStr.push_back(message[3]);
	vStr.push_back(message[4]);
	vStr.push_back(message[5]);
	vStr.push_back(message[6]);
	vStr.push_back(message[7]);
	TXTDATA->txtSave("messageFile/가디언.txt", vStr);
}
