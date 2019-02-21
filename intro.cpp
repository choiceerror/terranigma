#include "stdafx.h"
#include "intro.h"


intro::intro()
{
}


intro::~intro()
{
}

HRESULT intro::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	_camera = new camera;

	_camera->init(GAMESIZEX, GAMESIZEY, WINSIZEX, GAMESIZEY);

	IMAGEMANAGER->findImage("black")->setAlpahBlend(true);

	_intro.image = IMAGEMANAGER->findImage("인트로1");
	_intro.image->setAlpahBlend(true);
	_earthImage = IMAGEMANAGER->findImage("인트로5"); //지구 이미지
	_buttonImage = IMAGEMANAGER->findImage("인트로8"); //버튼이미지
	_buttonWorldTime = TIMEMANAGER->getWorldTime();
	//===========텍스트 관련 =============
	_text.image = IMAGEMANAGER->findImage("인트로6"); //텍스트 이미지
	_text.x = GAMESIZEX / 2;
	_text.y = GAMESIZEY / 2 + 80;
	//===================================

	_intro.alphaValue = 255;
	_intro.isAlpahOn = false;
	_intro.isAlpahOut = true;

	_intro.cameraPos.x = WINSIZEX / 2;
	_intro.cameraPos.y = 0;
	_intro.changeWorldTime = TIMEMANAGER->getWorldTime();
	_intro.changeTime = 10.f;

	_textCount[MESSAGE_ONE] = _textCount[MESSAGE_TWO] = 0;
	_nextText = 0;
	_imageChange = IMAGECHANGE::ONE;
	//messageAll();

	return S_OK;
}

void intro::release()
{
	SAFE_DELETE(_camera);
}

void intro::update()
{
	opening();
	_camera->update(_intro.cameraPos.x, _intro.cameraPos.y);

	
}

void intro::render()
{
	switch (_imageChange)
	{
	case IMAGECHANGE::ONE:
	case IMAGECHANGE::TWO:
	case IMAGECHANGE::THREE:
	case IMAGECHANGE::FOUR:
		_intro.image->render(getMemDC(), 0, 0, _intro.cameraPos.x - _camera->getCameraX(), _intro.cameraPos.y - _camera->getCameraY(), GAMESIZEX, GAMESIZEY);
		break;
	case IMAGECHANGE::FIVE:
		_earthImage->expandRenderCenter(getMemDC(), GAMESIZEX / 2, GAMESIZEY / 2, 0, 0, _earthSizeX, _earthSizeY);
		break;
	case IMAGECHANGE::SIX:
		_intro.image->render(getMemDC(), 0, 0);
		_text.image->expandRenderCenter(getMemDC(), _text.x, _text.y, 0, 0, 1.5f, 1.5f);

		if (0.5f + _buttonWorldTime <= TIMEMANAGER->getWorldTime() && 1.3f + _buttonWorldTime > TIMEMANAGER->getWorldTime())
		{
			_buttonImage->expandRenderCenter(getMemDC(), GAMESIZEX / 2 + 30, GAMESIZEY / 2 + 200, 0, 0, 2.f, 2.f);
		}
		else if (1.3f + _buttonWorldTime <= TIMEMANAGER->getWorldTime())
		{
			_buttonWorldTime = TIMEMANAGER->getWorldTime();
		}
		break;
	}

	IMAGEMANAGER->findImage("black")->alphaRender(getMemDC(), _intro.alphaValue);

	messageDraw();

	//char str[128];

	//sprintf_s(str, "_textCount[MESSAGE_ONE] : %d", _textCount[0]);
	//TextOut(getMemDC(), 100, 80, str, strlen(str));

	//sprintf_s(str, "_textCount[MESSAGE_TWO] : %d", _textCount[1]);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));

	//sprintf_s(str, "isNextPage : %d", _isNextPage);
	//TextOut(getMemDC(), 100, 120, str, strlen(str));

	//sprintf_s(str, "nextText : %d", _nextText);
	//TextOut(getMemDC(), 100, 140, str, strlen(str));

	//sprintf_s(str, "num : %d", _num);
	//TextOut(getMemDC(), 100, 160, str, strlen(str));

	//sprintf_s(str, "alpha : %d", _intro.alphaValue);
	//TextOut(getMemDC(), 100, 240, str, strlen(str));

	//sprintf_s(str, "imageChange : %d", _imageChange);
	//TextOut(getMemDC(), 100, 260, str, strlen(str));


	//sprintf_s(str, "isAlphaOut : %d", _intro.isAlpahOut);
	//TextOut(getMemDC(), 100, 180, str, strlen(str));


	//sprintf_s(str, "isAlphaOn : %d", _intro.isAlpahOn);
	//TextOut(getMemDC(), 100, 200, str, strlen(str));


	//sprintf_s(str, "sizeX : %f", _earthSizeX);
	//TextOut(getMemDC(), 100, 240, str, strlen(str));

	//sprintf_s(str, "sizeY : %f", _earthSizeY);
	//TextOut(getMemDC(), 100, 260, str, strlen(str));

}


