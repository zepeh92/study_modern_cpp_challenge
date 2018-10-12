/*
Gray code
Write a program that displays the normal binary representations, Gray code representations, and decoded Gray code values for all 5-bit numbers.
*/

#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

vector<bitset<8>> to_bitset(const void* bin, size_t len)
{
  vector<bitset<8>> ret;
  ret.reserve(len);
  bitset<8> bits;
  const char* cbin = (const char*)bin;
  for (auto i = len; 1 <= i; --i)
  {
    bits = cbin[i - 1];
    ret.push_back(bits);
  }
  return ret;
}

vector<bitset<8>> bin_to_gray(const void* bin, size_t len)
{
  if (len == 0)
  {
    return {};
  }

  vector<bitset<8>> res;
  res.reserve(len);

  bitset<8> bits;
  bitset<8> graybits;
  const char* cbin = (const char*)bin;
  bool lastbit = false;
  size_t i = len;
  
  do
  {
    --i;
    bits = cbin[i];
    graybits[graybits.size()-1] = lastbit ^ bits[bits.size()-1];
    size_t j = graybits.size() - 1;
    do
    {
      --j;
      graybits[j] = bits[j + 1] ^ bits[j];
    } while (j != 0);
    lastbit = graybits[0];
    res.push_back(graybits);
  } while (i != 0);

  return res;
}

uint32_t gray_to_uint(const void* gray, size_t len)
{
  if (len == 0)
  {
    return 0;
  }
  
  uint32_t res = 0;
  uint32_t temp = 0;
  bitset<8> graybits;
  bitset<8> bits;
  const char* const cgray = static_cast<const char*>(gray);
  bool lastbit = false;
  size_t i = len;
  
  do
  {
    --i;
    res = res | (temp << 8);
    graybits = cgray[i];
    bits[bits.size()-1] = graybits[graybits.size()-1] ^ lastbit;

    size_t j = bits.size() - 1;
    do
    {
      --j;
      bits[j] = bits[j + 1] ^ graybits[j];
    } while (j != 0);
    temp = bits.to_ulong();
    lastbit = bits[0];
  } while (i != 0);

  res = res | temp;
  
  return res;
}

template < typename Type >
uint32_t gray_to_uint(Type v)
{
  return gray_to_uint(&v, sizeof v);
}

int main()
{
  const uint8_t last = 0b00011111;// 15
  for (uint8_t i = 0; i != last; ++i)
  {
    cout << "n: " << (int)i << endl;
    cout << "bin: ";
    for (auto bits : to_bitset(&i, sizeof(i)))
    {
      cout << bits;
    }
    cout << endl;
    cout << "gray: ";
    for (auto bits : bin_to_gray(&i, sizeof(i)))
    {
      cout << bits;
    }
    cout << endl;
  }
  return 0;
}