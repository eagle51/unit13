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
//����Ķ����ʵ�ַֿ���ʱ�򣨶����ͷ�ļ���ʵ�ַ�cpp�ļ���������һֱ��ʶ��neq�����������ʾδ�����ʶ������
//�����Ҽ�ѡ��ת������ȴ����ת������ʵ�ֺͶ����һ��ͷ�ļ���ȴû������
//2016��6��12��15:19:08 ʵ����