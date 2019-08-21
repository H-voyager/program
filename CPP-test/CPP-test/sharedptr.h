#pragma once
#include <thread>
#include <mutex>

using std::mutex;

template <class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr)
		: _ptr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{}
	~SharedPtr()
	{
		Release();
	}

	SharedPtr(const SharedPtr<T>& sp)
		: _ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefConut();
	}

	void AddRefConut()
	{
		//加锁或者使用加1的原子操作
		_pMutex->lock();
		(*_pRefCount);
		_pMutex->unlock();
	}
	//sp1 = sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		//if(this != &sp)
		if (_ptr != sp._ptr)
		{
			//释放管理的旧资源
			Release();
			
			//共享管理新资源的对象,并增加引用计数
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;

			AddRefConut();
		}
		return *this;
	}

	T& operator*() { return *_ptr; }
	T* operator->() { return _ptr; }
	int UseCount() { return *_pRefCount; }
	T* Get() { return _ptr; }
private:
	void Release()
	{
		bool deleteflag = false;
		//引用计数减一.如果减值0 释放资源
		_pMutex->lock();

		if ((*_pRefCount == 0))
		{
			delete _ptr;
			delete _pRefCount;
			deleteflag = true;
		}
		_pMutex->unlock();

		if (deleteflag == true)
		{
			delete _pMutex;
		}
	}
private:
	mutex *_pMutex; //互斥锁
	int *_pRefCount; //引用计数
	T* _ptr;//指向管理资源的指针

};

