/*
Converting numerical values to Roman
Write a program that, given a number entered by the user, prints its Roman numeral equivalent.
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
  tuple<int, char> table[]
  {
    {1000, 'M'},
    {500, 'D'},
    {100, 'C'},
    {50, 'L'},
    {10, 'X'},
    {5, 'V'},
    {1, 'I'}
  };

  string str;

  while(true)
  {
    int val;
    cin >> val;
    
    if (val < 0)
      break;
    
    str.clear();

    while (0 < val)
    {
      for (auto&&[v, c] : table)
      {
        if (v <= val)
        {
          str += c;
          val -= v;
          break;
        }
      }
    }

    cout << str << endl;
  }

	return 0;
}