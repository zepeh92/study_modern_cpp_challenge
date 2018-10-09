/*
Least common multiple
Write a program that will, given two or more positive integers, calculate and print the least common multiple of them all.

## �ּ� �����
�� �� �̻��� ������ �ּ� ������� ����ϰ� ����Ͽ���
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
  int a;
  int b;
  cin >> a >> b;

  int i = max(a, b);
  do
  {
    if (i % a == 0 && i % b == 0)
    {
      cout << "common multiple is " << i << endl;
      break;
    }
    ++i;
  } while (i != numeric_limits<int>::max());

  return 0;
}