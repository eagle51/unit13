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
	return (*p)[curr];		//(*p)�Ƕ�����ָ���vector
}

inline string & StrBlobPtr::deref(int off) const
{
	auto p = check(curr + off, "dereference past end");
	return (*p)[curr];
}

//ǰ׺���������ص�����Ķ��������
inline StrBlobPtr &StrBlobPtr::incr()
{
	//���curr�Ѿ�ָ��������ĩβλ�ã��Ͳ��ܵ�����
	check(curr, "increment past end of StrBlobPtr");
	++curr;//�ƽ���ǰλ��
	return *this;
}

//ǰ׺�ݼ������صݼ���Ķ��������
inline StrBlobPtr &StrBlobPtr::dec()
{
	//���curr�Ѿ�Ϊ0���ݼ����ͻ����һ���Ƿ����±�
	--curr;		//�ݼ���ǰλ��
	check(-1, "decrement past begin of StrBlobPtr");
	return *this;
}

//StrBlob��begin��end��Ա�Ķ���
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

//StrBlobPtr�ıȽϲ���
inline bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();

	//���ײ��vector��ͬһ��
	if (l == r)
		return (!r || lhs.curr == rhs.curr);
	else
		return false;
}
inline bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	return !eq(lhs, rhs);
}