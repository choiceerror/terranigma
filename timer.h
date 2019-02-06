#pragma once

class timer
{
private:
	float	_timeScale;
	float	_timeElapsed;	//밀리세컨드 

	__int64 _curTime;		//현재 주기
	__int64 _lastTime;		//갱신시간 저장용
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;

	float _FPSTimeElapsed;
	float _worldTime;

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	inline float getElapsedTime() const { return _timeElapsed; }
	inline float getWorldTime() const { return _worldTime; }

};

