#pragma once
#include "gameNode.h"

struct tagFireBullet
{
	image* image;
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	float viewX, viewY;
	bool isCollision;
	animation* fireBulletAni;
};

class fireMonsterBullet : public gameNode
{
private:
	vector<tagFireBullet> _vFireBullet;
	vector<tagFireBullet>::iterator _viFireBullet;

	const char* _imageName;
	float _range; //거리
	int _fireBulletMax; 

public:
	fireMonsterBullet();
	~fireMonsterBullet();

	HRESULT init(const char* imageName, float range, int fireBulletMax);
	void release();
	void update(float cameraX, float cameraY);
	void render(float viewX, float viewY);

	void fire(float x, float y, float angle, float speed); //발사
	
	void move(float cameraX, float cameraY); //이동

	//접근자 설정자
	vector<tagFireBullet> getVFireBullet() {return _vFireBullet;}
	vector<tagFireBullet>* setVFireBullet() {return &_vFireBullet;}

	
};

