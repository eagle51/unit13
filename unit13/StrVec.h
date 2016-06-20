#ifndef STRVEC_H
#define STRVEC_H
#include <string>
#include <memory>
#include <utility>
class StrVec {
public:
	StrVec() ://allocator成员进行默认初始化
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(std::initializer_list<std::string> il);
	StrVec(const StrVec &);			//拷贝构造函数
	StrVec &operator=(const StrVec &);//拷贝赋值运算符
	~StrVec();						//析构函数
	void push_back(const std::string &);	//拷贝元素
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

	void reserve(size_t n) { if (n > capacity())reallocate(); }

	void resize(size_t n);
	void resize(size_t n, const std::string &s);

private:
	static std::allocator<std::string> alloc;	//分配元素
	//被添加元素的函数所使用
	void chk_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}

	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();
	std::string *elements;
	std::string *first_free;
	std::string *cap;

};

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
	//分配空间保存给定范围中的元素
	auto data = alloc.allocate(e - b);
	return{ data,uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
	//不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
	if (elements) {
		//逆序销毁就元素
		for (auto p = first_free;p != elements;/*空*/)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

/*for_each lambda版本的free()
void StrVec::free()
{
	for_each(elements,first_free,[](std::string &s){alloc.destroy(&s);});
}
*/

StrVec::StrVec(const StrVec &s)
{
	//调用alloc_n_copy分配空间以容纳与s中一样多的元素
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator =(const StrVec &rhs)
{
	//调用alloc_n_copy分配内存，大小与rhs中元素占用空间一样多
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = data.second;
	return *this;
}

void StrVec::reallocate()
{
	//我们将分配当前大小两倍的内存空间
	auto newcapacity = size() ? 2 * size() : 1;
	//分配新内存
	auto newdata = alloc.allocate(newcapacity);
	//将数据从就内存移动到新内存
	auto dest = newdata;	//指向新数组下一个空闲位置位置
	auto elem = elements;	//指向旧数组中下一个元素
	for (size_t i = 0;i != size();++i)
		alloc.construct(dest++, atd::move(*elem++));
	free();		//一旦移动完元素就释放旧内存空间
	//更新我们的数据结构，执行新元素
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
inline void StrVec::resize(size_t n)
{
	if (n > size()) {
		while (size() < n)
			push_back("");
	}
	else if
		(n < size()) {
		while (size() > n)
			alloc.destroy(--first_free);
	}
}

inline void StrVec::resize(size_t n, const std::string &s)
{
	if (n > size()) {
		while (size() < n)
			push_back(s);
	}
}

inline StrVec::StrVec(std::initializer_list<std::string> il)
{
	//调用alloc_n_copy分配与列表il中元素数目一样多的空间
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
#endif
//2016年6月19日23:00:39
//实验室
//2016年6月20日12:44:10修改