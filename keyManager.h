#pragma once
#include "singletonBase.h"
#include <bitset>

using namespace std;

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyPast;
	bitset<KEYMAX> _keyCurrent;

public:
	HRESULT init();
	void release();
	void update();

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);


	keyManager();
	~keyManager();
};
