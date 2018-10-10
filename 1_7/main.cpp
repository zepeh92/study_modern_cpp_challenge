/*
Amicable numbers
Write a program that prints the list of all pairs of amicable numbers smaller than 1,000,000.
*/

#include <iostream>
#include <cmath>
#include <set>

using namespace std;

bool is_prime(int v)
{
	if (v < 2) return false;

	for (int i = 2; i < v; ++i)
	{
		if (v % i == 0)
		{
			return false;
		}
	}
	return true;
}

bool is_divisor(int v, int divisor)
{
	return v % divisor == 0;
}

int sum_all_divisor(int v)
{
	int divsum = 0;
	for (int i = 1; i < v; ++i)
	{
		if (is_divisor(v, i))
		{
			divsum += i;
		}
	}
	return divsum;
}

int main()
{
	int max = 1'000'000;
	// https://ko.wikipedia.org/wiki/%EC%B9%9C%ED%99%94%EC%88%98

	/*
	// ��� ģȭ���� ���ؼ��� �������� ����
	for (int n = 2;; ++n)
	{
		int p = 3 * pow(2, n - 1) - 1;
		int q = 3 * pow(2, n) - 1;
		int r = 9 * pow(2, 2 * n - 1) - 1;

		if (is_prime(p) && is_prime(q) && is_prime(r))
		{
			int a = pow(2, n) * p * q;
			int b = pow(2, n) * r;

			printf("(%d, %d) ", a, b);
		}
	}
	*/
	set<int> exists;
	
	for (int a = 1; a <= max; ++a)
	{
		if (exists.find(a) == exists.end())
		{
			int b = sum_all_divisor(a);
			
			if (a == b) continue;
			
			int c = sum_all_divisor(b);

			if (a == c)
			{
				exists.insert({ a, b });
				printf("(%d, %d) ", a, b);
			}
		}
	}

	return 0;
}