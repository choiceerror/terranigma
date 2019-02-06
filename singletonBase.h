#pragma once

template <typename T>
class singletonBase
{
protected:
	//싱글톤 인스턴스화 시킬 것.
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};
public:

	static T* getSingleton();	//싱글톤접근자
	void releaseSingleton();	//없애는거
};

//싱글톤 초기화
template <typename T>
T* singletonBase<T>::singleton = 0;


template <typename T>
T* singletonBase<T>::getSingleton()
{
	if (!singleton) singleton = new T;

	return singleton;
}

template <typename T>
void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}