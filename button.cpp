#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth() * 1.5f, _image->getFrameHeight() * 1.5f);


	return S_OK;
}

void button::release()
{
}

void button::update()
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;


}

void button::render()
{
	switch (_direction)
	{
		case BUTTONDIRECTION_NULL:	case BUTTONDIRECTION_UP:
			_image->expandRenderCenter(getMemDC(), _x, _y,
				_btnUpFramePoint.x, _btnUpFramePoint.y, 1.5f, 1.5f);
		break;
		case BUTTONDIRECTION_DOWN:
			_image->expandRenderCenter(getMemDC(), _x, _y,
				_btnDownFramePoint.x, _btnDownFramePoint.y, 1.5f, 1.5f);
		break;
	
	}
}
