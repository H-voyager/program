#pragma once
#include <set>

using std::set;
using std::cout;
using std::endl;

void TestSet()
{
	// 用数组array中的元素构造set
	int array[] = { 0,1,2,9,4,5,6,7,8,3,0,1,2,3,4,5,6,7,8,9 };
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