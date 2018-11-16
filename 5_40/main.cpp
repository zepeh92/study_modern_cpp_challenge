// 40. �� ��¥�� �־����� �� ��¥�� ������ �ϼ��� �����ϴ� �Լ��� �ۼ��ϼ���.

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int daydiff(const system_clock::time_point& a, const system_clock::time_point& b)
{
	const auto diff = b - a;
	return duration_cast<chrono::hours>(diff).count() / 24;
}

int main()
{	
	system_clock::time_point a = chrono::system_clock::now() - 73h;
	system_clock::time_point b = chrono::system_clock::now();

	cout << daydiff(a, b) << endl;

	return 0;
}