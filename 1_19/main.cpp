/*
�����̳ʿ� � ���� ������ �߰��ϱ� push_back(T&& value) �޼ҵ带 ���� 
�����̳��� ���� ���ϴ� ���� ��Ҹ� �߰��� �� �ִ� General-purpose �Լ��� �ۼ��϶�.
*/

#include <iostream>
#include <vector>
#include <list>

template < typename Container, typename Iterator >
void push_back_n(Container& container, Iterator begin, Iterator end)
{
	const auto reserveCount = container.size() + std::distance(begin, end);
	container.reserve(reserveCount);
	for (auto i = begin; i != end; ++i)
	{
		container.push_back(*i);
	}
}

template < typename Container, typename Iterator >
void push_back_n(Container& container, Iterator begin, Iterator end)
{
	const auto reserveCount = container.size() + std::distance(begin, end);
	container.reserve(reserveCount);
	for (auto i = begin; i != end; ++i)
	{
		container.push_back(*i);
	}
}

int main()
{
	std::vector<int> vec{1,2,3,4,5};
	std::list<int> li{10, 11, 12, 13};

	push_back_n(vec, li.begin(), li.end());

	for (auto v : vec)
	{
		std::cout << v << ',' << std::endl;
	}

	return 0;
}