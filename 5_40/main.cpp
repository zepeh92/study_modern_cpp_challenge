// 40. 두 날짜가 주어지면 그 날짜의 사이의 일수를 리턴하는 함수를 작성하세요.

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