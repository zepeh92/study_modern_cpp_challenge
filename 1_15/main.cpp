/*
IPv4 주소를 나타내는 클래스를 작성하라. 콘솔로부터 IPv4 주소들을 읽고 쓸 수 있기 위해 필요
한 함수를 구현하라. 사용자는 값을 127.0.0.1 이나 168.192.0.100과 같이 점이 포함된 형태
(dotted form)로 입력할 수 있어야 한다. 또한 IPv4 형태의 주소들을 출력 스트림으로 만들 수
있어야 한다
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
  ipv4 v4("0.0.0.0");

  std::cout << v4; 

  return 0;
}