#pragma once
#include "singletonBase.h"
#include <vector>

struct tagIniData
{
	const char* subject;	//제갈량
	const char* title;		//지력
	const char* body;		//100
};

class iniDataManager : public singletonBase<iniDataManager>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;

	typedef vector<arrIniData> arrIniDatas;
	typedef vector<arrIniData>::iterator arrIniDatasIter;

private:
	arrIniDatas _vIniData;

public:
	iniDataManager();
	~iniDataManager();

	HRESULT init();
	void release();

	void addData(const char* subject, const char* title, const char* body);
	void iniSave(const char* fileName);

	char* loadDataString(const char* fileName, const char* subject, const char* title);

	int loadDataInteger(const char* fileName, const char* subject, const char* title);
};

