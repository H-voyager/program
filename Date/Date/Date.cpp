#include "Date.h"

bool Date::operator>(const Date& d) const
{
	if (_year > d._year)
	{
		return true;
		if (_year == d._year && _month > d._month)
		{
			return true;
			if (_year == d._year && _month == d._month && _day > d._day)
			{
				return true;
			}
		}
	}
	return false;
}
bool Date::operator>=(const Date& d) const
{
	if (*this < d)
	{
		return false;
	}
	return true;
	//return *this > d || *this == d;
}

bool Date::operator<(const Date& d) const
{
	if (*this >= d)
	{
		return false;
	}
	return true;
}

bool Date::operator<=(const Date& d) const
{
	if (*this > d)
	{
		return false;
	}
	return true;
}

bool Date::operator==(const Date& d) const
{
	if (_year ==d._year && _month == d._month && _day ==d._day )
	{
		return true;
	}
	return false;
}
bool Date::operator!=(const Date& d) const
{
	if (_year != d._year || _month != d._month || _day != d._day)
		return false;
}

// ++d
Date& Date::operator++()	// 前置++
{
	*this += 1;
	return *this;
}

// d++
Date Date::operator++(int) // 后置++
{
	Date ret(*this);
	*this += 1;
	return ret;
}


// 前置--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

//后置--
Date Date::operator--(int)
{
	Date ret (*this);
	*this -= 1;
	return ret;
}

Date Date::operator+(int day) const
{
	Date ret = *this;
	ret += day;
	return ret;
}

Date& Date::operator+=(int day)
{
	//if (day < 0)
	//	return *this -= -day;

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13)
		{
			++_year;
			_month = 1;
		}
	}

	return *this;
}

Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day <= 0)
	{
		if (_month = 1)
		{
			_year--;
			_month = 12;
		}
		else
		{
			_month--;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

Date Date::operator-(int day) const
{
	Date ret = *this;
	ret -= day;
	return ret;

}

int Date::operator-(const Date&d)
{
	Date maxdate(*this);//max_date
	Date mindate(d);
	int flag = 1;

	if (maxdate < mindate)
	{
		maxdate = d;
		mindate = *this;
		flag = -1;
	}

	int ndays = 0;
	while (mindate != maxdate)
	{
		mindate += 1;
		ndays++;
	}
	return ndays;
	//while (1)
	//{
	//	if (MinDate + Nday == MaxDate)
	//	{
	//		return Nday*flag;
	//	}
	//	Nday++;
	//}
}

void TestDate()
{
	Date d1(2019,1,1);
	d1 += 2000;
	d1.Print();
	
}

int main()
{
	TestDate();
	return 0;


}