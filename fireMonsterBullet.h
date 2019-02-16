#pragma once
#include "gameNode.h"

struct tagFireBullet
{
	image* image;
	RECT rc;
	RECT tileCollisionRc;
	float x, y;
	int idX, idY;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	float viewX, viewY;
	bool isCollision;
	animation* fireBulletAni;
	POINT tileIndex[8]; //타일인덱스 판별
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
	void update();
	void render(float cameraX, float cameraY);

	void fire(float x, float y, float angle, float speed); //파이어몬스터 총알발사
	void bossBulletFire(float x, float y, float angle, float speed);
	
	void move(); //이동

public:
	//접근자 설정자
	vector<tagFireBullet> getVFireBullet() {return _vFireBullet;}
	vector<tagFireBullet>* setVFireBullet() {return &_vFireBullet;}

	
};

