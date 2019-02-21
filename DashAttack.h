#pragma once
#include "gameNode.h"

class DashAttack : public gameNode
{
private:
	
	float _speed;

	float* _startX;
	float* _startY;
	float* _x;
	float* _y;

	int _direction;

	bool _isDashAttack;

public:
	DashAttack();
	~DashAttack();

	HRESULT init();
	void release();
	void update(float* x, float* y, bool objUnMove, int _playerState);
	void render();

	void dashAttacking(float* x, float* y, float* startX, float* startY, int direction, float speed);
	bool getDashAttack() { return _isDashAttack; }
};

