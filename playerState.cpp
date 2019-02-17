#include "stdafx.h"
#include "player.h"
//애니메이션 넣을때 중복되는 코드들 정리
void player::playerAniName(string targetName, string aniName)
{
	_player.ani = KEYANIMANAGER->findAnimation(targetName, aniName);
	_player.ani->start();
}
//스위치문으로 각 상태 애니메이션 재생
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
		if (!(_player.state == PLAYER_DASH_ATTACK))
		{
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
		}
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
			playerAniName("ark", "jumpAttackLeft");
			break;
		case RIGHT:
			playerAniName("ark", "jumpAttackRight");
			break;
		case UP:
			playerAniName("ark", "jumpAttackUp");
			break;
		case DOWN:
			playerAniName("ark", "jumpAttackDown");
			break;
		}
		break;
	case PLAYER_DASH_JUMP_ATTACK:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "dashJumpAttackLeft");
			break;
		case RIGHT:
			playerAniName("ark", "dashJumpAttackRight");
			break;
		case UP:
			playerAniName("ark", "dashJumpAttackUp");
			break;
		case DOWN:
			playerAniName("ark", "dashJumpAttackDown");
			break;
		}
		break;
	case PLAYER_DASH_ATTACK:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "dashAttackLeft");
			break;
		case RIGHT:
			playerAniName("ark", "dashAttackRight");
			break;
		case UP:
			playerAniName("ark", "dashAttackUp");
			break;
		case DOWN:
			playerAniName("ark", "dashAttackDown");
			break;
		}
		break;
	case PLAYER_OBJ_PICKUP:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "pickupLeft");
			break;
		case RIGHT:
			playerAniName("ark", "pickupRight");
			break;
		case UP:
			playerAniName("ark", "pickupUp");
			break;
		case DOWN:
			playerAniName("ark", "pickupDown");
			break;
		}
		break;
	case PLAYER_OBJ_WALK:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "objMoveLeft");
			break;
		case RIGHT:
			playerAniName("ark", "objMoveRight");
			break;
		case UP:
			playerAniName("ark", "objMoveUp");
			break;
		case DOWN:
			playerAniName("ark", "objMoveDown");
			break;
		}
		break;
	case PLAYER_OBJ_THROW:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "objThrowLeft");
			break;
		case RIGHT:
			playerAniName("ark", "objThrowRight");
			break;
		case UP:
			playerAniName("ark", "objThrowUp");
			break;
		case DOWN:
			playerAniName("ark", "objThrowDown");
			break;
		}
		break;
	case PLAYER_ENEMY_ATTACK:
		switch (_player.direction)
		{
		case LEFT:
			playerAniName("ark", "enemyAttackLeft");
			break;
		case RIGHT:
			playerAniName("ark", "enemyAttackRight");
			break;
		case UP:
			playerAniName("ark", "enemyAttackUp");
			break;
		case DOWN:
			playerAniName("ark", "enemyAttackDown");
			break;
		}
		break;
	case PLAYER_LEVELUP:
		playerAniName("ark", "levelUp");
		break;
	case PLAYER_DEATH:
		playerAniName("ark", "death");
		break;
	}
}