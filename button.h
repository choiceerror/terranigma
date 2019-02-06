#pragma once
#include "gameNode.h"

//콜백함수 == 함수포인터
typedef void(*CALLBACK_FUNCTION)(void);

//공부를 하면 참좋은게 있어서 알려드리러 왔습니다 ^^*
//<functional> 이란 라이브러리가 있는데욤
//여기에 std::bind, std::move, std::Function 등등 참 좋은게 있어요
//이것을 사용하면 일반매개변수도 콜백함수에서 사용할수 있어욤

//동휘, 재만, 진형, 치영, 범기, 수호형님, 도연이, 남규, 찬희
//는 주말에 집에가서 해오세요 반드시 '해(do it !sun)'와라
//그리고 람다식이란게 있는데 이거랑 엮어서 하면 츠아아암 좋습니다
//팀푸로젝트때도 좋을꺼 같아요

//그 외 나머지 사람은 delegate 란게 있어요 조사를 해오세요
//콜백함수와 델리게이트의 차이를 '인지'하고 계셨음 좋겠네용
//좋은 주말되세욤 *^^*

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;	//버튼의 상태 이넘문

	const char* _imageName;
	image* _image;
	RECT _rc;

	float _x, _y;		//위치 좌표
	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;

public:
	button();
	~button();

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);

	void release();
	void update();
	void render();
};

