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
	static int seq;		//������̬��Ա
};
int numbered::seq = 0;	//���岢��ʼ����̬��Ա����̬��Աһ��������������������ⶨ��ͳ�ʼ����
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
//2016��6��11��16:18:58
//ʵ����