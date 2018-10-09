/*
Sum of naturals divisible by 3 and 5
Write a program that calculates and prints the sum of all the natural numbers divisible by either 3 or 5, up to a given limit entered by the user.
## 3가 5가 나누어지는 수의 합을 구하여라
사용자가 입력한 숫자까지 3 또는 5이 나누어지는 수의 합을 출력하여라
*/

#include <iostream>

using namespace std;

int main()
{
  int val;
  cin >> val;

  int res = 0;
  for (int i = 0; i <= val; ++i)
  {
    if (i % 5 == 0 || i % 3 == 0)
    {
      res += i;
      break;
    }
  }

  cout << res << endl;

  return 0;
}