#pragma once
#include "gameNode.h"

#define LOADINGMAX 30000

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;
	image* _background;

	
public:
	loadingScene();
	~loadingScene();

	int _currentCount;	//외부에서 접근할수있게 해둔당

	HRESULT init();
	void release();
	void update();
	void render();
	
};

static DWORD CALLBACK ThreadFunction(LPVOID lpParameter);
