/*
63. Parallel min and max element algorithms using asynchronous functions
Implement general-purpose parallel algorithms that find the minimum value and, respectively, the maximum value in a given range. 
The parallelism should be implemented using asynchronous functions, although the number of concurrent functions is an implementation detail.
*/

#include <future>
#include <iostream>

using namespace std;

template < typename Iterator, typename ValueType = typename Iterator::value_type >
auto pararrel_minmax_element(Iterator begin, Iterator end, size_t leaf){

  const auto dist = static_cast<size_t>(distance(begin, end));
  if (dist <= leaf) {
    const auto minmax = minmax_element(begin, end);
    return make_pair(*minmax.first, *minmax.second);
  }

  auto mid = begin;
  advance(mid, (dist / 2));
  
  auto f0 = async(launch::async, [](auto begin1, auto end1, auto leaf) {
    return pararrel_minmax_element(begin1, end1, leaf);
  }, begin, mid, leaf);

  auto f1 = async(launch::async, [](auto begin1, auto end1, auto leaf) {
    return pararrel_minmax_element(begin1, end1, leaf);
  }, mid, end, leaf);

  const auto f0minmax = f0.get();
  const auto f1minmax = f1.get();

  return make_pair(min(f0minmax.first, f1minmax.first), max(f0minmax.second, f1minmax.second));
}

int main(){

  vector<int> vals{1,2,3,4,5,6,7,8,9,10,11};

  const auto [min, max] = pararrel_minmax_element(vals.begin(), vals.end(), 2);

  cout << "min: " << min << endl;
  cout << "max: " << max << endl;
  
  return 0;
}