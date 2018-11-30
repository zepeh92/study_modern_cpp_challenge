/*
54. Pairwise algorithm
Write a general-purpose function that, given a range, returns a new range with pairs of consecutive elements from the input range. 
Should the input range have an odd number of elements, the last one must be ignored. 
For example, if the input range was {1, 1, 3, 5, 8, 13, 21}, the result must be { {1, 1}, {3, 5}, {8, 13}}.
*/

#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

template < typename Container, typename PairType = pair<typename Container::value_type, typename Container::value_type> >
vector<PairType>
pairwise(const Container& container)
{
	vector<PairType> ret;
	const auto len = distance(container.begin(), container.end()) / 2;
	ret.reserve(len);
	const auto it = container.begin();
	for (auto i = 0; i != len; ++i)
	{
		auto a = *it++;
		auto b = *it++;
		ret.push_back({move(a), move(b)});
	}
	return ret;
}

int main()
{
	std::vector<int> rng{ 1,1,3,5,8,13,21 };

	for (const auto& pair : pairwise(rng))
	{
		printf("{%d:%d}, ", pair.first, pair.second);
	}

	return 0;
}