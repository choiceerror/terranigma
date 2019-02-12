#pragma once
#include "enemy.h"
class boss : public enemy
{
public:
	boss();
	~boss();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY, int hp);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

public:
	//접근자 설정자 모음
};

