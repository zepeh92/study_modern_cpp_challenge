/*

Abundant numbers
Write a program that prints all abundant numbers and their abundance, up to a number entered by the user.

## 과잉수 구하기
사용자가 입력한 숫자까지 과잉수를 구하기
[과잉수란](https://ko.wikipedia.org/wiki/%EA%B3%BC%EC%9E%89%EC%88%98)

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