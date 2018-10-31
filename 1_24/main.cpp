/*
24. ���ڿ������̳ʸ��κ�ȯ16�������ڿ����޾Ƽ�, 
�׹��ڿ����ڰ����̺�ȯ�� 8��Ʈ�������Ǻ��͸���ȯ�ϴ��Լ����ۼ��϶�.
�����ǿ��������Ͻÿ�:�Է�: "BAADF00D" or "b((dF00D", ��� : {0xBA, 0xAD, 0xF0, 0x0D} �Է� "010203040506", ��� : {1, 2, 3, 4, 5, 6}
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