#pragma once
#include "gameNode.h"

class DashJumpAttack : public gameNode
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
	DashJumpAttack();
	~DashJumpAttack();

	HRESULT init();
	void release();
	void update();
	void render();

	void jumping(float* x, float* y, float* startX, float* startY, float jumpPower, float gravity);
};
