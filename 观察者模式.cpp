#include <iostream>

class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;//禁用复制构造
	//禁用赋值构造
	NonCopyable& operator=(const NonCopyable&) = delete;
};

#include <string>
#include <functional>
#include <map>
using namespace std;

template<typename Func>
class Events : NonCopyable
{
public:
	Events(){}

	~Events(){}

	int Connect(Func&& f)
	{
		return Assign(f);
	}

	int Connect(const Func& f)
	{
		return Assign(f);
	}

	void Disconnect(int key)
	{
		m_connections.erase(key);
	}

	//通知所有观察者
	template<typename... Args>
	void Notify(Args&&... args)
	{
		for (auto& it : m_connections)
		{
			it.second(std::forward<Args>(args)...);
		}
	}

private:
	template<typename F>
	int Assign(F&& f)
	{
		int k = m_observerId++;
		m_connections.emplace(k, std::forward<F>(f));
		return k;
	}

	int m_observerId = 0;
	std::map<int, Func> m_connections;
};

struct stA
{
	int a, b;
	void print(int a, int b)
	{
		cout << a << ", " << b << endl;
	}
};

void print(int a, int b)
{
	cout << a << ", " << b << endl;
}

int main()
{
	Events<std::function<void(int, int)>> myevent;

	auto key = myevent.Connect(print);
	stA t;
	auto lambdakey = myevent.Connect([&t](int a, int b) { t.a = a; t.b = b; }); //lambda注册

	//function注册
	std::function<void(int, int)> f = std::bind(&stA::print, &t, std::placeholders::_1, std::placeholders::_2);
	myevent.Connect(f);

	int a = 1, b = 2;
	myevent.Notify(a, b);
	myevent.Disconnect(key);

	return 0;
}