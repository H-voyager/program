#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<typeinfo>
#include <string>
#include <vector>
#include "sharedptr.h"
#include <memory>
#include "BSTree.h"
#include "AVLTree.h"
#include "Seqlist.h"
#include <algorithm>
#include "map.h"
#include "set.h"

//struct fun1
//{
//	void f1();
//};
//
//struct fun2
//{
//	int _a;
//	int _c;
//	char _b;
//	
//};
//
//struct fun3
//{
//
//};

//class A
//{
//public:
//	void PrintA()
//	{
//		cout << _a << endl;
//	}
//	void Show()
//	{
//		cout << "Show()" << endl;
//	}
//private:
//	int _a;
//};

//class Date
//{
//public:
//	Date()
//	{
//		_year = 1900;
//		_month = 1;
//		_day = 1;
//	}
//	Date(int year = 1900, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//// 以下测试函数能通过编译吗？
//void Test()
//{
//	Date d1(1944,20,6);
//}

//class Time
//{
//public:
//	Time()
//	{
//		cout << "Time()" << endl;
//		_hour = 0;
//		_minute = 0;
//		_second = 0;
//	}
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//class Date
//{
//private:
//	// 基本类型(内置类型)
//	int _year;
//	int _month;
//	int _day;
//	// 自定义类型
//	Time _t;
//};

//class String
//{
//public:
//	String(const char* str = "jack")
//	{
//		_str = (char*)malloc(strlen(str) + 1);
//		strcpy(_str, str);
//	}
//	~String()
//	{
//		cout << "~String()" << endl;
//		free(_str);
//	}
//private:
//	char* _str;
//};
//class Person
//{
//private:
//	String _name;
//	int _age;
//};

//class Solution {
//public:
	/**
	*  奇数位上都是奇数或者偶数位上都是偶数
	*  输入：数组arr，长度大于2
	*  len：arr的长度
	*  将arr调整成奇数位上都是奇数或者偶数位上都是偶数
	*/
//	void oddInOddEvenInEven(vector<int>& arr, int len) 
//	{
//		int odd = 1;
//		int eve = 0;
//		int i = 0;
//		int j = 0;	
//
//		while (odd < len && eve < len)
//		{
//
//			if (arr[odd] % 2 == 1)
//			{
//				odd += 2;
//			}
//			if (arr[eve] % 2 == 0)
//			{
//				eve += 2;
//			}
//			if (odd < len && eve <len)
//			{
//				if (arr[odd] % 2 == 0 && arr[eve] % 2 == 1)
//				{
//					swap(arr[odd], arr[eve]);
//				}
//			}
//		}
//
//	}
//
//	void PrintVector(const vector<int>& v) 
//	{    // const对象使用const迭代器进行遍历打印
//		vector<int>::const_iterator it = v.begin();
//		while (it != v.end())
//		{
//			cout << *it << " ";
//			++it;
//		}
//		cout << endl;
//	}
//
//};
//
//class Solutionn {
//public:
//	vector<vector<int>> generate(int numRows) {
//		vector<vector<int>> vv;
//		vv.resize(numRows);
//		for (size_t i = 1; i <= numRows; i++)
//		{
//			vv[i - 1].resize(i, 0);
//			vv[i - 1][0] = 1;
//			vv[i - 1][i - 1] = 1;
//		}
//		for (size_t i = 0; i < vv.size(); i++)
//		{
//			for (size_t j = 0; j < vv[i].size(); j++)
//			{
//				if (vv[i][j] == 0)
//				{
//					vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
//				}
//			}
//		}
//		return vv;
//	}
//};
//
//
//class Solution2 {
//public:
//	string addStrings(string num1, string num2) {
//		int s1 = num1.size();
//		int s2 = num2.size();
//
//		while (s1 > s2){
//			num2 = '0' + num2;
//		}
//		while (s1 < s2){
//			num1 = '0' + num1;
//		}
//
//		for (int i = s1 - 1; i >= 0; i--){
//			num1[i] = num1[i] + num2[i] - '0';
//			if (num1[i] > '9'){
//				num1[i - 1] ++;
//				num1[i] = (num1[i] - '0') % 10 + '0';
//			}
//			num1[0] = num2[0] + num1[0] - '0';
//			if (num1[0] > '9'){
//				num1[0] = (num1[0] - '0') % 10 + '0';
//			}
//			num1 = '1' + num1;
//		}
//		return num1;
//	}
//};
//class A1 {
//public:
//	void f1(){}
//private:
//	int _a;
//};
//// 类中仅有成员函数
//class A2 {
//public:
//	void f2() {}
//private:
//
//	char _b;
//	int _a;
//	char _c;
//};
//// 类中什么都没有---空类
//class A3
//{};
//
//
//class Solution4 {
//public:
//	vector<string> letterCombinations(string digits) {
//		vector<string> f = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
//		vector<string> b;
//
//		if (digits.empty())
//			return b;
//
//		for (int i = 0; i < digits.size(); i++)
//		{
//			int res = digits[i] - '2';
//			int len = b.size();
//			for (int i = 0; i < len; i++)
//			{
//				for (auto m : f[res])
//				{
//					b.push_back(b[i] + m);
//				}
//			}
//			b.erase(b.begin(), b.begin() + len);
//		}
//		return b;
//	}
//};
//
//template<class T>
//bool IsEqual(T& left, T& right)
//{
//	return left == right;
//}
//void Test1()
//{
//	char* p1 = "hello";
//	char* p2 = "world";
//	if (IsEqual(p1, p2))
//		cout << p1 << endl;
//	else
//		cout << *p1 << "," << *p2 << endl;
//		cout << p2 << endl;
//}
//
//#include "point.h"
//#include <list>
//
//
//void TestListIterator1()
//{
//	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
//	list<int> l(array, array + sizeof(array) / sizeof(array[0]));
//	auto it = l.begin();
//	while (it != l.end())
//	{
//		// erase()函数执行后，it所指向的节点已被删除，因此it无效，在下一次使用it时，必须先给其赋值
//		l.erase(it);
//		++it;
//	}	
//	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
//	{
//		cout << *it << "\n" << endl;
//	}
//}
//// 改正
//void TestListIterator()
//{
//	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
//	list<int> l(array, array + sizeof(array) / sizeof(array[0]));
//	auto it = l.begin();
//	while (it != l.end())
//	{
//		//l.erase(it++);
//		it = l.erase(it);
//	}
//	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
//	{
//		cout << *it <<"\n"<< endl;
//	}
//}

