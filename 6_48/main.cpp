/*
48. The most frequent element in a range
Write a function that, given a range, returns the most frequent element and the number of times it appears in the range.
If more than one element appears the same maximum number of times then the function should return all the elements.
For instance, for the range{ 1,1,3,5,8,13,3,5,8,8,5 }, it should return { 5, 3 } and {8, 3}.
*/

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>

template < typename Iterator >
auto most_frequent_element(Iterator begin, Iterator end)
{
	using Type = std::decay_t<decltype(*begin)>;

	std::map<Type, int> m;
	
	for (auto i = begin; i != end; ++i)
	{
		++m[*i];
	}

	std::vector<Type> ret;

	if (begin == end)
	{
		return std::make_pair(ret, 0);
	}

	auto itmax = m.cbegin();
	auto it = m.cbegin();
	for (; it != m.cend(); ++it)
	{
		if (itmax->second < it->second)
		{
			ret.clear();
			ret.push_back(it->first);
			itmax = it;
		}
		else if(itmax->second == it->second)
		{
			ret.push_back(it->first);
		}
	}
	
	return std::make_pair(ret, itmax->second);
}

int main()
{
	std::initializer_list<int> args{ 1,1,3,5,8,13,3,5,8,8,5 };

	auto [lst, c] = most_frequent_element(args.begin(), args.end());

	for (const auto& elem : lst)
	{
		printf("{%d,%d},", elem, c);
	}

	return 0;
}