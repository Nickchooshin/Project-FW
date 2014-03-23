#pragma once

template <class T>
class Singleton
{
public:
	static T *ms_pSingleton;

public:
	Singleton()
	{
		unsigned __int64 ulOffset = (unsigned __int64)((T*)(1)) - (unsigned __int64)((Singleton<T>*)(T*)1);

		ms_pSingleton = (T*)((unsigned __int64)this + ulOffset);
	}

	virtual ~Singleton()
	{
		ms_pSingleton = 0;
	}

	static T* GetSingleton() { return(ms_pSingleton); }
};

template <class T> T* Singleton<T>::ms_pSingleton = 0;