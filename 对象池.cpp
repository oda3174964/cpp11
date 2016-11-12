#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <functional>

using namespace std;

class NonCopyable
{
public:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
	NonCopyable() = default;
};

const int MaxObjectNum = 10;

template<typename T>
class ObjectPool : NonCopyable
{
	template<typename... Args>
	using Constructor = std::function<std::shared_ptr<T>(Args...)>;

public:
	template<typename... Args>
	void Init(size_t num, Args&&... args)
	{
		if (num <= 0 || num > MaxObjectNum)
			throw std::logic_error("object num out of range.");

		auto constructName = typeid(Constructor<Args...>).name(); //不区分引用
		for (size_t i = 0; i < num; ++i)
		{
			m_object_map.emplace(constructName, shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName](T* p) //删除器中不直接删除对象，而是回收到对象池中，已供下次使用
			{
				m_object_map.emplace(std::move(constructName), std::shared_ptr<T>(p));
			}));
		}
	}

	//从对象池中获取一个对象
	template<typename... Args>
	std::shared_ptr<T> Get()
	{
		string constructName = typeid(Constructor<Args...>).name();

		auto range = m_object_map.equal_range(constructName);

		for (auto it = range.first; it != range.second; ++it)
		{
			auto ptr = it->second;
			m_object_map.erase(it);
			return ptr;
		}
		return nullptr;
	}

private:
	multimap<string, std::shared_ptr<T>> m_object_map;
};

struct BigObject
{
	BigObject() {}
	BigObject(int a) {}
	BigObject(const int& a, const int& b) {}

	void Print(const string& str)
	{
		cout << str << endl;
	}
};

void Print(shared_ptr<BigObject> p, const string& str)
{
	if (p != nullptr)
	{
		p->Print(str);
	}
}

void TestObjectPool()
{
	ObjectPool<BigObject> pool;
	pool.Init(2);

	{
		auto p = pool.Get();
		Print(p, "p");
		auto p2 = pool.Get();
		Print(p2, "p2");
	}//出了作用域，对象池返回出来的对象又会自动回收
	auto p = pool.Get();
	auto p2 = pool.Get();
	Print(p, "p");
	Print(p2, "p2");

	//对象池支持重载构造函数
	pool.Init(2, 1);
	auto p4 = pool.Get<int>();
	Print(p4, "p4");
	pool.Init(2, 1, 2);
	auto p5 = pool.Get<int, int>();
	Print(p5, "p5");
}

int main()
{
	TestObjectPool();
	return 0;
}