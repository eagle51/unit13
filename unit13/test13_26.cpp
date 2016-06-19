#include<iostream>
#include "my_strblob.h"
using namespace std;
int main()
{
	StrBlob b1;
	{
		StrBlob b2 = { "a","an","the" };
		b1 = b2;
		b2.push_back("about");
		cout << b2.size() << endl;
	}
	cout << b1.size() << endl;
	cout << b1.front() << " " << b1.back() << endl;

	const StrBlob b3 = b1;
	cout << b3.front() << " " << b3.back() << endl;

	for (auto it = b1.begin();neq(it, b1.end());it.incr())
		cout << it.deref() << endl;
	system("pause");
	return 0;
}
//将类的定义和实现分开的时候（定义放头文件，实现放cpp文件）主程序一直不识别neq这个函数（提示未定义标识符），
//但是右键选择转到定义却可以转到。将实现和定义放一个头文件里却没有问题
//2016年6月12日15:19:08 实验室