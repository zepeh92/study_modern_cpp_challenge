#include <string>
#include <sstream>
#include <iostream>

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

  ipv4(const ipv4& rhs)
  {
    memcpy(addr, rhs.addr, sizeof(addr));
  }

  ipv4& operator = (const std::string& str)
  {
    return *this = str.c_str();
  }

  ipv4& operator = (const char* str)
  {
    int idx = 0;
    int count = 0;
    char buf[4] = {0,};

    while (*str != 0)
    {
      buf[count++] = *str;
      if (count == 3 || *str == '.')
      {
        const auto v = ::atoi(buf);
        const bool valid = 0 <= v && v <= 255;
        if(!valid)
        {
          idx = 0;
          break;
        }
        addr[idx++] = static_cast<std::uint8_t>(v);
        count = 0;
      }
      ++str;
    }

    if (idx != 3)
    {
      memset(addr, 0, sizeof(addr));
    }

    return *this;
  }

  std::string to_string() const
  {
    std::stringstream ss;
    ss << *this;
    return ss.str();
  }

  friend std::ostream& operator << (std::ostream& os, const ipv4& v4);

private:

  std::uint8_t addr[4]{ 0,0,0,0 };
};

std::ostream& operator << (std::ostream& os, const ipv4& v4)
{
  char buf[(3*4) + 4] = {0,};
  sprintf_s(buf, "%d.%d.%d.%d", v4.addr[0], v4.addr[1], v4.addr[2], v4.addr[3]);
  return os << buf;
}

int main()
{
  ipv4 v4("127.0.0.272");

  std::cout << v4;

  return 0;
}