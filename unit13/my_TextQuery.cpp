#include <cstddef>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <utility>
#include <initializer_list>
#include "my_strblob.h"

using namespace std;

StrBlob::StrBlob() :data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {  }
StrBlob::StrBlob(vector<string> *p) : data(p) {  }
inline StrBlob::StrBlob(StrBlob &s):data(make_shared<vector<string>>(*s.data)){}
inline StrBlob &StrBlob::operator= (StrBlob &rhs)
{
	data = make_shared<vector<string>>(*rhs.data);
	return *this;
}

inline void StrBlob::check(size_type i, const string &msg) const
{
	if (i >= data->size())
		throw out_of_range(msg);
}

inline string &StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

inline const string &StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}
inline string &StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

inline const string &StrBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}
inline void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

inline shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;
}

inline string &StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];		//(*p)是对象所指向的vector
}

inline string & StrBlobPtr::deref(int off) const
{
	auto p = check(curr + off, "dereference past end");
	return (*p)[curr];
}

//前缀递增：返回递增后的对象的引用
inline StrBlobPtr &StrBlobPtr::incr()
{
	//如果curr已经指向容器的末尾位置，就不能递增它
	check(curr, "increment past end of StrBlobPtr");
	++curr;//推进当前位置
	return *this;
}

//前缀递减：返回递减后的对象的引用
inline StrBlobPtr &StrBlobPtr::dec()
{
	//如果curr已经为0，递减它就会产生一个非法的下标
	--curr;		//递减当前位置
	check(-1, "decrement past begin of StrBlobPtr");
	return *this;
}

//StrBlob的begin和end成员的定义
//inline StrBlobPtr StrBlob::begin()
//{
//	return StrBlobPtr(*this);
//}

inline StrBlobPtr StrBlob::begin() const
{
	return StrBlobPtr(*this);
}

//inline StrBlobPtr StrBlob::end()
//{
//	auto ret = StrBlobPtr(*this, data->size());
//	return ret;
//}

inline StrBlobPtr StrBlob::end() const
{
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

//StrBlobPtr的比较操作
inline bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();

	//若底层的vector是同一个
	if (l == r)
		return (!r || lhs.curr == rhs.curr);
	else
		return false;
}
inline bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	return !eq(lhs, rhs);
}