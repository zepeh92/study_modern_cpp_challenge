/*
���� ���� �ȿ��� IPv4 �ּҵ��� ����
����ڷκ��� ������ ��Ÿ���� �� IPv4 �ּҵ��� �Է¹޾Ƽ� �������� ��� �ּҵ��� �����ϴ�
���α׷��� �ۼ��϶�. �� �������� ��û�� ����� �����ϱ� ���ؼ�, ���� �������� ���ǵ� ������
Ȯ���϶�
*/

#include <array>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class ipv4
{
public:

  static bool is_ipv4(const char* str)
  {
    return false;
  }

  ipv4()
  {
  }

  ipv4(const char* str)
  {
    *this = str;
  }

  ipv4(const std::string& str)
  {
    *this = str.c_str();
  }

  ipv4(const ipv4& rhs) :
    addr(rhs.addr)
  {
  }

  ipv4& operator = (const std::string& str)
  {
    return *this = str.c_str();
  }

  ipv4& operator = (const char* str)
  {
    int idx = 3;
    int count = 0;
    char buf[4] = { 0, };

    char c;
    do
    {
      c = *str++;
      if (count == 3 || c == '.' || c == 0)
      {
        buf[count] = 0;
        const int v = ::atoi(buf);
        const bool valid = 0 <= v && v <= std::numeric_limits<std::uint8_t>::max();
        if (not valid)
        {
          idx = 0;
          addr.fill(0);
          return *this;
        }
        addr[idx--] = static_cast<std::uint8_t>(v);
        count = 0;
        continue;
      }
      buf[count++] = c;
    } while (c != 0);

    return *this;
  }

  std::string to_string() const
  {
    std::stringstream ss;
    ss << *this;
    return ss.str();
  }

  uint8_t operator[](int index) const
  {
    return addr[index];
  }

  bool operator==(const ipv4& rhs) const
  {
    return addr == rhs.addr;
  }

  ipv4& operator++()
  {
    uint32_t& temp = *reinterpret_cast<uint32_t*>(&addr[0]);
    ++temp;
    return *this;
  }

  ipv4& operator++(int)
  {
    uint32_t& temp = *reinterpret_cast<uint32_t*>(&addr[0]);
    temp++;
    return *this;
  }

  friend std::ostream& operator << (std::ostream& os, const ipv4& v4);

private:

  std::array<std::uint8_t, 4> addr{ 0,0,0,0 };
};

std::ostream& operator << (std::ostream& os, const ipv4& v4)
{
  char buf[(3 * 4) + 4] = { 0, };
  snprintf(buf, sizeof(buf), "%hhu.%hhu.%hhu.%hhu", v4.addr[3], v4.addr[2], v4.addr[1], v4.addr[0]);
  return os << buf;
}

int main()
{
  string a;
  string b;
  cin >> a >> b;
  
  ipv4 begin(a);
  ipv4 end(b);

  cout << "begin: " << begin << endl;
  cout << "end: " << end << endl;

  while (true)
  {
    if (begin == end)
    {
      break;
    }
    cout << begin << endl;
    begin++;
  }

  cout << end;

  return 0;
}