//// size/clear/resize
//void TestString1()
//{	// 取出url中的域名
	//string url("http://www.cplusplus.com/reference/string/string/");
	//cout << url << endl;
	//size_t start = url.find("://");
	//if (start == string::npos)
	//{
	//	cout << "invalid url" << endl;
	//	return;
	//}
	//start += 3;
	//size_t finish = url.find('/', start);
	//string address = url.substr(start, finish - start);
	//cout << address << endl;
	//// 删除url的协议前缀
	//size_t pos = url.find("://");
	//url.erase(0, pos + 3);
	//cout << url << endl;
/////////////////////////////////////////////////
	////获取file后缀
	//string file{ "string.cpp" };
	//size_t pos = file.rfind('.');
	////string suffix(file.substr(pos, file.size() - pos));
	//string suffix;
	//suffix.append(file.begin() + pos, file.end());
	//cout << suffix << endl;
	//cout << address << endl;
	//// 删除url的协议前缀
	//pos = url.find("://");
	//url.erase(0, pos + 3);
	//cout << url << endl;
/////////////////////////////////////////
	//std::string str;
	//std::string str2 = "Witing ";
	//std::string str3 = "Please ";

	//str.append(str2);//追加str2
	//str.append(str3, 2, 3);//追加str3 2-3-4字符
	//str.append("Something", 4);//追加前4个字符
	//str.append("here: ");//追加""中字符
	//str.append(10u, '.');//追加10个'.'
	//str.append(str3.begin() + 2, str3.end());//追加str3第2个字符开始到结尾

	//cout << str.c_str();
//////////////////////////////////////
//string 的3种遍历方式 for+operator[]  迭代器  范围for
	//string s("hello world");
	//for (int i = 0; i < s.size(); i++)
	//{
	//	cout << s[i];
	//}
	//cout << "\n" << endl;

	////string的反向迭代
	//string::reverse_iterator it = s.rbegin();
	//while (it != s.rend())
	//{
	//	cout << *it;
	//	++it;
	//}
	//cout << "\n" << endl;
	//for (auto &e : s)
	//{
	//	cout << e;
	//}
//////////////////////////////////////////////////	
	/*string s1("hello Bit");
	const string s2("Hello Bit");
	cout << s1 << " " << s2 << endl;
	cout << s1[0] << " " << s2[0] << endl;

	s1[0] = 'H';
	cout << s1 << endl;*/
/////////////////////////////////////////////////
//	// 注意：string类对象支持直接用cin和cout进行输入和输出
//	string s("hello world!!!");
//	cout << s.size() << endl;
//	cout << s.length() << endl;
//	cout << s.capacity() << endl;
//	cout << s << endl;
//	cout << "= == == == == == == == == " << endl;
//	// 将s中的字符串清空，注意清空时只是将size清0，不改变底层空间的大小
//	s.clear();
//	cout << s.size() << endl;
//	cout << s.capacity() << endl;
//	cout << "= == == == == == == == == " << endl;
//	// 将s中有效字符个数增改变到10个，多出位置用'a'进行填充
//	// “aaaaaaaaaa”
//	s.resize(10, 'a');
//	cout << s.size() << endl;
//	cout << s.capacity() << endl;
//	cout << "= == == == == == == == == " << endl;
//	// 将s中有效字符个数增加到20个，多出位置用缺省值'\0'进行填充
//	// "aaaaaaaaaa\0\0\0\0\0"
//	s.resize(20);
//	cout << s.size() << endl;
//	cout << s.capacity() << endl;
//	cout << s << endl;
//	cout << "= == == == == == == == == " << endl;
//	// 将s中有效字符个数缩小到5个
//	s.resize(5);
//	cout << s.size() << endl;
//	cout << s.capacity() << endl;
//	cout << s << endl;
//	cout << "= == == == == == == == == " << endl;
//	// reserve不会会改变string中有效元素个数
//	s.reserve(50);
//	cout << s.size() << endl;
//	cout << s.capacity() << endl;
//	// 当reserve参数小于string的底层空间大小时，不会将空间缩小
//	s.reserve(40);
//	cout << s.size() << endl;
//	cout << s.capacity() << endl;
//}

