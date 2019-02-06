#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect()
	: _effectImage(NULL), 
	_effectAnimation(NULL),
	_isRunning(false), 
	_x(0), _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init(image * effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;


	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

void effect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update()
{

	//이펙트 애니메이션 실행중이 아니면 실행하지마라
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(_elapsedTime);

	//애니메이션 재생신호가  false면 이펙트를 꺼라
	if (!_effectAnimation->isPlay()) killEffect();


}

void effect::render()
{
	//애니메이션이 재생중이 아니라면 렌더링 하지 않는다
	if (!_isRunning) return;

	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

void effect::startEffect(int x, int y)
{
	//이펙트이미지 or 이펙트애니메이션 셋팅이 되어있지않으면 이펙트 실행중지
	if (!_effectImage || !_effectAnimation) return;

	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;

	_effectAnimation->start();
}

void effect::killEffect()
{
	_isRunning = false;
}
