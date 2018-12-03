/*
62. Parallel min and max element algorithms using threads
Implement general-purpose parallel algorithms that find the minimum value and, respectively, the maximum value in a given range. 
The parallelism should be implemented using threads, although the number of concurrent threads is an implementation detail.
*/

#include <iostream>
#include <thread>
#include <algorithm>
#include <iterator>

using namespace std;

template < typename Iterator, typename Func >
auto pararrel_min_element(Iterator begin, Iterator end, Func func, size_t leaf = 1024){

  using ValueType = typename Iterator::value_type;

  const auto dist = (size_t)distance(begin, end);

  if (dist <= leaf) {
    return *min_element(begin, end, func);
  }

  const auto concurrency = thread::hardware_concurrency();
  size_t threadCount = min<size_t>(concurrency, dist / leaf);
  const auto sep = dist / threadCount;
  
  vector<pair<thread, ValueType>> threads(threadCount);
  if (threads.empty())
  {
    return pararrel_min_element(begin, end, func, dist);
  }

  auto it = begin;
  
  for (size_t i = 0; i != threads.size() - 1; ++i)
  {
    auto& thrd = threads[i];

    auto end = it;
    advance(end, sep);
    thrd.first = std::thread([&, it, end] {
      thrd.second = pararrel_min_element(it, end, func, sep);
    });
    it = end;
  }
  
  auto& lastThrd = threads.back();
  lastThrd.first = std::thread([&, it] {
    lastThrd.second = pararrel_min_element(it, end, func, std::distance(it, end));
  });
  
  for (auto& [thrd, min] : threads)
  {
    thrd.join();
  }

  return min_element(threads.begin(), threads.end(), [&](const auto& lhs, const auto& rhs) {
    return func(lhs.second, rhs.second);
  })->second;
}

int main()
{
  int count = 100;
  vector<int> vals{};
  for (int i = count; i != 0; --i) {
    vals.push_back(i);
  }

  auto min = pararrel_min_element(vals.begin(), vals.end(), [](auto a, auto b) { return a < b; }, 3);
  cout << "min: " << min << endl;
  return 0;
}