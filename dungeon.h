#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"

class dungeon : public gameNode
{
private:
	ballMonster* _ballMonster;
	fireMonster* _fireMonster;

public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();
};

