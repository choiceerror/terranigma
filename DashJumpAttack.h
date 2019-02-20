#pragma once
#include "gameNode.h"

class DashJumpAttack : public gameNode
{
private:
	float _jumpPower;
	float _gravity;

	float _speed;

	float* _x;
	float* _y;
	float* _startX;
	float* _startY;

	int _direction;

	bool _isJumpAttack;

public:
	DashJumpAttack();
	~DashJumpAttack();

	HRESULT init();
	void release();
	void update(float* x, float* y);
	void render();

	void dashJumpAttack(float* x, float* y, float* startX, float* startY, float jumpPower, float gravity, int direction, float speed);
};
