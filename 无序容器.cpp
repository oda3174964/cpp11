#include <unordered_map>
#include <vector>
#include <bitset>
#include <string>
#include <utility>

struct Key
{
	std::string first;
	std::string second;
};

struct KeyHash
{
	std::size_t operator()(const Key& k)const
	{
		return std::hash<std::string>()(k.first) ^ (std::hash<std::string>()(k.second) << 1);
	}
};

struct KeyEqual
{
	std::size_t operator()(const Key& lhs, const Key& rhs)const
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
};

int main()
{
	std::unordered_map<std::string, std::string> ml;

	std::unordered_map<int, std::string> m2 =
	{
		{ 1, "foo" },
		{ 3, "bar" },
		{ 2, "baz" },
	};

	std::unordered_map<int, std::string> m3 = m2;

	std::unordered_map<int, std::string> m4 = std::move(m2);

	std::vector<std::pair<std::bitset<8>, int>> v = { {0x12, 1}, {0x01, -1} };

	std::unordered_map<std::bitset<8>, double> m5(v.begin(), v.end());

	std::unordered_map<Key, std::string, KeyHash, KeyEqual> m6 = {
		{ {"Jhon", "Doe"}, "example"},
		{ {"Mary", "Sue"}, "another"},
	};
	
	return 0;
}