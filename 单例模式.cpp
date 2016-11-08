#include <iostream>
#include <string>

template <typename T>
class Singleton
{
public:
	template<typename... Args>
	static T* Instance(Args&&... args)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new T(std::forward<Args>(args)...);
		}
		return m_pInstance;
	}

	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
			throw std::logic_error("the instance is not init, please initialize the instance first");
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

private:
	Singleton(void);
	virtual ~Singleton(void);
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

private:
	static T* m_pInstance;
};

template <class T>
T* Singleton<T>::m_pInstance = nullptr;

using namespace std;

struct A
{
	A(const string&)
	{
		cout << "lvalue" << endl;
	}
	A(string&& x)
	{
		cout << "rvalue" << endl;
	}
};

struct B
{
	B(const string&)
	{
		cout << "lvalue" << endl;
	}
	B(string&& x)
	{
		cout << "rvalue" << endl;
	}
};

struct C
{
	C(int x, double y)
	{}

	void Fun()
	{
		cout << "test" << endl;
	}
};

int main()
{
	string str = "bb";
	Singleton<A>::Instance(str);
	Singleton<B>::Instance(std::move(str));
	Singleton<C>::Instance(1, 3.14);
	Singleton<C>::GetInstance()->Fun();

	Singleton<A>::DestroyInstance();
	Singleton<B>::DestroyInstance();
	Singleton<C>::DestroyInstance();
	return 0;
}