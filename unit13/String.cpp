#include <cstring>
using std::strlen;

#include <algorithm>
using std::copy;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::ostream;

#include <utility>
using std::swap;

#ifdef IN_CLASS_INITS
#include <initializer_list>
using std::initializer_list;
#endif

#include <memory>
using std::uninitialized_copy;

#include "String.h"

std::allocator<char> String::a;

String &String::operator=(const String &rhs)
{
	auto newp = a.allocate(rhs.sz);
	uninitialized_copy(rhs.p, rhs.p + rhs.sz, newp);

	if (p)
		a.deallocate(p, sz);
	p = newp;
	sz = rhs.sz;

	return *this;
}

#ifdef NOEXCEPT
String & String::operator=(String &&rhs) noexcept
#else
String & String::operator=(String &&rhs) throw()	//移动赋值运算符的定义
#endif
{
	if (this != rhs) {
		if (p)
			a.deallocate(p, sz);
		p = rhs.p;
		sz = rhs.sz;
		rhs.p = 0;
		rhs.sz = 0;
	}
	return *this;
}

String &String::operator=(const char *cp)
{
	if (p) 
		a.deallocate(p, sz);
	p = a.allocate(sz = strlen(cp));
	uninitialized_copy(cp, cp + sz, p);
	return *this;
}
String &String::operator =(char c)
{
	if (p)
		a.deallocate(p, sz);
	p = a.allocate(sz = 1);
	*p = c;
	return *this;
}

#ifdef INITIALIZER_LIST
String &String::operator =(initializer_list<char> il)
{
	if (p)
		a.deallocate(p, sz);
	p = a.allocate(sz = il.size());
	uninitialized_copy(il.begin(), il.end(), p);
	return *this;
}

#endif
ostream &print(ostream &os, const String &s)
{
	auto p = s.begin();
	while (p != s.end())
		os << *p++;
	return os;
}

String add(const String &lhs, const String &rhs)
{
	String ret;
	ret.sz = rhs.size() + lhs.size();
	ret.p = String::a.allocate(ret.sz);
	uninitialized_copy(lhs.begin(), lhs.end(), ret.p);
	uninitialized_copy(rhs.begin(), rhs.end(), ret.p + lhs.sz);
	return ret;
}

String make_plural(size_t ctr, const String &word, const String &ending)
{
	return (ctr != 1) ? add(word, ending) : word;
}

ostream &operator<<(ostream &os, const String &s)
{
	return print(os, s);
}

String operator+(const String &lhs, const String &rhs)
{
	return add(lhs,rhs);
}