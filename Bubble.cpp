#include "stdafx.h"
#include "Bubble.h"


Bubble::Bubble()
{
}


Bubble::~Bubble()
{
}

HRESULT Bubble::init()
{
	IMAGEMANAGER->addFrameImage("bubble", "image/bubble.bmp", 720, 360, 8, 4, true, MAGENTA);
	IMAGEMANAGER->findImage("bubble")->setAlpahBlend(true);


	return S_OK;
}

void Bubble::release()
{
	for (int i = 0; i < _vBubble.size(); ++i)
	{
		SAFE_DELETE(_vBubble[i]);
	}

	_vBubble.clear();
}

void Bubble::update()
{
	for (int i = 0; i < _vBubble.size(); ++i)
	{
		_vBubble[i]->count++;

		if (_vBubble[i]->image->getFrameX() >= _vBubble[i]->image->getMaxFrameX()) _vBubble[i]->frameX = 1;

		if (_vBubble[i]->count % 10 == 0)
		{
			_vBubble[i]->frameX += 1;

			_vBubble[i]->count = 0;
		}

		_vBubble[i]->x += cosf(_vBubble[i]->angle) * _vBubble[i]->speed;
		_vBubble[i]->y += -sinf(_vBubble[i]->angle) * _vBubble[i]->speed;
	}

	eraseBubble();
}

void Bubble::render(float cameraX, float cameraY)
{
	for (int i = 0; i < _vBubble.size(); ++i)
	{
		_vBubble[i]->image->alphaFrameRender(getMemDC(), _vBubble[i]->x - cameraX, _vBubble[i]->y - cameraY, _vBubble[i]->frameX, _vBubble[i]->frameY, 180);

		//if (_vBubble[i]->x - cameraX > -100 && _vBubble[i]->x - cameraX < 1154 && _vBubble[i]->y - cameraY > -130 && _vBubble[i]->y - cameraY < 898)
		{
		}

		//char str[120];
		//sprintf_s(str, "%d %d", _vBubble[20]->frameX, _vBubble[20]->frameY);
		//TextOut(getMemDC(), 300, 400, str, strlen(str));

	}
}

void Bubble::createBubble(float x, float y, int frameX, int frameY)
{
	tagBubble* bubble;
	bubble = new tagBubble;
	bubble->image = IMAGEMANAGER->findImage("bubble");
	bubble->imageName = "bubble";
	bubble->frameX = frameX;
	bubble->frameY = frameY;
	bubble->x = x;
	bubble->y = y;
	bubble->startX = RND->getRandomInt(-1800, 1800);
	bubble->startY = RND->getRandomInt(1930,2000);
	bubble->count = RND->getRandomInt(0,8);
	bubble->angle = (PI / 180) * 45;
	bubble->speed = 1.3f;
	bubble->isLive = true;

	_vBubble.push_back(bubble);
}

void Bubble::eraseBubble()
{
	for (int i = 0; i < _vBubble.size();++i)
	{
		if (_vBubble[i]->y < -100 || _vBubble[i]->x > 2020)
		{
			_vBubble[i]->isLive = false;

			_vBubble[i]->x = _vBubble[i]->startX;
			_vBubble[i]->y = _vBubble[i]->startY;
		}

		if (i < _vBubble.size() - 1)
		{
			for (int j = i + 1; j < _vBubble.size(); ++j)
			{
				if (getDistance(_vBubble[i]->x, _vBubble[i]->y, _vBubble[j]->x, _vBubble[j]->y) < 250 && _vBubble[i]->y > 1900)
				{
					_vBubble[i]->x = _vBubble[i]->startX;
					_vBubble[i]->y = _vBubble[i]->startY;
				}
			}
		}
	}

	//for (int i = 0; i < _vBubble.size();)
	//{
	//	if (_vBubble[i]->isLive == false)
	//	{
	//		_vBubble.erase(_vBubble.begin() + i);
	//	}
	//	else
	//	{
	//		++i;
	//	}
	//}
}
