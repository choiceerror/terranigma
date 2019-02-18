#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"
#include "dungeonMap.h"
#include "townMap.h"

void player::playerUIRender(bool uiRender)
{
	if (uiRender)
	{
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), 100, 100, 3, 1, 1.3, 1.3);	//레벨
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), 250, 100, 2, 1, 1.3, 1.3); //아이템
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), 100, 150, _player.level, 0, 1.3, 1.3); //레벨 숫자
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 150, 100, 1, 1, 1.3, 1.3);	//HP글씨
		if (!((_player.HP / 10) % 10 == 0))
		{
			IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 210, 150, (_player.HP / 10) % 10, 0, 1.3, 1.3); //십의자리
		}
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 180, 150, _player.HP % 10, 0, 1.3, 1.3); //일의자리
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 150, 150, 4, 1, 1.3, 1.3); //짝대기
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 120, 150, (_player.maxHP / 10) % 10, 0, 1.3, 1.3); //max 십의자리
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 90, 150, _player.maxHP % 10, 0, 1.3, 1.3); // "   일의자리
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 200, GAMESIZEY - 100, 0, 1, 1.3, 1.3); //돈이미지
		if (!((_player.money / 100) % 10 == 0))
		{
			IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 150, GAMESIZEY - 100, (_player.money / 100) % 10, 0, 1.3, 1.3); //돈 백의 자리
		}
		if (!((_player.money / 10) % 10 == 0))
		{
			IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 120, GAMESIZEY - 100, (_player.money / 10) % 10, 0, 1.3, 1.3); //돈 십의 자리
		}
		IMAGEMANAGER->findImage("player_ui")->expandRenderCenter(getMemDC(), GAMESIZEX - 90, GAMESIZEY - 100, _player.money % 10, 0, 1.3, 1.3); //돈 일의 자리
	}
}