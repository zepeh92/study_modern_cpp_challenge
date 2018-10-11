/*
Prime factors of a number
Write a program that prints the prime factors of a number entered by the user.

# 소인수 분해
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  int v;
  cin >> v;

  while (2 <= v)
  {
    for (int i = 2; i <= v; ++i)
    {
      if (v % i == 0)
      {
        cout << i << ' ';
        v /= i;
        break;
      }
    }
  }

  return 0;
}