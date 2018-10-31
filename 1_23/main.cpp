/*
23. ���̳ʸ�(Bin(ry)�����ڿ��κ�ȯ8��Ʈ���������޾Ƽ��������鿡���� 16�������ڿ�����ȯ�ϴ��Լ����ۼ��϶�. ���Լ��´빮�ڿͼҹ��ڸ�������Ҽ��־���Ѵ�.
�����Է°���¿����ѿ��������Ͻÿ�:�Է�: { 0xBA, 0xAD, 0xF0, 0x0D }, ���: "BAADF00D"  �Է�: { 1,2,3,4,5,6 }, ���: "010203040506"
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