#ifndef MYHASPTR_H
#define MYHASPTR_H
#include <string>
class HasPtr {
public:
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)),i(0) {}
	HasPtr(const HasPtr &hp);
	HasPtr &HasPtr::operator =(const HasPtr &);
	HasPtr &HasPtr::operator=(const std::string &);
	std::string &HasPtr::operator*();
	~HasPtr() { delete ps; }	//�˴������delete ps��Ϊps��Ĭ�ϳ�ʼ��ʱ��̬�����ڴ棬��ps������ָ������
private:
	std::string *ps;
	int i;
};

HasPtr::HasPtr(const HasPtr &hp)
{
	ps = new std::string(*(hp.ps));
	i = hp.i;
}

HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
	auto newp = new std::string(*rhs.ps);	//�ȱ���һ�ݿ�����Ϊ�˴����Ը�ֵ�����
	delete ps;
	ps = newp;
	i = rhs.i;
	return *this;
}
HasPtr &HasPtr::operator=(const std::string &rhs)
{
	*ps = rhs;
	return *this;
}
std::string &HasPtr::operator*()
{
	return *ps;
}

#endif