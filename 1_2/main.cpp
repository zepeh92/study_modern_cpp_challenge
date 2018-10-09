/*
Greatest common divisor
Write a program that, given two positive integers, will calculate and print the greatest common divisor of the two.
## 최대 공약수
두개의 정수가 주어질때 이 두 숫자의 최대공약수 를 구하고 출력하여라.
*/

#include <iostream>
#include <algorithm>

using namespace std;

bool is_common_divisor(int a, int b, int v)
{
  return ((a % v) == 0) && ((b % v) == 0);
}

int main()
{
  int a, b;
  cin >> b >> a;

  for (int i = max(a, b); 1 < i; --i)
  {
    if (is_common_divisor(a, b, i))
    {
      cout << "greatest common divisor is " << i << endl;
      break;
    }
  }

  return 0;
}