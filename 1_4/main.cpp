/*
Largest prime smaller than given number
Write a program that computes and prints the largest prime number that is smaller than a number provided by the user, which must be a positive integer.

## 주어진 숫자안에서 가장 큰 소수 구하기
사용자가 입력한 숫자안에서 가장 큰 소수 구하기(이 값은 양수여야한다)
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

int main()
{
  int val;
  cin >> val;

  for (int i = val; 1 < val; --i)
  {
    if (is_prime(i))
    {
      cout << i << " is largest prime" << endl;
      break;
    }
  }

  return 0;
}