#pragma once
#include "gameNode.h"

class blackFadeOut : public gameNode
{
private:
	RECT _blackBox;

	bool _isfadeOut;

	POINTFLOAT _pt[4];
	POINTFLOAT _goal;

	float _angle;

	float _centerX, _centerY;

	float _diagonalLength;
	float _diagonalMaxLength;

	float _worldTime;
	bool _once;


public:
	blackFadeOut();
	~blackFadeOut();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createColorObject(const char* hdcName,POINT* point,COLORREF color);
	void pointSetting();
	void diagonalLengthSize();
	void linearInterPolation();



	//================접근자 설정자===================
	
	bool getIsFadeOut() { return _isfadeOut; }
	void setIsFadeOut(bool _bool) { _isfadeOut = _bool; }

	
	void setGoal(float x, float y) { _goal.x = x, _goal.y = y; }
};

