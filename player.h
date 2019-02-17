#pragma once
#include "gameNode.h"
#include "jump.h"
#include "DashAttack.h"
#include "Inventory.h"

#define PLAYERFPS 6			//캐릭터 프레임 
#define PLAYERJUMP 14		//점프 프레임
#define PLAYERATTACKFPS 12	//공격 프레임

//클래스 첫번째 명은 대문자로
//메소드는 맨앞에 하는일(뭐하는놈인가) 그 뒤로 어떤일을 하는녀석인가 3. 이유 

class enemyManager;
class dungeonMap;
class townMap;
enum PLAYERSTATE
{
	PLAYER_IDLE = 0,			//캐릭터 아이들 상태
	PLAYER_IDLE_ACTION,		//캐릭터 아이들 액션
	PLAYER_WALK,			//캐릭터 걷는 상태
	PLAYER_RUN,				//뛸 때
	PLAYER_TR_PUSH_UP,		//벽 밀때
	PLAYER_JUMP,			//점프
	PLAYER_LEVELUP,			//레벨업
	PLAYER_ATTACK,			//공격
	PLAYER_COMBINATION,		//연속공격
	PLAYER_JUMP_ATTACK,		//점프공격
	PLAYER_DASH_JUMP_ATTACK,//대쉬점프공격
	PLAYER_DEATH,			//주금
	PLAYER_DASH_ATTACK,		//대쉬공격
	PLAYER_WORLDMAP,		//월드맵상태
	PLAYER_FALL,			//떨어질때
	PLAYER_OBJ_PICKUP,		//오브젝트 들때
	PLAYER_OBJ_WALK,		//오브젝트들고 걸을때
	PLAYER_OBJ_THROW,		//오브젝트 던질때
	PLAYER_ENEMY_ATTACK
};

enum PLAYERDIRECTION
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

struct tagPlayer
{
	RECT rc;						//캐릭터 렉트
	RECT attackRc;
	image* image_obj;				//캐릭터 오브젝트 들때 이미지
	image* image;					//캐릭터 이미지
	animation* ani;					//캐릭터 애니메이션
	PLAYERSTATE state;				//캐릭터 상태
	PLAYERDIRECTION direction;		//캐릭터 상하좌우 상태
	float x, y;						//캐릭터 좌표
	float speed;					//스피드
	float jumpPower;				//점프 파워
	float gravity;					//중력값
	int idX, idY;					//타일 인덱스값
	int maxHP;						//최대체력
	int HP;							//현재체력
	int str;						//공격력
	int def;						//방어력
	int money;						//돈
	int alphaRender;				//투명도
};

class player : public gameNode
{
private:
	tagPlayer _player;
	image* _image;
	jump* _jump;
	DashAttack* _dashAttack;

	Inventory* _inventory;

	int _doubleKey[4];					// 키를 2번 눌렀을때 달리게 해주기위한 인트형 변수
	int _curTime[4], _oldTime[4];

	int _attackComboKey;				// 키를 2번 눌렀을때 공격 콤보 (원리는 위와 동일)
	int _oldAttackTime;					// 공격쿨타임
	int _oldJumpTime;					// 점프쿨타임

	float _startX;						// 점프 시작 위치
	float _startY;						// 점프 시작 위치

	bool _attackMoveStop;				// 공격 중엔 움직이지마
	int _attackMoveStopTime;			// 몇 초 동안

	int _playerProtectTime;
	int _alphaChangeTime;
	bool _playerProtect;				//몬스터에게 공격당했을 때
	bool _alphaChange;					//플레이어 알파블랜드 적용중


	bool _isRun;						// 뛰는중
	bool _isAttack;						// 공격중
	bool _isJump;						// 점프중
	bool _isWalk;						// 걷는중
	bool _unMove;						// 플레이어 움직이지 못하게


	int TileX, TileY;

	int rightX, rightY;
	POINT tileIndex[2];

	enemyManager* _enemyManager;
	dungeonMap* _dungeon;
	townMap* _town;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update(bool enemyCheck, int a);
	void render(float cameraX, float cameraY);

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

	void enemyCollision(bool enemyCheck);

	void playerUI();

	void setEnemyManagerAddressLink(enemyManager* em) { _enemyManager = em; }
	void setMapManagerAddressLink(dungeonMap* dun) { _dungeon = dun; }
	void setTownManagerAddressLink(townMap* to) { _town = to; }
	//===================== 콜백 함수 =======================

	//콜백 공격함수
	static void callBackAttack(void* obj);
	//콜백 대쉬공격
	static void callBackDashAttack(void* obj);
	//콜백 점프
	static void callBackJump(void* obj);

	//===================== 타일 검출 =======================
	void tileCheck();
	void townCheck();
	//===================== 접근자 설정자 =======================

	PLAYERSTATE getPlayerState() { return _player.state; }
	PLAYERDIRECTION getPlayerDirection() { return _player.direction; }
	animation* getPlayerAni() { return _player.ani; }
	Inventory* getInventory() {return _inventory;}

	void setPlayerState(PLAYERSTATE state) { _player.state = state; }
	void setPlayerDirection(PLAYERDIRECTION direction) { _player.direction = direction; }
	void setPlayerAni(animation* animation) { _player.ani = animation; }
	void setPlayerPosX(float playerX) { _player.x = playerX; }
	void setPlayerPosY(float playerY) { _player.y = playerY; }
	void setPlayerSpeed(float speed) { _player.speed = speed; }
	void setPlayerUnMove(bool unMove) { _unMove = unMove; }

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
	bool getPlayerRun() { return _isRun; }
};

