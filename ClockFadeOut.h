#pragma once
#include "gameNode.h"

class ClockFadeOut : public gameNode
{
private:
	bool _isClockFadeOut;
	bool _isClockFadeIn;

	POINT _clockBlackPt[12];
	POINT _clockMagentaPt[12];
	float _clockBlackAngle[4];
	float _clockMagentaAngle[4];

	float _clockWorldTime;
	float _clockWorldTimeIn;

	bool _onceTime;
	bool _onceTimeIn;

	float _angleSpeed;

	RECT _magentaBox;
	RECT _blackBox;

	bool _goalArrive[8];


public:
	ClockFadeOut();
	~ClockFadeOut();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createColorObject3(const char* hdcName, POINT* point, COLORREF color);
	void pointSetting();

	bool getClockFadeOut() { return _isClockFadeOut; }
	void setClockFadeOut(bool torf) { _isClockFadeOut = torf; }

	bool getClockFadeIn() { return _isClockFadeIn; }
	void setClockFadeIn(bool torf) { _isClockFadeIn = torf; }
};

