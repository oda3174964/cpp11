#include <iostream>
#include <functional>

void call_when_even(int x, const const std::function<void(int)>& f)
{
	if (!(x & 1))
	{
		f(x);
	}
}

void output(int x)
{
	std::cout << x << " ";
}

void output_add_2(int x)
{
	std::cout << x + 2 << " ";
}

int main()
{
	{
		auto fr = std::bind(output, std::placeholders::_1);
		for (int i = 0; i < 10; ++i)
		{
			call_when_even(i, fr);
		}
		std::cout << std::endl;
	}

	{
		auto fr = std::bind(output_add_2, std::placeholders::_1);
		for (int i = 0; i < 10; i++)
		{
			call_when_even(i, fr);
		}
		std::cout << std::endl;
	}
	return 0;
}