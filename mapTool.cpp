#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	_MapT = new tileMap;
	_MapT->init();
	return S_OK;
}

void mapTool::release()
{
	_MapT->release();
	SAFE_DELETE(_MapT);
}

void mapTool::update()
{
	_MapT->update();
}

void mapTool::render()
{
	_MapT->render();
}
