#include <iostream>
using namespace std;
class numbered {
public:
	numbered(numbered &){
		mysn = seq++;
	}
	numbered() {
		mysn = seq++;
	}
	int mysn;
private:
	static int seq;		//声明静态成员
};
int numbered::seq = 0;	//定义并初始化静态成员（静态成员一般必须在类内声明，类外定义和初始化）
void f(numbered s)
{
	cout << s.mysn << endl;
}

void f1(const numbered &s)
{
	cout << s.mysn << endl;
}

int main()
{
	numbered a, b = a, c = b;
	f(a);f(b);f(c);
	f1(a);f1(b);f1(c);
	system("pause");
	return 0;
}
//2016年6月11日16:18:58
//实验室