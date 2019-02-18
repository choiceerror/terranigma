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


		HFONT font;
		HFONT oldFont;
		RECT rc;
		rc = RectMake(0, 550, GAMESIZEX - 200, 400);
		font = CreateFont(40, 25, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "Sam3KRFont");
		oldFont = (HFONT)SelectObject(getMemDC(), font);
		vStr = TXTDATA->txtLoad("messageFile/할아버지.txt");
		//TextOut(getMemDC(), 80, 500, vStr[0].c_str(), strlen(vStr[0].c_str()));
		//TextOut(getMemDC(), 80, 550, vStr[1].c_str(), strlen(vStr[1].c_str()));
		//DrawText(getMemDC(), &vStr[0].c_str,strlen(vStr[0].c_str), &rc, DT_CENTER|DT_WORDBREAK);
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
	}

	//HFONT font1, oldFont1;
	//RECT rcText = RectMake(300, 200, 400, 100);
	//
	//font1 = CreateFont(100, 0, 0, 0, 300, 0, 0, 0,
	//	DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
	//	PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Edwardian Script ITC"));
	//oldFont1 = (HFONT)SelectObject(getMemDC(), font1);
	//DrawText(getMemDC(), TEXT("Modern Times"), strlen("Modern Times"), &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//SelectObject(getMemDC(), oldFont1);
	//DeleteObject(font1);
	//SetBkMode(getMemDC(), TRANSPARENT);
}

void messageSpear::grandfaMessage()
{
	string message[2];
	
	vector<string> vStr;

	message[0] = "잭";
	//message[1] = "안녕하세요 \n 사랑해요";
	message[1] = "안녕하세요\nㅋㅋㅋ";
	//message[1][message[1].size()] = 10;
	//message[1].append((char*)10);
	//message[1][message[1].size()] = NULL;

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/할아버지.txt", vStr);
}

void messageSpear::grandmaMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "대사";
	message[1] = "";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/할머니.txt", vStr);
}

void messageSpear::birdMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "대사";
	message[1] = "";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/꼬꼬.txt", vStr);
}

void messageSpear::elderMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "대사";
	message[1] = "";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/장로할아범.txt", vStr);
}

void messageSpear::elleMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "대사";
	message[1] = "";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/엘.txt", vStr);
}

void messageSpear::fishManMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "대사";
	message[1] = "";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/낚시꾼.txt", vStr);
}

void messageSpear::maidMessage()
{
	string message[2];
	vector<string> vStr;

	message[0] = "대사";
	message[1] = "";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	TXTDATA->txtSave("messageFile/메이드.txt", vStr);
}
