#include <iostream>
#include <functional>

class A
{
	std::function<void()> callback_;

public:
	A(const std::function<void()>& f) :callback_(f)
	{}

	void notify(void)
	{
		callback_();
	}
};

class Foo
{
public:
	void operator()(void)
	{
		std::cout << __FUNCTION__ << std::endl;
	}
};

int main()
{
	Foo foo;
	A aa(foo);
	aa.notify();

	return 0;
}