//class SolutionA {
//public:
//	int firstUniqChar(string s) {
//		int count[256] = { 0 };
//		int size = s.size();
//		for (int i = 0; i <size; i++){
//			count[s[i]] += 1;
//		}
//
//		for (int i = 0; i < size; i++){
//			if (count[s[i]] == 1)
//				return i;
//		}
//		return -1;
//	}
//};


//class Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//private:
//	char _a = 'a';
//	int _b = 1;
//};

//class Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Base::Func1()" << endl;
//	}
//	virtual void Func2()
//	{
//		cout << "Base::Func2()" << endl;
//	}
//	void Func3()
//	{
//		cout << "Base::Func3()" << endl;
//	}
//private:
//	int _b = 1;
//};
//class Derive : public Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Derive::Func1()" << endl;
//	}
//private:
//	int _d = 2;
//};



class Date
{
public:
	Date() { cout << "Date()" << endl; }
	~Date(){ cout << "~Date()" << endl; }

	int _year;
	int _month;
	int _day;
};



struct ListNode
{
	int _data;
	weak_ptr < ListNode> _prev;
	weak_ptr < ListNode> _next;
	~ListNode(){ cout << "~ListNode()" << endl; }
};

int main()
{

	TestAVLTree();

	//TestBSTree();

	//TestSet();

	//Testmap();

	//shared_ptr<ListNode> node1(new ListNode);
	//shared_ptr<ListNode> node2(new ListNode);
	//cout << node1.use_count() << endl;
	//cout << node2.use_count() << endl;
	//node1->_next = node2;
	//node2->_prev = node1;
	//cout << node1.use_count() << endl;
	//cout << node2.use_count() << endl;

	//SharedPtr<int> sp1(new int(10));
	//SharedPtr<int> sp2(sp1);
	//*sp2 = 20;
	//cout << sp1.UseCount() << endl;
	//cout << sp2.UseCount() << endl;
	//SharedPtr<int> sp3(new int(10));
	//sp2 = sp3;
	//cout << sp1.UseCount() << endl;
	//cout << sp2.UseCount() << endl;
	//cout << sp3.UseCount() << endl;
	//sp1 = sp3;
	//cout << sp1.UseCount() << endl;
	//cout << sp2.UseCount() << endl;
	//cout << sp3.UseCount() << endl;


	//shared_ptr<Date> sp(new Date);
	//shared_ptr<Date> copy(sp);

	//cout << "ref count:" << sp.use_count() << endl;
	//cout << "ref count:" << copy.use_count() << endl;


	//auto_ptr<Date> ap(new Date);
	//auto_ptr<Date> copy(ap);
	//// auto_ptr的问题：当对象拷贝或者赋值后，前面的对象就悬空了
	//// C++98中设计的auto_ptr问题是非常明显的，所以实际中很多公司明确规定了不能使用auto_ptr
	//ap->_year = 2018;


	//Base b;
	//Derive d;
	//Base base;
	//cout << sizeof(base) << endl;
	//Test();
	//SolutionA A;
	//int i = A.firstUniqChar("loveleetcode");
	//cout << i;
	//cout << typeid(c).name() << endl;
	//TestString1();
	/*struct A
	{
		long a1;
		short a2;
		int a3;
		int *a4;
	};
	long a1;
	cout << sizeof(A) << endl;*/

	//char str[80];

	//sprintf(str, "Pi 的值 = %d", 123456);
	//puts(str);
	//TestListIterator();


	//Test1();
	////cout << sizeof(A1) << sizeof(A2) << sizeof(A3) << endl;
	//system("pause");
	//return 0;



	/*string num1 = ("1");
	string num2 = ("1");
	Solution2 A;
	num1 = A.addStrings(num1, num2);
	cout <<num1 << endl;*/


	//vector <int> arr;
	//arr.resize(5,100);
	//for (int  i = 0; i < arr.size(); i++)
	//{
	//	cout << ' ' << arr[i] << endl;
	//}
//	Solution A;
//	A.oddInOddEvenInEven(arr, arr.capacity());
//	A.PrintVector(arr);
//
	//Person p;

	//Date d;

	//A* p = NULL;
	//p->PrintA();
	//p->Show();
	/*cout << sizeof(fun1) << endl;
	cout << sizeof(fun2) << endl;
	cout<<sizeof(fun3) << endl;*/
	//int b = 20;
	//int a = 30;
	//int ** aa = new int*[10];
	//int *a = new int[10];
	//int *p = &b;
	//*p << endl;
	//cout << p << '\n' << *p << endl;

	system("pause");
	return 0;
}