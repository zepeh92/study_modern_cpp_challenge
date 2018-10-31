/*
24. 문자열을바이너리로변환16진수문자열을받아서, 
그문자열숫자값들이변환된 8비트정수들의벡터를반환하는함수를작성하라.
다음의예를참고하시오:입력: "BAADF00D" or "b((dF00D", 출력 : {0xBA, 0xAD, 0xF0, 0x0D} 입력 "010203040506", 출력 : {1, 2, 3, 4, 5, 6}
*/

#include <iostream>
#include <iomanip>
#include <string_view>
#include <sstream>
#include <vector>

using namespace std;

auto to_vector(std::string_view view)
{
	const size_t len = (view.length() / 2);
	vector<int> ret(len);
	std::stringstream ss;
 	for (int i = 0; i < len; ++i)
	{
		auto str = view.substr(i * 2, 2);
		ss << hex << setw(2) << str;
		int v;
		ss >> v;
		ret.push_back(v);
		ss.clear();
	}
	cout << endl;
	return ret;
}

int main()
{
	for (auto v : to_vector("BAADF00D"))
	{
		cout << v << ',';
	}

	cout << endl;

	for (auto v : to_vector("010203040506"))
	{
		cout << v << ',';
	}
	
	return 0;
}