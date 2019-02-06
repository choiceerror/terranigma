#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"


keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
	deleteAll();
}

void keyAniManager::update()
{
	iterAniMap iter = _mTotalAnimations.begin();

	for (iter; _mTotalAnimations.end() != iter; ++iter)
	{
		iterAnimation it = (*iter).second->begin();
		iterAnimation end = (*iter).second->end();
		for (it; it != end; ++it)
		{
			if (!it->second->isPlay()) continue;

			it->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		}
	}
}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);


	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}


void keyAniManager::addCoordinateFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string targetName, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		arrAnim = new arrAnimation;
		_mTotalAnimations.insert(pair<string, arrAnimation*>(targetName, arrAnim));
	}

	arrAnim = _mTotalAnimations[targetName];
	arrAnim->insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::start(string targetName, string animationKeyName)
{
	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		return;
	}

	arrAnim = _mTotalAnimations[targetName];
	if (arrAnim->find(animationKeyName) != arrAnim->end())
	{
		iterAnimation iter = arrAnim->find(animationKeyName);
		iter->second->start();
	}
}

void keyAniManager::stop(string targetName, string animationKeyName)
{
	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		return;
	}

	arrAnim = _mTotalAnimations[targetName];
	if (arrAnim->find(animationKeyName) != arrAnim->end())
	{
		iterAnimation iter = arrAnim->find(animationKeyName);
		iter->second->stop();
	}
}

void keyAniManager::pause(string targetName, string animationKeyName)
{
	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		return;
	}

	arrAnim = _mTotalAnimations[targetName];
	if (arrAnim->find(animationKeyName) != arrAnim->end())
	{
		iterAnimation iter = arrAnim->find(animationKeyName);
		iter->second->pause();
	}
}

void keyAniManager::resume(string targetName, string animationKeyName)
{
	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		return;
	}

	arrAnim = _mTotalAnimations[targetName];
	if (arrAnim->find(animationKeyName) != arrAnim->end())
	{
		iterAnimation iter = arrAnim->find(animationKeyName);
		iter->second->resume();
	}
}

animation* keyAniManager::findAnimation(string targetName, string animationKeyName)
{
	arrAnimation* arrAnim = nullptr;
	if (_mTotalAnimations.find(targetName) == _mTotalAnimations.end())
	{
		return nullptr;
	}

	arrAnim = _mTotalAnimations[targetName];
	if (arrAnim->find(animationKeyName) != arrAnim->end())
	{
		iterAnimation iter = arrAnim->find(animationKeyName);
		return iter->second;
	}

	return nullptr;
}

void keyAniManager::deleteAll()
{
	iterAniMap iter = _mTotalAnimations.begin();

	for (iter; _mTotalAnimations.end() != iter; ++iter)
	{
		iterAnimation it = (*iter).second->begin();
		iterAnimation end = (*iter).second->end();
		for (it; it != end;)
		{
			if (it->second != NULL)
			{
				it->second->release();
				SAFE_DELETE(it->second);
				it = (*iter).second->erase(it);
			}
			else
				++it;
		}

		(*iter).second->clear();
	}

	_mTotalAnimations.clear();
}
