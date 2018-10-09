/*
Sum of naturals divisible by 3 and 5
Write a program that calculates and prints the sum of all the natural numbers divisible by either 3 or 5, up to a given limit entered by the user.
## 3�� 5�� ���������� ���� ���� ���Ͽ���
����ڰ� �Է��� ���ڱ��� 3 �Ǵ� 5�� ���������� ���� ���� ����Ͽ���
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