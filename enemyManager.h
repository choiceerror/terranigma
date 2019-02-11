#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"
#include "knightMonster.h"
#include "fireMonsterBullet.h"

//던전 층수
enum DUNGEON_FLOOR
{
	FIRST_FLOOR, //1층
	SECOND_FLOOR, //2층
	THIRD_FLOOR, //3층
};

class player;

class enemyManager : public gameNode
{
private:
	//볼몬스터 벡터
	vector<ballMonster*> _vBallMonster;
	vector<ballMonster*>::iterator _viBallMonster;

	//파이어 몬스터 벡터
	vector<fireMonster*> _vFireMonster;
	vector<fireMonster*>::iterator _viFireMonster;

	//나이트 몬스터 벡터
	vector<knightMonster*> _vKnightMonster;
	vector<knightMonster*>::iterator _viKnightMonster;

	//파이어몬스터 총알
	fireMonsterBullet* _fireMonsterBullet;

	player* _player;

	DUNGEON_FLOOR _dungeonFloor; //던전 층수
	int _fireBulletSpeed;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void updateCollection(); //업데이트 모음 함수
	void enemyDraw(); //에너미들 랜더링 모음함수
	void setEnemy(); //에너미 셋팅
	void enemyAttackPlayerCollision(); //에너미들의 공격이 플레이어랑 충돌할 함수
	void fireMonsterBulletFire(int i); //파이어몬스터 총알 발사할 함수
	void enemyDead(); //에너미들이 죽을 함수
	void enemyRespon(); //에너미들이 죽은다음 리스폰할 함수

public:
	//접근자 설정자 모음
	vector<ballMonster*> getVBallMonster() {return _vBallMonster;}
	vector<ballMonster*>* setVBallMonster() {return &_vBallMonster;}

	vector<fireMonster*> getVFireMonster() {return _vFireMonster;}
	vector<fireMonster*>* setVFireMonster() {return &_vFireMonster;}

	vector<knightMonster*> getVKnightMonster() {return _vKnightMonster;}
	vector<knightMonster*>* setVKnightMonster() {return &_vKnightMonster;}

	void setPlayerMemoryAddressLink(player* player) {_player = player;}

};

