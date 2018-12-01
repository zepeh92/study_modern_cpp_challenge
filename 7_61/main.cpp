/*
61.Parallel transform algorithm

Write a general-purpose algorithm that applies a given unary function to transform the elements of a range in parallel. 
The unary operation used to transform the range must not invalidate range iterators or modify the elements of the range. 
The level of parallelism, that is, the number of execution threads and the way it is achieved, is an implementation detail.
*/

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <future>

using namespace std;

template < typename Container, typename Inserter, typename Iterator, typename Func >
auto pararrel_transform(Iterator begin, Iterator end, Inserter inserter, Func func, size_t leaf = 1024) {

	const size_t dist = static_cast<size_t>(std::distance(begin, end));
	if (dist < leaf) {
		Container ret;
		std::transform(begin, end, inserter(ret), [&](const auto& v) {
			return func(v);
		});
		return ret;
	}

	auto f = async(launch::async, [&] {
		Container ret;
		const auto mid = begin + (dist / 2);
		const auto a = pararrel_transform<Container>(begin, mid, inserter, func, leaf);
		const auto b = pararrel_transform<Container>(mid, end, inserter, func, leaf);
		merge(a.begin(), a.end(), b.begin(), b.end(), inserter(ret));
		return ret;
	});

	return f.get();
}


int main() {
	
	vector<int> vals{ 1,2,3,4,5,6,7,8,9,10 };

	map<string, int> m = pararrel_transform<map<string, int>>(
		vals.begin(), vals.end(), 
		[](auto& c) { return inserter(c, c.begin()); }, 
		[](auto v) { return std::make_pair('[' + to_string(v) + ']', v); },
		2);

	for (auto&& [str, v] : m) {
		printf("key: %s, val:%d\n", str.c_str(), v);
	}

	return 0;
}