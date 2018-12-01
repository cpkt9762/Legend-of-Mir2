#include <Windows.h>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <Detours.h>
class A
{
public:
	friend class B;                         //这是友元类的声明
private:
	int data;
};

class B            //友元类定义，为了访问类A中的成员
{
public:
	void set_show(int x, A &a)
	{ 
		a.data = x;

		printf("a = %d\n", a.data);
	}
};
int main()
{
	class A a;
	class B b;

	b.set_show(1, a);

	getchar();
	return 0;
}