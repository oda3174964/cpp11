#include <iostream>
using namespace std;

void print()
{
	cout << "empty" << endl;
}

template<class T, class ...Args>
void print(T head, Args... rest)
{
	cout << "parameter " << head << endl;
	print(rest...);
}

int main()
{
	print(1, 2, 3, 4);
	system("pause");
	return 0;
}