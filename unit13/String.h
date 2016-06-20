#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <algorithm>
#include <cstddef>
#include <iostream>

#ifdef INITIALIZER_LIST
#include <initializer_list>
#endif

#include <iostream>
#include <memory>

class String {
	friend String operator+(const String &, const String &);
	friend String add(const String &, const String &);
	friend std::ostream &operator<<(std::ostream &, const String &);
	friend std::ostream &print(std::ostream &, const String &);

public:
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
	String() = default;
#else
	String():sz(0),p(nullptr){}
#endif

	String(const char *cp) : 
		sz(std::strlen(cp)),p(a.allocate(sz))
	{
		std::uninitialized_copy(cp, cp + sz, p);
	}
	String(const String &s):sz(s.sz),p(a.allocate(s.sz))
	{
		std::uninitialized_copy(s.p, s.p + sz, p);
	}

#ifdef NOEXCEPT
	String(String &&s)noexcept:sz(s.size()),p(s.p)
#else
	String(String &&s) throw():sz(s.size()),p(s.p)
#endif
	{
		s.p = 0;s.sz = 0;
	}

	String(size_t n,char c):sz(n),p(a.allocate(n))
	{
		std::uninitialized_fill_n(p, sz, c);
	}

	String &operator=(const String &);

#ifdef NOEXCEPT
	String &operator=(String &&)noexcept;
#else
	String &operator=(String &&) throw();
#endif
#ifdef NOEXCEPT
	~String()noexcept { if (p) a.deallocate(p, sz); }
#else
	~String() throw() { if (p) a.deallocate(p, sz); }
#endif

	String &operator=(const char*);
	String &operator=(char);
#ifdef INITIALIZER_LIST
	String &
		operator=(std::initializer_list<char>);
#endif

	const char *begin() { return p; }
	const char *begin() const{ return p; }
	const char *end() { return (p + sz); }
	const char *end() const { return(p + sz); }

	size_t size() const { return sz; }
	void swap(String &s) 
	{
		auto tmp = p;p = s.p;s.p = tmp; 
		auto cnt = sz;sz = s.sz;;s.sz = cnt;
	}
private:
#ifdef IN_CLASS_INTS
	std::size_t sz = 0;
	char *p = nullptr;
#else
	std::size_t sz;
	char *p;
#endif
	static std::allocator<char> a;
};

String make_plural(size_t ctr, const String &, const String &);
inline void swap(String &s1, String &s2)
{
	s1.swap(s2);
}
#endif // !STRING_H