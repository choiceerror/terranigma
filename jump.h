#pragma once
#include "gameNode.h"

class jump : public gameNode
{
private:
	float _jumpPower;
	float _gravity;

	float* _x;
	float* _y;
	float* _startX;
	float* _startY;

	bool _isJump;

public:
	jump();
	~jump();

	HRESULT init();
	void release();
	void update();
	void render();

	void jumping(float* x, float* y, float* startX, float* startY, float jumpPower, float gravity);

	bool getIsJump() { return _isJump; }
	void setIsJump(bool torf) { _isJump = torf; }
};
