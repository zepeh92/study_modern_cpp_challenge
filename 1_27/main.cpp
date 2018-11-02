/*
27. 구분자 목록을 받아 문자열을 분리
*/

#include <iostream>
#include <string>
#include <regex>

using namespace std;

vector<string> split(const string& str, const string& delims)
{
  vector<string> ret;
  string temp;
  for (auto ch : str)
  {
	const auto i = find(delims.begin(), delims.end(), ch);
	if (i == delims.end())
	{
	  temp.push_back(ch);
	}
	else
	{
	  ret.push_back(temp);
	  temp.clear();
	}
  }
  if (!temp.empty())
  {
	ret.push_back(temp);
  }
  return ret;
}

int main()
{
  for (const auto& str : split("this,is.an example", ",. "))
  {
	cout << str << endl;
  }
  return 0;
}