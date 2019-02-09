#pragma once
class jump
{
public:
	jump();
	~jump();

	HRESULT init();
	void release();
	void update();
	void render();
};

