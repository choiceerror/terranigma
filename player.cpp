#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("player", "image/player_test.bmp", 0, 0, 1008, 2821, 12, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_obj", "image/player_obj.bmp", 0, 0, 1540, 800, 10, 10, true, RGB(255, 0, 255));

	_player.image = IMAGEMANAGER->findImage("player");
	_player.image_obj = IMAGEMANAGER->findImage("player_obj");

	keyFrameInit();

	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.speed = 3;
	_player.rc = RectMakeCenter(_player.x + 42, _player.y + 50, 24, 24);
	_player.state = PLAYER_IDLE;
	_player.direction = DOWN;

	for (int i = 0; i < 4; i++)
	{
		_curTime[i] = GetTickCount();
		_oldTime[i] = _curTime[i];
		_doubleKey[i] = 0;
		
	}

	_attackComboKey = 0;
	
	_run = _jump = false;

	return S_OK;
}

void player::release()
{

}

void player::update()
{
	if (_player.state == PLAYER_RUN)
	{
		_run = true;
	}
	else _run = false;
	keyInput();
	playerState();
}

void player::render()
{
	//_player.image->aniRender(getMemDC(),_player.x, _player.y, _player.ani);
	_player.image->expandAniRenderCenter(getMemDC(), _player.x, _player.y, _player.ani, 2, 2);
	//Rectangle(getMemDC(), _player.rc);
	char str[128];
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(str, "%d", _doubleKey[i]);
		//SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), 100 + i * 30, 100, str, strlen(str));
	}

	sprintf_s(str, "%d", _player.direction);
	//SetTextColor(getMemDC(), RGB(0, 0, 0));
	TextOut(getMemDC(), 100, 120, str, strlen(str));
}
// 캐릭터 프레임 초기값
void player::keyFrameInit()
{
	int idleLeft[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleLeft", "player", idleLeft, 1, PLAYERFPS, true);
	int idleRight[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleRight", "player", idleRight, 1, PLAYERFPS, true);
	int idleUp[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleUp", "player", idleUp, 1, PLAYERFPS, true);
	int idleDown[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleDown", "player", idleDown, 1, PLAYERFPS, true);
	int idleAction[] = { 4, 5, 6, 7, 6, 7, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleAction", "player", idleAction, 8, PLAYERFPS, true);
	int moveLeft[] = { 24, 25, 26,  };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveLeft", "player", moveLeft, 3, PLAYERFPS, true);
	int moveRight[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveRight", "player", moveRight, 6, PLAYERFPS, true);
	int moveUp[] = { 36, 37, 38, 40, 41, 40, 37};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveUp", "player", moveUp, 7, PLAYERFPS, true);
	int moveDown[] = { 48, 49, 50, 51, 52, 53 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveDown", "player", moveDown, 6, PLAYERFPS, true);
	int runLeft[] = { 65, 66, 67, 68, 69 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runLeft", "player", runLeft, 5, PLAYERFPS, true);
	int runRight[] = { 60, 61, 62, 63, 64 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runRight", "player", runRight, 5, PLAYERFPS, true);
	int runUp[] = { 72, 73, 74, 75, 76 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runUp", "player", runUp, 5, PLAYERFPS, true);
	int runDown[] = { 77, 78, 79, 80, 81 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runDown", "player", runDown, 5, PLAYERFPS, true);
	int push[] = { 84, 85 , 86, 87 , 88 , 89 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "push", "player", push, 6, PLAYERFPS, true);
	int jumpLeft[] = { 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpLeft", "player", jumpLeft, 11, PLAYERJUMP, false, jump, this);
	int jumpRight[] = { 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpRight", "player", jumpRight, 11, PLAYERJUMP, false, jump, this);
	int jumpUp[] = { 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpUp", "player", jumpUp, 11, PLAYERJUMP, false, jump , this);
	int jumpDown[] = { 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpDown", "player", jumpDown, 11, PLAYERJUMP, false, jump, this);
	int levelUp[] = { 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "levelUp", "player", levelUp, 11, PLAYERFPS, true);
	int attackLeft[] = { 160, 161, 162, 163 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackLeft", "player", attackLeft, 4, PLAYERATTACKFPS, false, attack, this);
	int attackRight[] = { 156, 157, 158, 159 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackRight", "player", attackRight, 4, PLAYERATTACKFPS, false, attack, this);
	int attackUp[] = { 168, 169, 170, 171 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackUp", "player", attackUp, 4, PLAYERATTACKFPS, false, attack, this);
	int attackDown[] = { 172, 173, 174 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackDown", "player", attackDown, 3, PLAYERATTACKFPS, false, attack, this);
	int combinationLeft[] = { 192, 193, 194, 195, 196, 197, 198, 199 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationLeft", "player", combinationLeft, 8, PLAYERATTACKFPS, false, attack, this);
	int combinationRight[] = { 180, 181, 182, 183, 184, 185, 186, 187 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationRight", "player", combinationRight, 8, PLAYERATTACKFPS, false, attack, this);
	int combinationUp[] = { 204, 205, 206, 207, 208, 209 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationUp", "player", combinationUp, 6, PLAYERATTACKFPS, false, attack, this);
	int combinationDown[] = { 216, 217, 218, 219, 220, 221, 222 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationDown", "player", combinationDown, 7, PLAYERATTACKFPS, false, attack, this);
	int jumpAttackLeft[] = { 240, 241, 242, 243, 244, 245,246, 247 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackLeft", "player", jumpAttackLeft, 8, PLAYERFPS, false);
	int jumpAttackRight[] = { 228, 229, 230, 231, 232, 233, 234, 235 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackRight", "player", jumpAttackRight, 8, PLAYERFPS, false);
	int jumpAttackUp[] = { 252, 253, 254, 255, 256, 257, 258, 259 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackUp", "player", jumpAttackUp, 8, PLAYERFPS, false);
	int jumpAttackDown[] = { 264, 265, 266, 267, 268, 269, 270, 271 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackDown", "player", jumpAttackDown, 8, PLAYERFPS, false);
	int dashJumpAttackLeft[] = { 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackLeft", "player", dashJumpAttackLeft, 12, PLAYERFPS, false);
	int dashJumpAttackRight[] = { 276,277,278,279,280,281,282,283,284,285,286,287 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackRight", "player", dashJumpAttackRight, 12, PLAYERFPS, false);
	int dashJumpAttackUp[] = { 300, 301, 302, 303, 304, 305, 306, 307 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackUp", "player", dashJumpAttackUp, 8, PLAYERFPS, false);
	int dashJumpAttackDown[] = { 312, 313, 314, 315, 316, 317, 318, 319 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackDown", "player", dashJumpAttackDown, 8, PLAYERFPS, false);
	int death[] = { 324,325,326,327,328,329 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "death", "player", death, 6, PLAYERFPS, false);
	int fall[] = { 330, 331, 332 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "fall", "player", fall, 3, PLAYERFPS, false);
	int dashAttackLeft[] = { 340, 341, 342, 343 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackLeft", "player", dashAttackLeft, 4, PLAYERFPS, false);
	int dashAttackRight[] = { 336, 337, 338, 339 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackRight", "player", dashAttackRight, 4, PLAYERFPS, false);
	int dashAttackUp[] = { 348, 349, 350, 351 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackUp", "player", dashAttackUp, 4, PLAYERFPS, false);
	int dashAttackDown[] = { 352, 353, 354, 355 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackDown", "player", dashAttackDown, 4, PLAYERFPS, false);
	int worldMapLeft[] = { 363, 364, 365 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapLeft", "player", worldMapLeft, 3, PLAYERFPS, true);
	int worldMapRight[] = { 360, 361, 362 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapRight", "player", worldMapRight, 3, PLAYERFPS, true);
	int worldMapUp[] = { 366, 367, 368 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapUp", "player", worldMapUp, 3, PLAYERFPS, true);
	int worldMapDown[] = { 369, 370, 371 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "worldMapDown", "player", worldMapDown, 3, PLAYERFPS, true);
	int pickupLeft[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "pickupLeft", "player_obj", pickupLeft, 4, PLAYERFPS, false);
	int pickupRight[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "pickupRight", "player_obj", pickupRight, 4, PLAYERFPS, false);
	int pickupUp[] = { 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "pickupUp", "player_obj", pickupUp, 4, PLAYERFPS, false);
	int pickupDown[] = { 10, 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "pickupDown", "player_obj", pickupDown, 4, PLAYERFPS, false);
	int objMoveLeft[] = { 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objMoveLeft", "player_obj", objMoveLeft, 6, PLAYERFPS, true);
	int objMoveRight[] = { 20, 21, 22, 23, 24, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objMoveRight", "player_obj", objMoveRight, 6, PLAYERFPS, true);
	int objMoveUp[] = { 40, 41, 42, 43, 44, 45 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objMoveUp", "player_obj", objMoveUp, 6, PLAYERFPS, true);
	int objMoveDown[] = { 50, 51, 52, 53, 54, 55 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objMoveDown", "player_obj", objMoveDown, 6, PLAYERFPS, true);
	int objThrowLeft[] = { 71, 72, 73, 74, 75, 76, 77, 78 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objThrowLeft", "player_obj", objThrowLeft, 8, PLAYERFPS, false);
	int objThrowRight[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objThrowRight", "player_obj", objThrowRight, 9, PLAYERFPS, false);
	int objThrowUp[] = { 80, 81, 82, 83 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objThrowUp", "player_obj", objThrowUp, 8, PLAYERFPS, false);
	int objThrowDown[] = { 71, 72, 73, 74, 75, 76, 77, 78 };
	KEYANIMANAGER->addArrayFrameAnimation("ark_obj", "objThrowDown", "player_obj", objThrowDown, 8, PLAYERFPS, false);
}
// 키 입력
void player::keyInput()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.direction = LEFT;
		if (!_run ) _player.state = PLAYER_WALK;
		if (_doubleKey[LEFT] == 1)
		{
			_player.state = PLAYER_RUN;
			_player.speed = 5;
		}
		_player.x -= _player.speed;
	
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if ((!(_player.state == PLAYER_RUN) || _player.direction == LEFT))
		{
			_player.state = PLAYER_IDLE;
			_player.speed = 3;
		}
		
		if(_doubleKey[LEFT] == 0) _doubleKey[LEFT]++;
		_curTime[LEFT] = GetTickCount();
		_oldTime[LEFT] = _curTime[LEFT];
		
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.direction = RIGHT;
		if (!_run )  _player.state = PLAYER_WALK;
		if (_doubleKey[RIGHT] == 1)
		{
			_player.state = PLAYER_RUN;
			_player.speed = 5;
		}
		_player.x += _player.speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if ((!(_player.state == PLAYER_RUN) || _player.direction == RIGHT))
		{
			_player.state = PLAYER_IDLE;
			_player.speed = 3;
		}
		
		
		if (_doubleKey[RIGHT] == 0) _doubleKey[RIGHT]++;
		_curTime[RIGHT] = GetTickCount();
		_oldTime[RIGHT] = _curTime[RIGHT];
		
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player.direction = UP;
		if (!_run) _player.state = PLAYER_WALK;
		if (_doubleKey[UP] == 1)
		{
			_player.state = PLAYER_RUN;
			_player.speed = 5;
		}
		_player.y -= _player.speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))     
	{
		if ((!(_player.state == PLAYER_RUN) || _player.direction == UP))
		{
			_player.state = PLAYER_IDLE;
			_player.speed = 3;
		}
		
		if (_doubleKey[UP] == 0) _doubleKey[UP]++;
		_curTime[UP] = GetTickCount();
		_oldTime[UP] = _curTime[UP];
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player.direction = DOWN;
		if (!_run) _player.state = PLAYER_WALK;
		if (_doubleKey[DOWN] == 1)
		{
			_player.state = PLAYER_RUN;
			_player.speed = 5;
		}
		_player.y += _player.speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if ((!(_player.state == PLAYER_RUN) || _player.direction == DOWN))
		{
			_player.state = PLAYER_IDLE;
			_player.speed = 3;
		}
		
		if (_doubleKey[DOWN] == 0) _doubleKey[DOWN]++;
		_curTime[DOWN] = GetTickCount();
		_oldTime[DOWN] = _curTime[DOWN];
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_player.state = PLAYER_ATTACK;
		if (_attackComboKey == 1)
		{
			_player.state = PLAYER_COMBINATION;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('C'))
	{
		if(_attackComboKey == 0) _attackComboKey++;
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_player.state = PLAYER_JUMP;
	}

	DoubleKeyIntVoid();
}
// 캐릭터 상태
void player::playerState()
{
	switch (_player.state)
	{
	case PLAYER_IDLE_ACTION:
		playerAniName("ark", "idleAction");
		break;
	case PLAYER_IDLE:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "idleLeft");
			break;
		case RIGHT:
			playerAniName("ark", "idleRight");
			break;
		case UP:
			playerAniName("ark", "idleUp");
			break;
		case DOWN:
			playerAniName("ark", "idleDown");
			break;
		}
		break;
	case PLAYER_WALK:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "moveLeft");
			break;
		case RIGHT:
			playerAniName("ark", "moveRight");
			break;
		case UP:
			playerAniName("ark", "moveUp");
			break;
		case DOWN:
			playerAniName("ark", "moveDown");
			break;
		}
		break;
	case PLAYER_RUN:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "runLeft");
			break;
		case RIGHT:
			playerAniName("ark", "runRight");
			break;
		case UP:
			playerAniName("ark", "runUp");
			break;
		case DOWN:
			playerAniName("ark", "runDown");
			break;
		}
		break;
	case PLAYER_JUMP:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "jumpLeft");
			break;
		case RIGHT:
			playerAniName("ark", "jumpRight");
			break;
		case UP:
			playerAniName("ark", "jumpUp");
			break;
		case DOWN:
			playerAniName("ark", "jumpDown");
			break;
		}
		break;
	case PLAYER_ATTACK:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "attackLeft");
			break;
		case RIGHT:
			playerAniName("ark", "attackRight");
			break;
		case UP:
			playerAniName("ark", "attackUp");
			break;
		case DOWN:
			playerAniName("ark", "attackDown");
			break;
		}
		break;
	case PLAYER_COMBINATION:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "combinationLeft");
			break;
		case RIGHT:
			playerAniName("ark", "combinationRight");
			break;
		case UP:
			playerAniName("ark", "combinationUp");
			break;
		case DOWN:
			playerAniName("ark", "combinationDown");
			break;
		}
		break;
	case PLAYER_JUMP_ATTACK:
		switch (_player.direction)
		{
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
		break;
	case PLAYER_DASH_JUMP_ATTACK:
		switch (_player.direction)
		{
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
		break;
	case PLAYER_DASH_ATTACK:
		switch (_player.direction)
		{
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
		break;
	case PLAYER_WORLDMAP:
		switch (_player.direction)
		{
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
		break;
	case PLAYER_OBJ_PICKUP:
		switch (_player.direction)
		{
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
		break;
	case PLAYER_OBJ_WALK:
		switch (_player.direction)
		{
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
		break;
	case PLAYER_OBJ_THROW:
		switch (_player.direction)
		{
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
		break;
	}
}
// 키 연속으로 눌렀을때 예외처리 모음
void player::DoubleKeyIntVoid()
{
	//예외처리 key - LEFT->UP->LEFT 뛰는거 방지
	if (_doubleKey[LEFT] == 1 && (_player.state == PLAYER_WALK && !(_player.direction == LEFT)))			
	{
		_doubleKey[LEFT]--;
	}
	else if (_doubleKey[RIGHT] == 1 && (_player.state == PLAYER_WALK && !(_player.direction == RIGHT)))
	{
		_doubleKey[RIGHT]--;
	}
	else if (_doubleKey[UP] == 1 && (_player.state == PLAYER_WALK && !(_player.direction == UP)))
	{
		_doubleKey[UP]--;
	}
	else if (_doubleKey[DOWN] == 1 && (_player.state == PLAYER_WALK && !(_player.direction == DOWN)))
	{
		_doubleKey[DOWN]--;
	}

	for(int i = 0; i < 4; i++) _curTime[i] = GetTickCount();

	//doubleKey를 0.2초가 지나면 0으로 초기화하게 
	if ((_curTime[LEFT] - _oldTime[LEFT] >= 1 * 200 && _doubleKey[LEFT] == 1) && !(_player.state == PLAYER_RUN && _player.direction == LEFT))		
	{
		_doubleKey[LEFT]--;
		_oldTime[LEFT] = GetTickCount();
	}
	if ((_curTime[RIGHT] - _oldTime[RIGHT] >= 1 * 200 && _doubleKey[RIGHT] == 1) && !(_player.state == PLAYER_RUN))
	{
		_doubleKey[RIGHT]--;
		_oldTime[RIGHT] = GetTickCount();
	}
	if ((_curTime[UP] - _oldTime[UP] >= 1 * 200 && _doubleKey[UP] == 1) && !(_player.state == PLAYER_RUN))
	{
		_doubleKey[UP]--;
		_oldTime[UP] = GetTickCount();
	}
	if ((_curTime[DOWN] - _oldTime[DOWN] >= 1 * 200 && _doubleKey[DOWN] == 1) && !(_player.state == PLAYER_RUN))
	{
		_doubleKey[DOWN]--;
		_oldTime[DOWN] = GetTickCount();
	}

	if (GetTickCount() - _oldAttackTime >= 1 * 400 && _attackComboKey == 1)
	{
		_attackComboKey--;
		_oldAttackTime = GetTickCount();
	}
}
//중복되는 코드 줄일라고 만든 함수
void player::playerAniName(string targetName, string aniName)
{
	_player.ani = KEYANIMANAGER->findAnimation(targetName, aniName);
	_player.ani->start();
}

void player::attack(void * obj)
{
	player* playerAttack = (player*)obj;

	playerAttack->setPlayerState(PLAYER_IDLE);
	if (playerAttack->getPlayerDirection() == LEFT)
	{
		playerAttack->setPlayerDirection(LEFT);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleLeft"));
	}
	if (playerAttack->getPlayerDirection() == RIGHT)
	{
		playerAttack->setPlayerDirection(RIGHT);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleRight"));
	}
	if (playerAttack->getPlayerDirection() == UP)
	{
		playerAttack->setPlayerDirection(UP);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleUp"));
	}
	if (playerAttack->getPlayerDirection() == DOWN)
	{
		playerAttack->setPlayerDirection(DOWN);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleDown"));
	}
	playerAttack->getPlayerAni()->start();
}

void player::jump(void * obj)
{
	player* playerAttack = (player*)obj;

	playerAttack->setPlayerState(PLAYER_IDLE);
	if (playerAttack->getPlayerDirection() == LEFT)
	{
		playerAttack->setPlayerDirection(LEFT);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleLeft"));
	}
	else if (playerAttack->getPlayerDirection() == RIGHT)
	{
		playerAttack->setPlayerDirection(RIGHT);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleRight"));
	}
	else if (playerAttack->getPlayerDirection() == UP)
	{
		playerAttack->setPlayerDirection(UP);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleUp"));
	}
	else if (playerAttack->getPlayerDirection() == DOWN)
	{
		playerAttack->setPlayerDirection(DOWN);
		playerAttack->setPlayerAni(KEYANIMANAGER->findAnimation("ark", "idleDown"));
	}
	playerAttack->getPlayerAni()->start();
}

void player::jumpAttack(void * obj)
{
}

void player::dashAttack(void * obj)
{
}

void player::dashJumpAttack(void * obj)
{
}

void player::objThrow(void * obj)
{
}
