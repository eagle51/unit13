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
	//const����ĳ�Ա�ǲ����޸ĵ�,Ȼ��const����ͨ��ָ��ά���Ķ���ȴ�ǿ����޸ĵ�.���ҵ�ѧϰ�ĵ�C++����е�const�ؼ��ֳ����÷��ܽ�20160612
	++*rhs.use;		//�˴�rhs��const���͵ı�������Ȼ����ͨ��ָ��ķ�ʽ�޸�rhs.use
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
