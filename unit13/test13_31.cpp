#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "myHasPtr.h"
using namespace std;
int main(int argc,char **argv)
{
	vector<HasPtr> vh;
	int n = atoi(argv[1]);
	cout << "n = " << n << endl;
	for (int i = 0;i < n;i++)
		vh.push_back(to_string(n - i));
	for (auto p : vh)
		cout << *p << " ";
	cout << endl;
	sort(vh.begin(), vh.end());
	for (auto p : vh)
		cout << *p << " ";
	cout << endl;
	//system("pause");
	return 0;
}
/*
在vc++2015的编译器的STL实现中，当元素小于等于16时，sort使用的插入排序算法，而且未使用swap交换元素，而是内存区域的整片移动
因此，当我们将命令行参数设定不超过16时，会发现swap并未被调用。而当命令行参数大于等于17时，就会发现sort调用了swap。因为此时sort
采用的是快速排序算法，使用了swap交换元素。但是，交换元素的次数可能比预期的快速排序算法的交换元素次数要好得多。
原因是，在快速排序算法递归排序的过程中，如果子序列长度小于等于16， 又会转到插入排序算法，而不会继续递归至子序列长度变为1。
2016年6月14日15:37:44
实验室
*/