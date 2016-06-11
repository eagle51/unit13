#include <string>
#include <iostream>
class Employee {
public:
	Employee() { myid = id++; }
	Employee(const std::string &s) : name(s) { myid = id++; }
	const std::string &get_name() { return name; }
	int get_myid() { return myid; }

	Employee(Employee &e) { name = e.get_name();myid = id++; }
	Employee &operator=(Employee &rhs) { name = rhs.get_name();return *this; }
private:
	std::string name;
	int myid;
	static int id;
};

int Employee::id = 0;

void f(Employee &s)
{
	std::cout << s.get_name() << ":" << s.get_myid() << std::endl;
}
int main()
{
	Employee a("赵"), b = a, c("钱");
	f(c);
	c = b;
	f(a);f(b);f(c);
	system("pause");
	return 0;
}
//拷贝赋值运算符定义了赋值的时候对象执行的操作，合成拷贝赋值运算符则拷贝所有非静态数据成员
//2016年6月11日20:19:00
//实验室