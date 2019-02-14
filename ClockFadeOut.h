#pragma once
#include "gameNode.h"

class ClockFadeOut : public gameNode
{
private:
	bool _isClockFadeOut;

	POINT _clockBlackPt[12];
	POINT _clockMagentaPt[12];
	float _clockBlackAngle[4];
	float _clockMagentaAngle[4];

	float _clockWorldTime;

	bool _onceTime;

	float _angleSpeed;

	RECT _magentaBox;

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

};

