#include <iostream>
#include "myHasPtr.h"
using std::cout;
using std::endl;
int main()
{
	HasPtr h("hi mom!");
	HasPtr h2(h);
	HasPtr h3 = h;
	h2 = "hi dad!";
	h3 = "hi son!";

	//swap(h2, h3);
	cout << "h: " << *h << endl;
	cout << "h2: " << *h2 << endl;
	cout << "h3: " << *h3 << endl;
	system("pause");
	return 0;
}
//2016年6月12日13:38:04
//实验室