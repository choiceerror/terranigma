#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave(const char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;

	char str[128];

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	//문자 배열은 동적배열로 해서 항상 크기에 맞게 유동적으로 바뀌게
	//수정한 번 해보세요 공부하는 샘 치고
	char str[128];
	ZeroMemory(str, sizeof(str));

	//벡터 사이즈 만큼 반복한다.
	//현재좌표X, 현재좌표Y, 현재체력, 최대체력
	//  300,     300,      80,      100
	for (int i = 0; i < vArray.size(); ++i)
	{
		//vector<string> -> 문자열 char c_str()
		strncat_s(str, 128, vArray[i].c_str(), 126);
		//300,300,80,100

		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}

	return str;
}

vector<string> txtData::txtLoad(const char * loadFileName)
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = ","; //구분자
	char* token;


	token = strtok_s(charArray, separator, &temp);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	//300,300,80,100
	//300

	return vArray;
}
