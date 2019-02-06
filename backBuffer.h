#pragma once
class backBuffer
{
public:
	typedef struct tagBackBufferInfo
	{
		HDC		hMemDC;		//메모리 DC
		HBITMAP hBit;		//비트맵 핸들
		HBITMAP hOBit;		//비트맵 핸들(올드)
		int		width;		//가로크기
		int		height;		//세로크기

		tagBackBufferInfo()
		{
			hMemDC		= NULL;
			hBit		= NULL;
			hOBit		= NULL;
			width		= 0;
			height		= 0;
		}
	}BACKBUFFER_INFO, *LPBACKBUFFER_INFO;

private:
	LPBACKBUFFER_INFO _backBuffer;

public:

	backBuffer();
	~backBuffer();

	//백DC 초기화용	DC크기
	HRESULT init(int width, int height);

	void release();

	void render(HDC hdc, int destX, int destY);

	inline HDC getMemDC() { return _backBuffer->hMemDC; }
};