void intro::opening()
{
	switch (_imageChange)
	{
	case IMAGECHANGE::ONE:

		//처음일때만
		if (_intro.isAlpahOut == true)
		{
			if (_intro.alphaValue > 0)
			{
				_intro.alphaValue -= ALPHA;
			}
			else if (_intro.alphaValue <= 0)
			{
				_intro.alphaValue = 0;
				_intro.isAlpahOut = false; //알파꺼주고
			}
		}

		//0보다 클때만 카메라좌표빼고
		if (_intro.cameraPos.x > 0)
		{
			_intro.cameraPos.x -= 1;
		}
		else if (_intro.cameraPos.x <= 0)
		{
			//카메라 고정
			_intro.cameraPos.x = 0;
			//대사가 나오는걸 몇초 있기위해 좀있다가 알파꺼줌.
			if (_intro.changeTime + _intro.changeWorldTime <= TIMEMANAGER->getWorldTime())
			{
				_intro.isAlpahOn = true;
			}
		}

		//카메라가 다 이동한후 알파변화
		if (_intro.isAlpahOn == true)
		{
			if (_intro.alphaValue < 255)
			{
				_intro.alphaValue += ALPHA;
			}
			else if (_intro.alphaValue >= 255)
			{
				_intro.alphaValue = 255;
				_intro.isAlpahOn = false; //다음체인지를 위한 알파 끔.
				_intro.isAlpahOut = true; //다음이미지 갔을때 알파 다시적용시키기위해서 켜줌
				_imageChange = IMAGECHANGE::TWO; //끝났으면 이미지 체인지

			}
		}
		break;
	case IMAGECHANGE::TWO:

		if (_intro.isAlpahOut == true)
		{
			
			if (_intro.alphaValue > 0)
			{
				_intro.alphaValue -= ALPHA;
			}
			else if (_intro.alphaValue <= 0)
			{
				_intro.alphaValue = 0;
				_intro.isAlpahOut = false; //알파꺼주고
				_intro.changeWorldTime = TIMEMANAGER->getWorldTime(); //체인지 하기위한 시간 다시받음.
			}
		}

		else if (_intro.isAlpahOn == true)
		{
			if (_intro.alphaValue < 255)
			{
				_intro.alphaValue += ALPHA;
			}
			else if (_intro.alphaValue >= 255)
			{
				_intro.alphaValue = 255;
				_intro.isAlpahOn = false; //다음체인지를 위한 알파 끔.
				_intro.isAlpahOut = true; //다음이미지 갔을때 알파 다시적용시키기위해서 켜줌
				_imageChange = IMAGECHANGE::THREE; //끝났으면 이미지 체인지
			}
		}
		else if (_intro.isAlpahOut == false) //알파가 꺼졌으면
		{
			//시간이 지난뒤에
			if (_intro.changeTime + _intro.changeWorldTime <= TIMEMANAGER->getWorldTime())
			{
				_intro.isAlpahOn = true; //다시킴
			}
		}

		//이미지 한번만 넣기위함
		if (_intro.isOnce[0] == false)
		{
			_intro.image = IMAGEMANAGER->findImage("인트로2");
			_intro.isOnce[0] = true;
		}


		break;
	case IMAGECHANGE::THREE:
		if (_intro.isAlpahOut == true)
		{
			if (_intro.alphaValue > 0)
			{
				_intro.alphaValue -= ALPHA;
			}
			else if (_intro.alphaValue <= 0)
			{
				_intro.alphaValue = 0;
				_intro.isAlpahOut = false; //알파꺼주고
				_intro.changeWorldTime = TIMEMANAGER->getWorldTime(); //체인지 하기위한 시간 다시받음.
			}
		}

		else if (_intro.isAlpahOn == true)
		{
			if (_intro.alphaValue < 255)
			{
				_intro.alphaValue += ALPHA;
			}
			else if (_intro.alphaValue >= 255)
			{
				_intro.alphaValue = 255;
				_intro.isAlpahOn = false; //다음체인지를 위한 알파 끔.
				_intro.isAlpahOut = true; //다음이미지 갔을때 알파 다시적용시키기위해서 켜줌
				_imageChange = IMAGECHANGE::FOUR; //끝났으면 이미지 체인지
			}
		}

		else if (_intro.isAlpahOut == false) //알파가 꺼졌으면
		{
			//시간이 지난뒤에
			if (_intro.changeTime + _intro.changeWorldTime <= TIMEMANAGER->getWorldTime())
			{
				_intro.isAlpahOn = true; //다시킴
			}
		}

		//이미지 한번만 넣기위함
		if (_intro.isOnce[1] == false)
		{
			_intro.image = IMAGEMANAGER->findImage("인트로3");
			_intro.isOnce[1] = true;
		}
		break;
	case IMAGECHANGE::FOUR:
		if (_intro.isAlpahOut == true)
		{
			if (_intro.alphaValue > 0)
			{
				_intro.alphaValue -= ALPHA;
			}
			else if (_intro.alphaValue <= 0)
			{
				_intro.alphaValue = 0;
				_intro.isAlpahOut = false; //알파꺼주고
				_intro.changeWorldTime = TIMEMANAGER->getWorldTime(); //체인지 하기위한 시간 다시받음.
			}
		}
		else if (_intro.isAlpahOn == true)
		{
			if (_intro.alphaValue < 255)
			{
				_intro.alphaValue += ALPHA;
			}
			else if (_intro.alphaValue >= 255)
			{
				_intro.alphaValue = 255;
				_intro.isAlpahOn = false; //다음체인지를 위한 알파 끔.
				_intro.isAlpahOut = true; //다음이미지 갔을때 알파 다시적용시키기위해서 켜줌
				_imageChange = IMAGECHANGE::FIVE; //끝났으면 이미지 체인지
			}
		}
		else if (_intro.isAlpahOut == false) //알파가 꺼졌으면
		{
			//시간이 지난뒤에
			if (_intro.changeTime + _intro.changeWorldTime <= TIMEMANAGER->getWorldTime())
			{
				_intro.isAlpahOn = true; //다시킴
			}
		}

		//이미지 한번만 넣기위함
		if (_intro.isOnce[2] == false)
		{
			_intro.image = IMAGEMANAGER->findImage("인트로4");
			_intro.isOnce[2] = true;
		}
		break;
	case IMAGECHANGE::FIVE:

		if (_intro.isAlpahOut == true)
		{
			if (_intro.alphaValue > 0)
			{
				_intro.alphaValue -= ALPHA;
			}
			else if (_intro.alphaValue <= 0)
			{
				_intro.alphaValue = 0;
				_intro.isAlpahOut = false; //알파꺼주고
				_intro.changeWorldTime = TIMEMANAGER->getWorldTime(); //체인지 하기위한 시간 다시받음.
			}
		}

		if (_intro.alphaValue == 0 && _intro.isSizeUpStop == false)
		{
			_earthSizeX += 0.03f;
			_earthSizeY += 0.03f;

			if (_earthSizeX > 10 && _earthSizeY > 10)
			{
				_intro.isSizeUpStop = true; //점점 커지다가 멈춤
			}
		}

		//지구 사이즈업이 끝나면
		else if (_intro.isSizeUpStop == true)
		{
			if (_intro.alphaValue < 255)
			{
				_intro.alphaValue += ALPHA;
			}
			else if (_intro.alphaValue >= 255)
			{
				_intro.alphaValue = 255;
				_intro.isSizeUpStop = false;
				_intro.isAlpahOut = true; //다음알파값 적용시키기위해서 켜줌.
				_imageChange = IMAGECHANGE::SIX;
			}
		}

		break;
	case IMAGECHANGE::SIX:

		if (_intro.isAlpahOut == true)
		{
			if (_intro.alphaValue > 0)
			{
				_intro.alphaValue -= ALPHA;
			}
			else if (_intro.alphaValue <= 0)
			{
				_intro.alphaValue = 0;
				_intro.isAlpahOut = false; //알파꺼주고
			}
		}
		else if (_intro.isAlpahOut == false)
		{
			//==========선형보간 구간===========
			_text.goal.x = 250;
			_text.goal.y = 150;

			_text.angle = getAngle(_text.x, _text.y, _text.goal.x, _text.goal.y);
			_text.distance = getDistance(_text.x, _text.y, _text.goal.x, _text.goal.y);

			if (_text.isOnce == false)
			{
				_text.moveSpeed = _text.distance * (TIMEMANAGER->getElapsedTime() / 3.0f);
				_text.isOnce = true;
				_text.moveWorldTime = TIMEMANAGER->getWorldTime();
			}

			if (3.f + _text.moveWorldTime >= TIMEMANAGER->getWorldTime())
			{
				_text.x += cosf(_text.angle) * _text.moveSpeed;
				_text.y += -sinf(_text.angle) * _text.moveSpeed;
			}
			//==============================
		}

		if (_intro.isOnce[3] == false)
		{
			_intro.image = IMAGEMANAGER->findImage("인트로7");
			_intro.isOnce[3] = true;
		}

		break;

	}

}

