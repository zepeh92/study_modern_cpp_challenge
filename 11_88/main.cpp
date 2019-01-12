/*
88. Caesar cipher
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

class CeasarCryptor
{
public:

  struct Range
  {
    vector<char> arr;
    int min = 0;
    int max = 0;

    Range(int start, int end)
    {
      int cnt = end - start;
      if (0 < cnt)
      {
        min = start;
        max = end;
        arr.resize(cnt);
        iota(arr.begin(), arr.end(), static_cast<char>(min));
      }
    }

    bool in_range(int c) const
    {
      return min <= c && c <= max;
    }
  };
  
  CeasarCryptor(int shift) :
    range('A', ('z' + 1))
  {
    this->shift = shift;
  }

  char encrypt(char c) const
  {
    if (!range.in_range(c)) return c;
    const int index = ((c - range.min) + shift) % range.arr.size();
    return range.arr[index];
  }

  string encrypt(const string& str) const
  {
    string ret;
    ret.reserve(str.size());
    transform(str.begin(), str.end(), back_inserter(ret), [&](char c) { return encrypt(c); });
    return ret;
  }


private:

  int shift;
  Range range;
};

int main()
{
  CeasarCryptor cryptor(3);

  string cipher = cryptor.encrypt("hello COME TO ROME");

  cout << cipher << endl;

  return 0;
}