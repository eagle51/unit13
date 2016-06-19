#ifndef MYHASPTR_H
#define MYHASPTR_H
#include <string>
#include <iostream>
class HasPtr {
	friend void swap(HasPtr &lhs, HasPtr &rhs);
public:
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)),i(0) {}
	HasPtr(const HasPtr &hp);
	HasPtr &operator =(const HasPtr &);
	HasPtr &operator=(const std::string &);
	std::string &operator*();
	bool operator<(const HasPtr &) const;
	~HasPtr() { delete ps; }	//此处需添加delete ps因为ps的默认初始化时动态分配内存，而ps是内置指针类型
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
	auto newp = new std::string(*rhs.ps);	//先保存一份拷贝是为了处理自赋值的情况
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

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
	using std::swap;
	using std::cout;
	using std::endl;
	cout << "交换 " << *lhs.ps << "和" << *rhs.ps << endl;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}
bool HasPtr::operator<(const HasPtr &rhs) const
{
	return *ps < *rhs.ps;
}
#endif