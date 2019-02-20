#pragma once
#include "gameNode.h"
#include "camera.h"

struct tagIntro
{
	image* image;
	int alphaValue; //알파값
	bool padeIn, padeOut; 
	bool isIntroImageShow; //인트로이미지 보여줄건지
	POINTFLOAT cameraPos;
};

class intro : public gameNode
{
private:
	tagIntro _intro;
	camera* _camera;
	HFONT _font;
	HFONT _oldFont;
	vector<string*> _vMessage;

	float _textWolrldTime;

	int _talkCount;
public:
	intro();
	~intro();

	HRESULT init();
	void release();
	void update();
	void render();

	void opening(); //오프닝

	void messageAll(); //메시지 모음
	void messageDraw(const char* txtName); //메시지 그리기

	void setWindowsSize(int x, int y, int width, int height);
	
};

