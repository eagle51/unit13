#include <iostream>
#include "myHasPtr2.h"
using namespace std;
int main()
{
	HasPtr h("hi mom!");
	HasPtr h2 = h;
	h = "hi dad!";
	cout << "h: " << *h << endl;
	cout << "h2: " << *h2 << endl;
	system("pause");
	return 0;
}
//2016��6��12��20:51:37
//ʵ����