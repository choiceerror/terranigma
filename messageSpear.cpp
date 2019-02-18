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
	sprintf_s(_grandfa, "할아버지");
	sprintf_s(_grandfaTitle, "타이틀");
	sprintf_s(_grandfaMessage, "메세지");

	INIDATA->addData(_grandfa, _grandfaTitle, _grandfaMessage);
	//INIDATA->iniSave("")

	sprintf_s(_grandma, "할머니");
	sprintf_s(_grandmaTitle, "타이틀");
	sprintf_s(_grandmaMessage, "메세지");

	sprintf_s(_bird, "꼬꼬");
	sprintf_s(_birdTitle, "타이틀");
	sprintf_s(_birdMessage, "메세지");

	sprintf_s(_elder, "장로할아범");
	sprintf_s(_elderTitle, "타이틀");
	sprintf_s(_elderMessage, "메세지");

	sprintf_s(_elle, "엘");
	sprintf_s(_elleTitle, "타이틀");
	sprintf_s(_elleMessage, "메세지");

	sprintf_s(_maid, "메이드");
	sprintf_s(_maidTitle, "타이틀");
	sprintf_s(_maidMessage, "메세지");

	sprintf_s(_fishMan, "낚시꾼");
	sprintf_s(_fishManTitle, "타이틀");
	sprintf_s(_fishManMessage, "메세지");

	sprintf_s(_townMan, "마을사람");
	sprintf_s(_townManTitle, "타이틀");
	sprintf_s(_townManMessage, "메세지");
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
}

void messageSpear::grandfaMessage()
{
	
}

void messageSpear::grandmaMessage()
{
}

void messageSpear::birdMessage()
{
}

void messageSpear::elderMessage()
{
}

void messageSpear::elleMessage()
{
}

void messageSpear::fishManMessage()
{
}

void messageSpear::maidMessage()
{
}
