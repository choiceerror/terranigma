#pragma once
#include "singletonBase.h"
#include <map>

//¾ÀÀ» À§ÇÑ °ÔÀÓ³ëµå Àü¹æ¼±¾ð
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>			 mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode*	_currentScene;	//ÇöÀç ¾À
	mapSceneList		_mSceneList;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//¾À Ãß°¡ ÇÔ¾¥
	gameNode* addScene(string sceneName, gameNode* scene);

	//¾À º¯°æ ÇÔ¾¥
	HRESULT changeScene(string sceneName);


};

