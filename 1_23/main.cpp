/*
23. 바이너리(Bin(ry)를문자열로변환8비트정수들을받아서그정수들에대한 16진수문자열을반환하는함수를작성하라. 이함수는대문자와소문자모두제공할수있어야한다.
여기입력과출력에대한예를참고하시오:입력: { 0xBA, 0xAD, 0xF0, 0x0D }, 출력: "BAADF00D"  입력: { 1,2,3,4,5,6 }, 출력: "010203040506"
*/

#include <iostream>
#include <iomanip>

template < typename Container >
void print(Container&& container, bool upper = true)
{
	using namespace std;

	cout << hex << uppercase << setfill('0');

	for (auto v : container)
	{
		cout << setw(2) << static_cast<int>(v);
	}

	cout << endl;
}

int main()
{
	auto vals0 = { 0xBA, 0xAD, 0xF0, 0x0D };
	print(vals0);

	auto vals1 = { 1,2,3,4,5,6 };
	print(vals1, false);

	return 0;
}