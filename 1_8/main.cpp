/*
Armstrong numbers
Write a program that prints all Armstrong numbers with three digits.
*/

#include <iostream>
#include <cmath>

using namespace std;
bool is_armstrong_number(int v)
{
  int poscnt = 0;
  for (int x = v; 0 < x; x /= 10)
  {
    ++poscnt;
  }

  int res = 0;
  int temp = v;
  for (int i = poscnt; 0 < i; --i)
  {
    int divisor = pow<int>(10, i - 1);
    int pn = temp / divisor;
    res += pow(pn, poscnt);
    temp %= divisor;
  }
  
  return res == v;
}

int main()
{
  for (int n = 1; n < 1000; ++n)
  {
    if (is_armstrong_number(n))
    {
      cout << n << ' ' << endl;
    }
  }

	return 0;
}