#pragma once
#include <iostream>
#include <string>

using namespace std;

class String
{
public:
	typedef char* iterator;
public:
	String(const char* str = "")
	{
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}
	String(const String& s)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(s._str);
		swap(_str,tmp._str);
	}

	String& operator=(String s)
	{
		swap(_str, s._str);
		return *this;
	}
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}

	iterator begin()
	{
		return _str;
	}
	iterator end()
	{
		return _str + _size;
	}

	void Reserve(size_t n)
	{
		if (n == 0 || n > _capacity)
		{
			size_t newsize = n;
			if (newsize % 8 != 0)
			{
				newsize = (newsize / 8 + 1) * 8;
			}
			char* newstr = new char[newsize];
			if (_str)
			{
				strcpy(newstr, _str);
			}
			_str =  newstr;
			_capacity = newsize - 1;

		}
	}

	void Resize(size_t newsize, char c = '\0')
	{
		if (newsize > _size)
		{
			Reserve(newsize);
			for (size_t i = 0; i < newsize; i++)
			{
				_str[i] = c;
				_size++;
			}
			_str[_size] = '\0';
		}
	}

	void pushback(char c)
	{
		if (_size == _capacity)
		
			Reserve(_capacity * 2);
	}

private:
	char* _str;
	size_t _capacity;
	size_t _size;
};
