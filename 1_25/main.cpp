/*
25. 글 제목을 대문자 표시
입력된 텍스트 단어 단위로 대문자로
*/

#include <iostream>
#include <string>

using namespace std;

std::string capitalize(const std::string& str)
{
  string res;
  res.reserve(str.size());
  bool upper = true;
  for (auto c : str)
  {
	if (upper)
	{
	  c = toupper(c);
	  upper = false;
	}

	switch (c)
	{
	case ' ':
	case '\n':
	case '\r\n':
	  upper = true;
	default:
	  break;
	}
	res.push_back(c);
  }
  return res;
}

int main()
{
  string str;
  getline(cin, str);

  cout << capitalize(str) << endl;
 
  return 0;
}