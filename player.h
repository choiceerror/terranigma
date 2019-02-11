#pragma once
#include "gameNode.h"
#include "jump.h"

#define PLAYERFPS 6			//캐릭터 프레임 
#define PLAYERJUMP 14		//점프 프레임
#define PLAYERATTACKFPS 12	//공격 프레임

//클래스 첫번째 명은 대문자로
//메소드는 맨앞에 하는일(뭐하는놈인가) 그 뒤로 어떤일을 하는녀석인가 3. 이유 

class enemyManager;

enum PLAYERSTATE
{
	PLAYER_IDLE,
	PLAYER_IDLE_ACTION,
	PLAYER_WALK,
	PLAYER_RUN,
	PLAYER_TR_PUSH_UP,
	PLAYER_JUMP,
	PLAYER_LEVELUP,
	PLAYER_ATTACK,
	PLAYER_COMBINATION,
	PLAYER_JUMP_ATTACK,
	PLAYER_DASH_JUMP_ATTACK,
	PLAYER_DEATH,
	PLAYER_DASH_ATTACK,
	PLAYER_WORLDMAP,
	PLAYER_FALL,
	PLAYER_OBJ_PICKUP,
	PLAYER_OBJ_WALK,
	PLAYER_OBJ_THROW
};

enum PLAYERDIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct tagPlayer
{
	RECT rc;
	image* image_obj;
	image* image;
	animation* ani;
	PLAYERSTATE state;
	PLAYERDIRECTION direction;
	float x, y;
	float speed;
	float jumpPower;
	float gravity;
	int idX, idY;
	int maxHP;
	int HP;
	int str;
	int def;
	int money;
};

class player : public gameNode
{
private:
	tagPlayer _player;
	image* _image;
	jump* _jump;

	int _doubleKey[4];					// 키를 2번 눌렀을때 달리게 해주기위한 인트형 변수
	int _curTime[4], _oldTime[4];

	int _attackComboKey;				// 키를 2번 눌렀을때 공격 콤보 (원리는 위와 동일)
	int _oldAttackTime;					// 공격쿨타임
	int _oldJumpTime;					// 점프쿨타임

	float _startX;						// 점프 시작 위치
	float _startY;						// 점프 시작 위치

	bool _isRun;
	bool _isAttack;
	bool _isJump;

	enemyManager* _enemyManager;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX , float cameraY);

	//각 상태 프레임 입력 초기값 
	void keyFrameInit();		
	//키 입력 
	void keyInput();							
	//키다운 입력 중복된 코드 함수로 만들어서 사용
	void keyDownInput(PLAYERDIRECTION direction);
	//키업 입력 중복된 코드 함수로 만들어서 사용
	void keyUpInput(PLAYERDIRECTION direction);	
	//플레이어 상태 애니메이션 재생 함수
	void playerState();
	//더블키(공격 , 달리기)
	void DoubleKeyIntVoid();
	//재생에 중복되는 코드 함수화
	void playerAniName(string targetName, string aniName);

	void setEnemyManagerAddressLink(enemyManager* em) { _enemyManager = em; }

	//===================== 콜백 함수 =======================

	//콜백 공격함수
	static void callBackAttack(void* obj);
	//콜백 대쉬공격
	static void callBackDashAttack(void* obj);
	//콜백 점프
	static void callBackJump(void* obj);

	//===================== 접근자 설정자 =======================

	PLAYERSTATE getPlayerState() { return _player.state; }
	PLAYERDIRECTION getPlayerDirection() { return _player.direction; }
	animation* getPlayerAni() { return _player.ani; }

	void setPlayerState(PLAYERSTATE state) { _player.state = state; }
	void setPlayerDirection(PLAYERDIRECTION direction) { _player.direction = direction; }
	void setPlayerAni(animation* animation) { _player.ani = animation; }
	void setPlayerPosX(float playerX) { _player.x = playerX; }
	void setPlayerPosY(float playerY) { _player.x = playerY; }
	void setPlayerSpeed(float speed) { _player.speed = speed; }

	RECT getPlayerRc() { return _player.rc; }

	float getPlayerX() { return _player.x; }
	float getPlayerY() { return _player.y; }
	float getPlayerSpeed() { return _player.speed; }
	float getPlayerJumpPower() { return _player.jumpPower; }
	float getPlayergravity() { return _player.gravity; }

	int getPlayerMoney() { return _player.money; }
	int getPlayerMaxHP() { return _player.maxHP; }
	int getPlayerHP() { return _player.HP; }
	int getPlayerStr() { return _player.str; }
	int getPlayerDef() { return _player.def; }

	bool getPlayerJump() { return _isJump; }


};

