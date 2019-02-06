#pragma once

//=====================================
// ## 18.11.20 ## 매크로를 모아두자 ##
//=====================================

//파이
#define PI 3.141592654f
//원
typedef struct tagELLIPSE
{
	POINT p;
	float r;
} ELLIPSE, *LPELLIPSE;
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}
//================= 렉트 관련 함수 ========================
//    렉트를 만든다(레프트, 탑, 가로크기, 세로크기)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}
//    렉트를 만든다(중점X좌표, 중점Y좌표, 가로크기, 세로크기)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}
//================= 사각형 관련 함수 ======================
//          사각형 생성함수(뿌려줄DC, left, top, 가로크기, 세로크기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
//====================== 동 그 라 미 관련 ===============================
//        원 생성함수 (hdc, left, top, 가로크기, 세로크기)
inline ELLIPSE EllipseMake(float x, float y, float r)
{
	ELLIPSE rt;
	rt.p.x = x;
	rt.p.y = y;
	rt.r = r;
	return rt;
}
//        원 생성함수 (hdc, 센터좌표 X, 센터좌표 Y, 가로크기, 세로크기)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
//        원 그림
inline void EllipseRender(HDC hdc, ELLIPSE& e)
{
	Ellipse(hdc, e.p.x - e.r, e.p.y - e.r, e.p.x + e.r, e.p.y + e.r);
}

inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//라디안 각도를 디그리로
inline float RadToDeg(float angle)
{
	return angle * (180.0f / PI);
}
//디그리 각도를 라디안으로
inline float DegToRad(float angle)
{
	return angle * (PI / 180.0f);
}

//거리구하기
inline float GetDistance(POINT& p1, POINT& p2)
{
	return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
//원충돌했는지
inline bool EllipseCollision(ELLIPSE& e1, ELLIPSE& e2)
{
	return (e1.r + e2.r >= GetDistance(e1.p, e2.p));
}
//두 숫자의 사이값
inline float GetCenter(float a, float b)
{
	return a + (b - a) / 2;
}
//렉트 중점 반환함수
inline POINT GetRectCenter(RECT& rc)
{
	POINT p;
	p.x = GetCenter(rc.left, rc.right);
	p.y = GetCenter(rc.top, rc.bottom);
	return p;
}
//렉트 x중점 반환 함수
inline float GetRectXCenter(RECT& rc)
{
	return GetCenter(rc.left, rc.right);
}
//렉트 y중점 반환 함수
inline float GetRectYCenter(RECT& rc)
{
	return GetCenter(rc.top, rc.bottom);
}
//렉트 width 반환 함수
inline float GetRectWidth(RECT& rc)
{
	return rc.right - rc.left;
}
//렉트 height 반환 함수
inline float GetRectHeight(RECT& rc)
{
	return rc.bottom - rc.top;
}
//원 점 충돌
inline bool PtInEllipse(ELLIPSE& e, POINT p)
{
	return (e.r >= GetDistance(e.p, p));
}
//원 사각형 충돌
inline bool RectEllipseCollition(RECT& rc, ELLIPSE& e)
{
	if ((rc.left <= e.p.x && e.p.x <= rc.right) || (rc.top <= e.p.y && e.p.y <= rc.bottom))
	{
		RECT rc2 = { rc.left - e.r, rc.top - e.r, rc.right + e.r, rc.bottom + e.r };
		if (PtInRect(&rc2, e.p))return true;
	}
	else
	{
		POINT p;
		p.x = rc.left;
		p.y = rc.top;
		if (PtInEllipse(e, p)) return true;
		p.x = rc.left;
		p.y = rc.bottom;
		if (PtInEllipse(e, p)) return true;
		p.x = rc.right;
		p.y = rc.top;
		if (PtInEllipse(e, p)) return true;
		p.x = rc.right;
		p.y = rc.bottom;
		if (PtInEllipse(e, p)) return true;
	}
	return false;
}
//렉트 색칠
inline void RectangleBrush(HDC hdc, RECT& rc, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
	Rectangle(hdc, rc);
	SelectObject(hdc, oBrush);
	DeleteObject(brush);
}
//원색칠
inline void EllipseBrush(HDC hdc, ELLIPSE& e, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
	EllipseRender(hdc, e);
	SelectObject(hdc, oBrush);
	DeleteObject(brush);
}

//디그리 코사인
inline float dCosf(float angle)
{
	return cosf(DegToRad(angle));
}
//디그리 사인
inline float dSinf(float angle)
{
	return sinf(DegToRad(angle));
}