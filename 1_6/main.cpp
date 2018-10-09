/*

Abundant numbers
Write a program that prints all abundant numbers and their abundance, up to a number entered by the user.

## ���׼� ���ϱ�
����ڰ� �Է��� ���ڱ��� ���׼��� ���ϱ�
[���׼���](https://ko.wikipedia.org/wiki/%EA%B3%BC%EC%9E%89%EC%88%98)

*/

#include <iostream>

using namespace std;

bool is_divisor(int a, int b)
{
  return b < a && (a % b == 0);
}

bool is_abundant_number(int v)
{
  int temp = 0;
  for (int i = 1; i < v; ++i)
  {
    if (is_divisor(v, i))
    {
      temp += i;
    }
  }
  return v < temp;
}

int main()
{
  int val;
  cin >> val;

  for (int i = 0; i <= val; ++i)
  {
    if (is_abundant_number(i))
    {
      cout << i << ',';
    }
  }
  
  return 0;
}