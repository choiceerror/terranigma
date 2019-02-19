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
	animation* ani;
	POINT tileIndex[8]; //타일인덱스 판별
	float sizeX, sizeY;
	int max;
	float worldTime;
	float bulletWorlTime;
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

	void move(); //이동

public:
	//접근자 설정자
	vector<tagFireBullet> getVFireBullet() { return _vFireBullet; }
	vector<tagFireBullet>* setVFireBullet() { return &_vFireBullet; }

};

class bossBullet : public gameNode
{
private:

	vector<tagFireBullet> _vBossBullet;
	vector<tagFireBullet>::iterator _viBossBullet;

	const char* _imageName;
	int _range;
	int _bulletMax;
	animation* _tempAni;


public:
	HRESULT init(const char* imageName, float range, int bulletMax);
	void release();
	void update();
	void render(float cameraX, float cameraY);

	void bossFire(float x, float y, float angle, float speed, int bulletMax); //보스몬스터 총알발사

	void move(); //이동

public:
	//접근자 설정자
	int getBulletMax() {return _bulletMax;}
	void setBulletMax(int max) {_bulletMax = max;}

	vector<tagFireBullet> getVBossBullet() { return _vBossBullet; }
	vector<tagFireBullet>* setVBossBullet() { return &_vBossBullet; }
};

