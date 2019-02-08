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

	IMAGEMANAGER->addFrameImage("player", "image/player.bmp", 0, 0, 1008, 2821, 12, 31, true, RGB(255,0, 255));
	IMAGEMANAGER->addFrameImage("ark_obj", "image/player_obj.bmp", 0, 0, 1540, 800, 10, 10, true, RGB(255, 0, 255));

	_player.image = IMAGEMANAGER->findImage("player");

	int idleLeft[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleLeft", "player", idleLeft, 1, PLAYERFPS, true);
	int idleRight[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleRight", "player", idleRight, 1, PLAYERFPS, true);
	int idleUp[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleUp", "player", idleUp, 1, PLAYERFPS, true);
	int idleDown[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleDown", "player", idleDown, 1, PLAYERFPS, true);
	int idleAction[] = {4, 5, 6, 7, 6, 7, 5, 4};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "idleAction", "player", idleAction, 8, PLAYERFPS, true);
	int moveLeft[] = { 24, 25, 26, 27, 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveLeft", "player", moveLeft, 6, PLAYERFPS, true);
	int moveRight[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveRight", "player", moveRight, 6, PLAYERFPS, true);
	int moveUp[] = { 36, 37, 38, 39, 40, 40 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveUp", "player", moveUp, 6, PLAYERFPS, true);
	int moveDown[] = { 48, 49, 50, 51, 52, 53 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "moveDown", "player", moveDown, 6, PLAYERFPS, true);
	int runLeft[] = {65, 66, 67, 68, 69};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runLeft", "player", runLeft, 5, PLAYERFPS, true);
	int runRight[] = { 60, 61, 62, 63, 64 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runRight", "player", runRight, 5, PLAYERFPS, true);
	int runUp[] = { 72, 73, 74, 75, 76};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runUp", "player", runUp, 5, PLAYERFPS, true);
	int runDown[] = { 77, 78, 79, 80, 81};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "runDown", "player", runDown, 5, PLAYERFPS, true);
	int push[] = { 84, 85 , 86, 87 , 88 , 89};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "push", "player", push, 6, PLAYERFPS, true);
	int jumpLeft[] = { 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpLeft", "player", jumpLeft, 11, PLAYERFPS, false);
	int jumpRight[] = { 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpRight", "player", jumpRight, 11, PLAYERFPS, false);
	int jumpUp[] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpUp", "player", jumpUp, 11, PLAYERFPS, false);
	int jumpDown[] = { 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpDown", "player", jumpDown, 12, PLAYERFPS, false);
	int levelUp[] = {144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "levelUp", "player", levelUp, 11, PLAYERFPS, true);
	int attackLeft[] = {160, 161, 162, 163};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackLeft", "player", attackLeft, 4, PLAYERFPS, false);
	int attackRight[] = { 156, 157, 158, 159 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackRight", "player", attackRight, 4, PLAYERFPS, false);
	int attackUp[] = { 168, 169, 170, 171 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackUp", "player", attackUp, 4, PLAYERFPS, false);
	int attackDown[] = { 172, 173, 174 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "attackDown", "player", attackDown, 3, PLAYERFPS, false);
	int combinationLeft[] = { 192, 193, 194, 195, 196, 197, 198, 199 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationLeft", "player", combinationLeft, 8, PLAYERFPS, false);
	int combinationRight[] = { 180, 181, 182, 183, 184, 185, 186, 187 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationRight", "player", combinationRight, 8, PLAYERFPS, false);
	int combinationUp[] = {204, 205, 206, 207, 208, 209 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationUp", "player", combinationUp, 6, PLAYERFPS, false);
	int combinationDown[] = {216, 217, 218, 219, 220, 221, 222 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "combinationDown", "player", combinationDown, 7, PLAYERFPS, false);
	int jumpAttackLeft[] = {240, 241, 242, 243, 244, 245,246, 247};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackLeft", "player", jumpAttackLeft, 8, PLAYERFPS, false);
	int jumpAttackRight[] = { 228, 229, 230, 231, 232, 233, 234, 235 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackRight", "player", jumpAttackRight, 8, PLAYERFPS, false);
	int jumpAttackUp[] = { 252, 253, 254, 255, 256, 257, 258, 259 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackUp", "player", jumpAttackUp, 8, PLAYERFPS, false);
	int jumpAttackDown[] = { 264, 265, 266, 267, 268, 269, 270, 271 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "jumpAttackDown", "player", jumpAttackDown, 8, PLAYERFPS, false);
	int dashJumpAttackLeft[] = {288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackLeft", "player", dashJumpAttackLeft, 12, PLAYERFPS, false);
	int dashJumpAttackRight[] = { 276,277,278,279,280,281,282,283,284,285,286,287 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackRight", "player", dashJumpAttackRight, 12, PLAYERFPS, false);
	int dashJumpAttackUp[] = {300, 301, 302, 303, 304, 305, 306, 307 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackUp", "player", dashJumpAttackUp, 8, PLAYERFPS, false);
	int dashJumpAttackDown[] = { 312, 313, 314, 315, 316, 317, 318, 319 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashJumpAttackDown", "player", dashJumpAttackDown, 8, PLAYERFPS, false);
	int death[] = {324,325,326,327,328,329};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "death", "player", death, 6, PLAYERFPS, false);
	int fall[] = {330, 331, 332};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "fall", "player", fall, 3, PLAYERFPS, false);
	int dashAttackLeft[] = {340, 341, 342, 343};
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackLeft","player", dashAttackLeft, 4, PLAYERFPS, false);
	int dashAttackRight[] = { 336, 337, 338, };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackLeft", "player", dashAttackLeft, 4, PLAYERFPS, false);
	int dashAttackUp[] = { 340, 341, 342, 343 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackLeft", "player", dashAttackLeft, 4, PLAYERFPS, false);
	int dashAttackDown[] = { 340, 341, 342, 343 };
	KEYANIMANAGER->addArrayFrameAnimation("ark", "dashAttackLeft", "player", dashAttackLeft, 4, PLAYERFPS, false);
	
	



	


	_player.ani = KEYANIMANAGER->findAnimation("ark", "runUp");


	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_player.ani->start();
}

void player::render()
{
	_player.image->aniRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _player.ani);
}
