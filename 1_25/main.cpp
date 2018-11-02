/*
25. �� ������ �빮�� ǥ��
�Էµ� �ؽ�Ʈ �ܾ� ������ �빮�ڷ�
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