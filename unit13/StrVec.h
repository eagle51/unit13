#ifndef STRVEC_H
#define STRVEC_H
#include <string>
#include <memory>
#include <utility>
class StrVec {
public:
	StrVec() ://allocator��Ա����Ĭ�ϳ�ʼ��
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(std::initializer_list<std::string> il);
	StrVec(const StrVec &);			//�������캯��
	StrVec &operator=(const StrVec &);//������ֵ�����
	~StrVec();						//��������
	void push_back(const std::string &);	//����Ԫ��
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

	void reserve(size_t n) { if (n > capacity())reallocate(); }

	void resize(size_t n);
	void resize(size_t n, const std::string &s);

private:
	static std::allocator<std::string> alloc;	//����Ԫ��
	//�����Ԫ�صĺ�����ʹ��
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
	//����ռ䱣�������Χ�е�Ԫ��
	auto data = alloc.allocate(e - b);
	return{ data,uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
	//���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0������ʲôҲ����
	if (elements) {
		//�������پ�Ԫ��
		for (auto p = first_free;p != elements;/*��*/)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

/*for_each lambda�汾��free()
void StrVec::free()
{
	for_each(elements,first_free,[](std::string &s){alloc.destroy(&s);});
}
*/

StrVec::StrVec(const StrVec &s)
{
	//����alloc_n_copy����ռ���������s��һ�����Ԫ��
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator =(const StrVec &rhs)
{
	//����alloc_n_copy�����ڴ棬��С��rhs��Ԫ��ռ�ÿռ�һ����
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = data.second;
	return *this;
}

void StrVec::reallocate()
{
	//���ǽ����䵱ǰ��С�������ڴ�ռ�
	auto newcapacity = size() ? 2 * size() : 1;
	//�������ڴ�
	auto newdata = alloc.allocate(newcapacity);
	//�����ݴӾ��ڴ��ƶ������ڴ�
	auto dest = newdata;	//ָ����������һ������λ��λ��
	auto elem = elements;	//ָ�����������һ��Ԫ��
	for (size_t i = 0;i != size();++i)
		alloc.construct(dest++, atd::move(*elem++));
	free();		//һ���ƶ���Ԫ�ؾ��ͷž��ڴ�ռ�
	//�������ǵ����ݽṹ��ִ����Ԫ��
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
	//����alloc_n_copy�������б�il��Ԫ����Ŀһ����Ŀռ�
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
#endif
//2016��6��19��23:00:39
//ʵ����
//2016��6��20��12:44:10�޸