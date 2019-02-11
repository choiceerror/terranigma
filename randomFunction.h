#pragma once
#include "singletonBase.h"
#include <time.h>
#include <random>

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{}

	//int형 랜덤값을 뽑아보자
	inline int getInt(int num) { return rand() % num; }


	//범위를 정해서 랜덤값 뽑아보기
	                      //    5            10
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
	}

	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }

	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }

	//범위로 소수점 받아오는 함수
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

	//메르센 난수 정수 배출 (min ~ max) 두 숫자 포함
	int getRandomInt(int min, int max)
	{
		random_device rd;
		mt19937 rEngine(rd());
		uniform_int_distribution<> dist(min, max);
		return static_cast<int>(dist(rEngine));
	}
	//메르센 난수 실수 배출 (min ~ max) 두 숫자 포함
	float getRandomFloat(float min, float max)
	{
		random_device rd;
		mt19937 rEngine(rd());
		uniform_real_distribution<> dist(min, max);
		return static_cast<float>(dist(rEngine));
	}
};