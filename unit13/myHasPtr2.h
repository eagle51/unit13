#ifndef MYHASPTR2_H
#define MYHASPTR2_H
#include <string>
using namespace std;
class HasPtr {
public:
	HasPtr(const string &s = string()) :ps(new string(s)), i(0), use(new std::size_t(1)) {}
	HasPtr(const HasPtr &hp);
	HasPtr &operator= (const HasPtr &rhs);
	HasPtr &operator= (const string &s);
	string &operator* () {return *ps;}
	~HasPtr();
private:
	string *ps;
	int i;
	std::size_t *use;
};
HasPtr::~HasPtr()
{
	if (--*use == 0) {
		delete ps;
		delete use;
	}
}
HasPtr::HasPtr(const HasPtr &hp)
{
	++*hp.use;
	ps = hp.ps;
	i = hp.i;
	use = hp.use;
}

HasPtr &HasPtr::operator =(const HasPtr &rhs)
{
	//const对象的成员是不可修改的,然而const对象通过指针维护的对象却是可以修改的.见我的学习心得C++编程中的const关键字常见用法总结20160612
	++*rhs.use;		//此处rhs是const类型的变量，竟然可以通过指针的方式修改rhs.use
	if (--*use == 0) {
		delete ps;
		delete use;
	}
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;
	return *this;
}

HasPtr &HasPtr::operator= (const string &rhs)
{
	*ps = rhs;
	return *this;
}
#endif