void intro::messageAll()
{
	string message[2];

	vector<string> vStr;

	message[0] = "그 별은 가지고 있었다 두개의 마음을";
	message[1] = "밝은면과 어두운면의 두개의 얼굴이었다.....";
	//message[2] = "이별이 태어난 후 46억년의 세월은..";
	//message[3] = "커다란 두개의 의지에 의해 진화와 쇠퇴를 반복하고 있다.";
	//message[4] = "밝은 면의 의지로 새로운 생명이 태어나고,";
	//message[5] = "어두운 면의 의지로 빙하기가 온다.";
	//message[6] = "밝은 면으로 새로운 기술이 만들어지고,";
	//message[7] = "세월이 지난다음...";
	//message[8] = "어두운 면의 의지에 의해 그 희생자가 나온다..";
	//message[9] = "인류는 그 두개의 의지를 신과 악마 라고 불렀다";

	vStr.push_back(message[0]);
	vStr.push_back(message[1]);
	//vStr.push_back(message[2]);
	//vStr.push_back(message[3]);
	//vStr.push_back(message[4]);
	//vStr.push_back(message[5]);
	//vStr.push_back(message[6]);
	//vStr.push_back(message[7]);
	//vStr.push_back(message[8]);
	//vStr.push_back(message[9]);

	TXTDATA->txtSave("messageFile/인트로.txt", vStr);

}

