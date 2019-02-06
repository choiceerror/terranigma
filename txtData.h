#pragma once
#include "singletonBase.h"
#include <vector>

class txtData : public singletonBase<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT init();
	void release();

	//저장 관련 함수

	//txt로 파일저장함수 (세이브 파일 이름, 문자열 벡터)
	void txtSave(const char* saveFileName, vector<string> vStr);
	//    문자조합용 함수(문자열 벡터)
	char* vectorArrayCombine(vector<string> vArray);


	//불러오기 관련 함수
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

};

