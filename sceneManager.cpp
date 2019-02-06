#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

gameNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	//씬이 없다면 널값을 반환해라
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//변경할 씬을 못찾았다
	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	//성공적으로 씬이 변경이되면 init함수를 실행
	if (SUCCEEDED(find->second->init()))
	{
		//현재 어떤 씬의 정보가 들어있을수도 있으므로 릴리즈 시켜주고
		if (_currentScene) _currentScene->release();

		//바꾸려는 씬을 현재 씬으로 교체한다.
		_currentScene = find->second;

		//이 씬구조는 입맛에 따라 바꿔도 상관이 없다.
		//다만 예를 들어 맵툴씬에서 맵을 그린 것을 저장하고 다음씬으로 변경할때
		//저장을 먼저 시키지않으면 체인지씬 함수가 발동됨과 동시에 데이터가 사라짐.

		return S_OK;
	}


	return E_FAIL;
}
