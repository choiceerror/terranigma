#pragma once
#include "gameNode.h"
#include "ballMonster.h"
#include "fireMonster.h"
#include "knightMonster.h"
#include "fireMonsterBullet.h"
#include "dungeonMap.h"
#include "boss.h"
#include "camera.h"

enum ENEMYINFO
{
	BALLMONSTER_HP = 50,
	FIREMONSTER_HP = 30,
	KNIGHTMONSTER_HP = 100,
	BOSS_HP = 10,
};

enum ONCE //한번만 받기위함.
{
	LINEAR_APPEAR,
	CAMERA_LINEAR,
	BOSS_APPEAR,
	WORLDTIME,
};

enum class BULLET_PATTERN
{
	GOLD_BULLET,
	BLUE_BULLET,
	RED_BULLET,
	RGB_BULLET,
};

enum ATTACK_PATTERN
{
	ATTACK_ONE,
	ATTACK_TWO,
	ATTACK_THREE,
	ATTACK_SHOCK, //쇼크공격
	ATTACK_NONE,
};

struct tagShockAttack
{
	RECT rc;
	RECT rc2;
	float x, y;
	image* image;
	animation* ani;
	bool isAttack;
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

	//보스 벡터
	vector<boss*> _vBoss;
	vector<boss*>::iterator _viBoss;

	//파이어몬스터 총알
	fireMonsterBullet* _fireMonsterBullet;

	vector<POINTFLOAT> _vEnemyDeadPoint;
	camera* _camera;

	//=================보스 관련==================
	bossBullet* _goldBullet; //골드총알
	bossBullet* _blueBullet; //블루총알
	bossBullet* _redBullet; //레드총알
	bossBullet* _rgbBullet; //세개다 합친총알
	BULLET_PATTERN _bulletPattern; //총알 나가는 종류
	ATTACK_PATTERN _attackPattern; //공격종류
	tagShockAttack* _shockAttack;

	float _worldTime;
	bool _isBossAppear; //보스 등장시점 판별해줄 불값
	bool _isOnce[5]; //업데이트부분에 한번만 받기위함.

	POINTFLOAT _appearGoal;
	float _goalAngle;
	float _elapsedTime;
	float _goalDistance;
	float _appearSpeed; //등장 스피드

	POINTFLOAT _moveGoal[4];

	float _goalX;
	float _goalY;
	float _moveWorldTime;
	float _rndMoveWorldTime;
	float _attackWorldTime[5];

	int _rndAttack[4]; //3개중에 한개나갈타입
	int _rndAttackType[3]; //1개 어택중에 다르게 나갈타입.

	float _moveSpeed;
	float _bulletSpeed[3];
	//=================보스 관련==================

	player* _player;

	dungeonMap* _dungeonMap; //던전맵

	int _fireBulletSpeed;

	RECT _playerAttackRc; //임의의 공격렉트

	int _rndMove[4];


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
	void bossAppear(); //보스 등장
	void bossMovePattern(); //보스 무브패턴
	void bossAttackPattern(); //보스 공격패턴
	void bossBulletDraw(float cameraX, float cameraY);
	void enemyRespon(); //에너미들이 죽은다음 리스폰할 함수


public:
	//접근자 설정자 모음
	vector<ballMonster*> getVBallMonster() { return _vBallMonster; }
	vector<ballMonster*>* setVBallMonster() { return &_vBallMonster; }

	vector<fireMonster*> getVFireMonster() { return _vFireMonster; }
	vector<fireMonster*>* setVFireMonster() { return &_vFireMonster; }

	vector<knightMonster*> getVKnightMonster() { return _vKnightMonster; }
	vector<knightMonster*>* setVKnightMonster() { return &_vKnightMonster; }

	vector<boss*> getVBoss() { return _vBoss; }
	vector<boss*>* setVBOss() { return &_vBoss; }

	vector<POINTFLOAT> getVEnemyDeadPoint() { return _vEnemyDeadPoint; }
	vector<POINTFLOAT>* setVEnemyDeadPoint() { return &_vEnemyDeadPoint; }

	fireMonsterBullet* getFireMonsterBullet() { return _fireMonsterBullet; }
	bossBullet* getGoldBullet() { return _goldBullet; }
	bossBullet* getBlueBullet() { return _blueBullet; }
	bossBullet* getRedBullet() { return _redBullet; }
	bossBullet* getRgbBullet() { return _rgbBullet; }
	tagShockAttack* getShockAttack() { return _shockAttack; }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setDungeonMapAddressLink(dungeonMap* map) { _dungeonMap = map; }
	void setCameraAddressLink(camera* camera) { _camera = camera; }
};

