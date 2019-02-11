#pragma once
#include "gameNode.h"

class PlayerWorldMap : gameNode
{
private:
	float _x, _y;
	float _speed;
public:
	PlayerWorldMap();
	~PlayerWorldMap();
};

