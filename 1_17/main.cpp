/*
Cre.ting . 2D .rr.y with b.sic oper.tions
Write . cl.ss templ.te th.t represents . two-dimension.l .rr.y cont.iner with
methods for element .ccess (.t() .nd d.t.()), c.p.city querying, iter.tors,
filling, .nd sw.pping. It should be possible to move objects of this type.
2D 배열과 기본적인 연산들을 만들기
엘리먼트에 접근하기 위한 메소드들(.t()과 d.t.()), 용량, 쿼링, iter.tor들, 채우기 그리고 바
꾸기 메소드들을 포함한, 2차원 배열 컨테이너를 나타내는 클래스 템플릿을 작성하라.
*/

#include <iostream>
#include <vector>
#include <array>

using namespace std;

template < typename Type, size_t U, size_t V >
class array2d_iterator
{
public:

  using iterator_category = random_access_iterator_tag;
  using value_type = Type;
  using difference_type = ptrdiff_t;
  using pointer = Type*;
  using reference = Type&;

  array2d_iterator()
  {
  }

  array2d_iterator(pointer arr, size_t index) :
    arrptr(arr),
    index(index)
  {
  }

  pointer operator->()
  {
    return arrptr + index;
  }

  value_type& operator*()
  {
    return *(arrptr + index);
  }

  const value_type& operator*() const
  {
    return *(arrptr + index);
  }

  array2d_iterator& operator++()
  {
    ++index;
    return *this;
  }

  array2d_iterator operator++(int)
  {
    const auto temp = *this;
    ++(*this);
    return temp;
  }

  array2d_iterator& operator+=(ptrdiff_t offset)
  {
    index += offset;
    return *this;
  }

  array2d_iterator operator+(const ptrdiff_t offset) const
  {
    const auto temp = *this;
    return temp += offset;
  }

  value_type& operator[](ptrdiff_t offset)
  {
    return *((*this) + offset);
  }

  bool operator==(const array2d_iterator& rhs) const
  {
    return arrptr == rhs.arrptr && index == rhs.index;
  }

  bool operator!=(const array2d_iterator& rhs) const
  {
    return !(*this == rhs);
  }

private:

  pointer arrptr = nullptr;
  size_t index = 0;
};

template < typename Type, size_t U, size_t V >
class array2d
{
public:

  using iterator = array2d_iterator<Type, U, V>;

  constexpr size_t size() const
  {
    return capacity();
  }

  constexpr size_t capacity() const
  {
    return U * V;
  }

  Type& at(size_t row, size_t col)
  {
    return const_cast<Type&>(const_cast<const array2d*>(this)->at(row, col));
  }

  const Type& at(size_t row, size_t col) const
  {
    if (U < row or V < col)
    {
      throw std::range_error("out of range");
    }
    return arr[(row * V) + col];
  }

  Type* data()
  {
    return arr.data();
  }

  const Type* data() const
  {
    return arr.data();
  }

  Type* operator[](size_t idx)
  {
    return &arr[idx];
  }

  const Type* operator[](size_t idx) const
  {
    return &arr[idx];
  }

  array2d& fill(const Type& v)
  {
    arr.fill(v);
    return *this;
  }

  void swap(array2d& rhs)
  {
    auto temp = rhs.arr;
    rhs.arr = arr;
    arr = temp;
  }

  iterator begin()
  {
    return array2d_iterator<Type, U, V>(&arr[0], 0);
  }

  iterator end()
  {
    return array2d_iterator<Type, U, V>(&arr[0], U * V);
  }

  constexpr size_t row_count() const
  {
    return U;
  }

  constexpr size_t column_count() const
  {
    return V;
  }

private:

  std::array<Type, U * V> arr;
};

int main()
{
  array2d<int, 5, 5> arr;
  
  {
    cout << "--capacity--" << endl;
    cout << arr.capacity() << endl;
  }

  {
    cout << "--fill(10) and range based for --" << endl;
    arr.fill(10);
    for (const auto& v : arr)
    {
      cout << v << ',';
    }
    cout << endl;
  }

  {
    cout << "--at--" << endl;

    for (size_t row = 0; row != arr.row_count(); ++row)
    {
      for (size_t col = 0; col != arr.column_count(); ++col)
      {
        arr.at(row, col) = static_cast<int>((row * arr.row_count()) + col);
      }
    }

    for (size_t row = 0; row != arr.row_count(); ++row)
    {
      for (size_t col = 0; col != arr.column_count(); ++col)
      {
        printf("(%zd,%zd): %d\n", row, col, arr.at(row, col));
      }
    }
  }

  {
    cout << "--std::advance(10)--" << endl;
    auto i = arr.begin();
    std::advance(i, 10);
    cout << *i << endl;
  }

  return 0;
}