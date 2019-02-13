#pragma once
#include "enemy.h"
class fireMonster : public enemy
{
private:
	int _fireCount; //발사카운트
	float _viewX;
	float _viewY;
public:
	fireMonster();
	~fireMonster();

	virtual HRESULT init(string enemyName, const char* imageName, float x, float y, int idX, int idY, int hp);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	void move();
	bool fireBulletCountFire();

public:
	//접근자 설정자 모음

};

