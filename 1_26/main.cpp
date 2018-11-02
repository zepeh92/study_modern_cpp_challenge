/*
26. �����ڷ� �и��� ���ڿ����� ����
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string concat(const vector<string>& strs, char delim)
{
  string ret;
  if (strs.empty())
  {
	return ret;
  }

  auto i = strs.begin();
  ret += *i++;
  for (i; i != strs.end(); ++i)
  {
	ret += delim;
	ret += *i;
  }
  
  return ret;
}

int main()
{
  cout << concat({"this", "is", "an", "example"}, ' ') << endl;
  return 0;
}