void intro::messageDraw()
{
	if (_nextText < 6)
	{
		string introText[10];

		_font = CreateFont(30, 17, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "Sam3KRFont");
		_oldFont = (HFONT)SelectObject(getMemDC(), _font);

		_textSizeMax[MESSAGE_ONE] = 40;
		_textSizeMax[MESSAGE_TWO] = 46;
		_textSizeMax[MESSAGE_THREE] = 38;
		_textSizeMax[MESSAGE_FOUR] = 60;
		_textSizeMax[MESSAGE_FIVE] = 44;
		_textSizeMax[MESSAGE_SIX] = 36;
		_textSizeMax[MESSAGE_SEVEN] = 40;
		_textSizeMax[MESSAGE_EIGHT] = 20;
		_textSizeMax[MESSAGE_NINE] = 50;
		_textSizeMax[MESSAGE_TEN] = 52;

		
		if (0.1f + _textWolrldTime <= TIMEMANAGER->getWorldTime())
		{
			if (_textSizeMax[_num] > _textCount[MESSAGE_ONE])
			{
				if(_intro.isAlpahOut == false)
				_textCount[MESSAGE_ONE] += 2;
			}
			else if (_textSizeMax[_num + 1] > _textCount[MESSAGE_TWO])
			{
				if (_intro.isAlpahOut == false)
				_textCount[MESSAGE_TWO] += 2;
			}

			_textWolrldTime = TIMEMANAGER->getWorldTime();
		}
		
		if (_isNextPage == true)
		{
			if (_nextText < 6)
			{
				_nextText++;
			}
			if (_num < 8)
			{
				_num += 2;
			}
			else
			{
				_num = 0;
				_textCount[MESSAGE_ONE] = _textCount[MESSAGE_TWO] = 0;
				_isNextPage = false;
			}
			_isNextPage = false;
			_textCount[MESSAGE_ONE] = _textCount[MESSAGE_TWO] = 0;
		}

		switch (_nextText)
		{
		case MESSAGE_ONE:
			if (_imageChange == IMAGECHANGE::ONE)
			{
				introText[MESSAGE_ONE] = "그  별은  가지고  있었다  두개의  마음을";
				introText[MESSAGE_TWO] = "밝은면과  어두운면의  두개의  얼굴이었다......";
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y, introText[MESSAGE_ONE].c_str(), _textCount[MESSAGE_ONE]);
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y + 50, introText[MESSAGE_TWO].c_str(), _textCount[MESSAGE_TWO]);
			}
			break;
		case MESSAGE_TWO:
			if (_imageChange == IMAGECHANGE::ONE)
			{
				introText[MESSAGE_THREE] = "이별이  태어난  후  46억년의  세월은..";
				introText[MESSAGE_FOUR] = "커다란  두개의  의지에  의해  진화와  쇠퇴를  반복하고  있다";
				TextOut(getMemDC(), MESSAGE_X + 30, MESSAGE_Y, introText[MESSAGE_THREE].c_str(), _textCount[MESSAGE_ONE]);
				TextOut(getMemDC(), MESSAGE_X - 30, MESSAGE_Y + 50, introText[MESSAGE_FOUR].c_str(), _textCount[MESSAGE_TWO]);
			}
			break;
		case MESSAGE_THREE:
			if (_imageChange == IMAGECHANGE::TWO)
			{
				introText[MESSAGE_FIVE] = "밝은  면의  의지로  새로운  생명이  태어나고";
				introText[MESSAGE_SIX] = "어두운  면의  의지로  빙하기가  온다";
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y, introText[MESSAGE_FIVE].c_str(), _textCount[MESSAGE_ONE]);
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y + 50, introText[MESSAGE_SIX].c_str(), _textCount[MESSAGE_TWO]);
			}
			break;
		case MESSAGE_FOUR:
			if (_imageChange == IMAGECHANGE::THREE)
			{
				introText[MESSAGE_SEVEN] = "밝은  면으로  새로운  기술이  만들어지고";
				introText[MESSAGE_EIGHT] = "세월이  지난다음....";
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y, introText[MESSAGE_SEVEN].c_str(), _textCount[MESSAGE_ONE]);
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y + 50, introText[MESSAGE_EIGHT].c_str(), _textCount[MESSAGE_TWO]);
			}
			break;
		case MESSAGE_SIX:
			if (_imageChange == IMAGECHANGE::FOUR)
			{
				introText[MESSAGE_NINE] = "어두운  면의  의지에  의해  그  희생자가  나온다..";
				introText[MESSAGE_TEN] = "인류는  그  두개의  의지를  신과  악마라고  불렀다..";
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y, introText[MESSAGE_NINE].c_str(), _textCount[MESSAGE_ONE]);
				TextOut(getMemDC(), MESSAGE_X, MESSAGE_Y + 50, introText[MESSAGE_TEN].c_str(), _textCount[MESSAGE_TWO]);
			}
			break;

		}

		//if ((_textCount[MESSAGE_ONE] > introText[MESSAGE_ONE].size() && _textCount[MESSAGE_TWO] > introText[MESSAGE_TWO].size())
		//	&& (_textCount[MESSAGE_ONE] > introText[MESSAGE_THREE].size() && _textCount[MESSAGE_TWO] > introText[MESSAGE_FOUR].size())
		//	&& (_textCount[MESSAGE_ONE] > introText[MESSAGE_FIVE].size() && _textCount[MESSAGE_TWO] > introText[MESSAGE_SIX].size())
		//	&& (_textCount[MESSAGE_ONE] > introText[MESSAGE_SEVEN].size() && _textCount[MESSAGE_TWO] > introText[MESSAGE_EIGHT].size())
		//	&& (_textCount[MESSAGE_ONE] > introText[MESSAGE_NINE].size() && _textCount[MESSAGE_TWO] > introText[MESSAGE_TEN].size()))
		//{
		//	_isNextPage = true;
		//}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_isNextPage = true;
		}

		
		SelectObject(getMemDC(), _oldFont);
		DeleteObject(_font);
	}
}

void intro::setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅을 한다
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
