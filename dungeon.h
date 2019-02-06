#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"
#include "knightMonster.h"

class dungeon : public gameNode
{
private:
	ballMonster* _ballMonster;
	fireMonster* _fireMonster;
	knightMonster* _knightMonster;

public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();
};

