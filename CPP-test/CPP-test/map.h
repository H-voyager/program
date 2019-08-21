#pragma once
#include <iostream>
#include <string>
#include <map>
#include <set>

using std::map;
using std::string;

void Testmap()
{
	map<string, string> m;
	
	//向map中插入元素的方式:
	//将键值对<test, 测试>插入,直接用pair构造键值对

	m.insert(std::pair<string, string>("test", "测试"));

	//将键值对<"test", "测试">插入到map中,用make_pair函数来构造键值对
	m.insert(std::make_pair("test0", "测试0"));

	//用opetator[]向map中插入元素
	//用<key, T()>构造一个键值对，然后调用insert()函数将该键值对插入到map中
	//如果key已经存在，插入失败，insert函数返回该key所在位置的迭代器
	//如果key不存在，插入成功，insert函数返回新插入元素所在位置的迭代器
	//operator[]函数最后将insert返回值键值对中的value返回
	m["test1"] = "测试1";

	//key不存在时抛异常
	//m.at("test2") = "测试2";

	std::cout << m.size() << std::endl;

	//用迭代器遍历map中的元素,得到一个按照key排序的序列
	for (auto& e : m)
		std::cout << e.first << "-->" << e.second << std::endl;
	std::cout << std::endl;

	//map的键值对key一定是唯一的,如果存在插入失败
	auto ret = m.insert(std::make_pair("test", "测试one"));
	if (ret.second)
	{
		std::cout << "<test, 测试one>不存在,插入成功" << std::endl;
	}
	else
	{
		std::cout << "键值test已经存在,插入失败" << std::endl;
	}

	//删除key为test1的元素
	m.erase("test1");
	if (m.count("test1") == 1)
	{
		std::cout << "test1还存在" << std::endl;
	}
	else
	{
		std::cout << "test1已删除" << std::endl;
	}
}



void TestSet1()
{
	// 用数组array中的元素构造set
	int array[] = { 0, 1, 2, 9, 4, 5, 6, 7, 8, 3, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	multiset<int> s(array, array + sizeof(array));
	cout << s.size() << endl;
	// 正向打印set中的元素，从打印结果中可以看出：set可去重
	for (auto& e : s)
		cout << e << " ";
	cout << endl;
	// 使用迭代器逆向打印set中的元素
	for (auto it = s.rbegin(); it != s.rend(); ++it)
		cout << *it << " ";
	cout << endl;
	// set中值为3的元素出现了几次
	cout << s.count(3) << endl;
}