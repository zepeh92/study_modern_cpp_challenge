/*
89. 비즈네르 암호
알파뱃 대문자만을 대상으로
*/

#include <algorithm>
#include <iostream>
#include <string>

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
    return 0 <= index ? (index % end) : ((end -1) + (index + 1) % end);
  }

private:

  int end;
};

struct VigenereTable
{
public:
  static constexpr int RangeMin = 'A';
  static constexpr int RangeMax = 'Z';
  static constexpr int RowCount = RangeMax - RangeMin + 1;
  static constexpr int ColumnCount = RangeMax - RangeMin + 1;

  char arr[RowCount][ColumnCount];

  void build()
  {
    int i = 0;
    for (int r = RangeMin; r <= RangeMax; ++r)
    {
      int j = 0;
      for (int c = r; c <= RangeMax; ++c)
      {
        arr[i][j++] = c;
      }
      for (int c = RangeMin; c <= r; ++c)
      {
        arr[i][j++] = c;
      }
      ++i;
    }
  }
};


class VigenereCryptor
{
public:

  VigenereCryptor(const string_view& key) :
    key(key)
  {
    table.build();
  }

  string encrypt(const string_view& str) const
  {
    string ret;
    ret.reserve(str.size());
    int i = 0;
    CircularIndex rowidx(key.size() - 1);
    transform(str.begin(), str.end(), back_inserter(ret), [&](char c) 
      { 
        int idx = key[rowidx[i++]];
        return encrypt(idx, c);
      });
    return ret;
  }

  string decrypt(const string_view& str) const
  {
    string ret;
    ret.reserve(str.size());
    int i = 0;
    CircularIndex rowidx(key.size() - 1);
    transform(str.begin(), str.end(), back_inserter(ret), [&](char c) 
      {
        int idx = key[rowidx[i++]];
        return decrypt(idx, c);
      });
    return ret;
  }

  bool in_range(char c) const
  {
    return table.RangeMin <= c && c <= table.RangeMax;
  }

private:

  char encrypt(int key, char c) const
  {
    if (!in_range(c)) return c;
    return table.arr[key - table.RangeMin][c - table.RangeMin];
  }

  char decrypt(int key, char c) const
  {
    if (!in_range(c)) return c;
    int colidx = c - table.RangeMin;
    auto& row = table.arr[key - table.RangeMin];
    for (int i = 0; i < table.ColumnCount; ++i)
    {
      if (row[i] == c)
      {
        return table.arr[0][i];
      }
    }
    return c;
  }

  string key;
  VigenereTable table;
};

int main()
{
  // 비교 대상 예문) https://ko.wikipedia.org/wiki/%EB%B9%84%EC%A6%88%EB%84%A4%EB%A5%B4_%EC%95%94%ED%98%B8
  string key = "SKY";
  string input = "DIVERTTROOPSTOEASTRIDGE";

  VigenereCryptor encryptor(key);

  string cipher = encryptor.encrypt(input);
  string plain = encryptor.decrypt(cipher);

  cout << "KEY: " << key << endl;
  cout << "INPUT: " << input << endl;
  cout << "CIPHER: " << cipher << endl;
  cout << "PLAIN: " << plain << endl;

  return 0;
}