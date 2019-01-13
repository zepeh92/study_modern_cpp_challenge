/*
88. Caesar cipher
대문자만을 대상으로 
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

class CircularIndex
{
public:

  explicit CircularIndex(int max) :
    end{ max + 1 }
  {
  }

  int operator[](int index) const
  {
    return 0 <= index ? (index % end) : ((end - 1) + (index + 1) % end);
  }

private:

  int end;
};

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
    CircularIndex idx(range.max - range.min - 1);
    return range.arr[idx[c - range.min + shift]];
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
  string input = "hello COME TO ROME";
  int shift = 3;

  CeasarCryptor cryptor(shift);

  string cipher = cryptor.encrypt(input);

  // 비교) https://ko.wikipedia.org/wiki/%EC%B9%B4%EC%9D%B4%EC%82%AC%EB%A5%B4_%EC%95%94%ED%98%B8
  cout << "SHIFT: " << shift << endl;
  cout << "INPUT: " << input << endl;
  cout << "CIPHER: " << cipher << endl;

  return 0;
}