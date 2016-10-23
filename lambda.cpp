#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using std::vector;
using namespace std;

class CountEven
{
	int& count_;

public:
	CountEven(int& count) : count_(count)
	{}

	void operator()(int val)
	{
		if (!(val & 1))
		{
			++count_;
		}
	}
};

int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5, 6 };

	int even_count = 0;
	for_each(v.begin(), v.end(), CountEven(even_count));
	std::cout << "The number of even is " << even_count << std::endl;
	return 0;
}