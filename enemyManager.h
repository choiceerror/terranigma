#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"
#include "knightMonster.h"
#include "fireMonsterBullet.h"
#include "dungeonMap.h"


enum ENEMYINFO
{
	BALLMONSTER_HP = 100,
	FIREMONSTER_HP = 100,
	KNIGHTMONSTER_HP = 500,
	BOSS_HP = 3000,
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

	vector<POINTFLOAT> _vEnemyDeadPoint;

	player* _player;

	dungeonMap* _dungeonMap; //던전맵


	int _fireBulletSpeed;

	RECT _playerAttackRc; //임의의 공격렉트

	int _rndMove[3];

	RECT _objectRc; //몬스터들 못가게 막기위한 임시렉트

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);

	void updateCollection(); //업데이트 모음 함수
	void drawAll(float cameraX, float cameraY); //랜더링 모음함수
	void setEnemy(); //에너미 셋팅
	void enemyAI(); //에너미들의 AI
	void playerAttackEnemyCollision(); //플레이어 공격에 에너미들이 맞을함수
	void fireMonsterBulletFireCollision(int num); //파이어몬스터 총알 발사하고 충돌할 함수
	void enemyDead(); //에너미들이 죽을 함수
	void tileCheckObjectCollision(); //타일검출 충돌 함수
	void enemyRespon(); //에너미들이 죽은다음 리스폰할 함수


public:
	//접근자 설정자 모음
	vector<ballMonster*> getVBallMonster() { return _vBallMonster; }
	vector<ballMonster*>* setVBallMonster() { return &_vBallMonster; }

	vector<fireMonster*> getVFireMonster() { return _vFireMonster; }
	vector<fireMonster*>* setVFireMonster() { return &_vFireMonster; }

	vector<knightMonster*> getVKnightMonster() { return _vKnightMonster; }
	vector<knightMonster*>* setVKnightMonster() { return &_vKnightMonster; }

	vector<POINTFLOAT> getVEnemyDeadPoint() { return _vEnemyDeadPoint; }
	vector<POINTFLOAT>* setVEnemyDeadPoint() { return &_vEnemyDeadPoint; }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setDungeonMapAddressLink(dungeonMap* map) { _dungeonMap = map; }

};

