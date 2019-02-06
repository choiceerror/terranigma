#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* _timer;	//만든 타이머를 가져온다

public:
	timeManager();
	~timeManager();

	HRESULT init();
	void release();
	void update(float lockFPS = 0.0f);
	void render(HDC hdc);

	//cpu경과시간을 받아오는 함수
	inline float getElapsedTime() const { return _timer->getElapsedTime(); }
	
	//총 경과시간을 받아오는 함수
	inline float getWorldTime() const { return _timer->getWorldTime(); }
};

