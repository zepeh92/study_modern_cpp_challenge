/*
Sexy prime pairs
Write a program that prints all the sexy prime pairs up to a limit entered by the user.

## !섹!시! 소수 쌍을 구하기
사용자가 입력한 숫자까지 모든 섹시 소수를 구하여라
[섹시 소수란](https://ko.wikipedia.org/wiki/%EC%84%B9%EC%8B%9C_%EC%86%8C%EC%88%98)
*/

#include <iostream>

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

bool is_sexy_prime(int v)
{
  return is_prime(v) && is_prime(v + 6);
}

int main()
{
  int val;
  cin >> val;

  for (int i = 2; i <= val; ++i)
  {
    if (is_sexy_prime(i))
    {
      printf("(%d,%d)", i, i + 6);
    }
  }

  return 0;
}