/*
65. Thread-safe logging to the console
Write a class that enables components running in different threads to safely print log messages to the console by synchronizing access to the standard output stream to guarantee the integrity of the output. 
This logging component should have a method called log() with a string argument representing the message to be printed to the console.

https://docs.microsoft.com/en-us/previous-versions/c9ceah3b(v=vs.140)
iostream
The standard iostream objects cin, cout, cerr, clog, wcin, wcout, wcerr, and wclog follow the same rules as the other classes, with this exception: it is safe to write to an object from multiple threads.
For example, thread 1 can write to cout at the same time as thread 
2. However, this can cause the output from the two threads to be intermixed.
*/

#include <vector>
#include <list>
#include <sstream>
#include <shared_mutex>
#include <thread>
#include <iostream>
#include <atomic>
#include <cstdarg>

using namespace std;

class logger;
class log_buffer;

class logger{

public:

  using unique_lock = unique_lock<std::shared_mutex>;
  using shared_lock = shared_lock<std::shared_mutex>;
  using clock = chrono::steady_clock;
  using time_point = chrono::time_point<typename clock>;

  static logger& get_instance(){
    static logger inst{};
    return inst;
  }

  void write(const char* message) {

    using namespace std::chrono;

    const auto now = clock::now();
    const auto elapsed = now - m_merged;

    if (m_period < elapsed) {

      unique_lock lock{ m_mutex };

      if (m_period < elapsed) {

        m_merged = now;

        static int seq = 0;

        cout << "---seq" << seq++ << "---" << endl;

        for (log_buffer* buffer : m_buffers) {
          buffer->read(cout);
        }

        cout << "---------" << endl;
      }
    }

    log_buffer& buf = get_tls_buffer();

    shared_lock lock{ m_mutex };

    buf.write(message);
  }

private:

  class log_buffer {
  public:

    log_buffer() {
      logger::get_instance().register_buffer(this);
    }

    void write(const char* log) {
      m_buf += log;
    }

    void read(ostream& os) {
      os << m_buf;
      m_buf.clear();
    }

  private:

    string m_buf;
  };

  static log_buffer& get_tls_buffer() {
    static thread_local log_buffer buf;
    return buf;
  }

  void register_buffer(log_buffer* buf) {
    unique_lock lock{ m_mutex };
    m_buffers.push_back(buf);
  }

  logger() {
  }

  time_point m_merged;
  chrono::milliseconds m_period = chrono::milliseconds{ 1000 };
  shared_mutex m_mutex;
  list<ostream*> m_ostreams;
  list<log_buffer*> m_buffers;
};

int main() {

  using namespace std;

  std::stringstream ss;

  ss.move(std::cout);
  std::cout << ss.str();

  std::vector<std::thread> threads{

  };

  std::thread t0 = std::thread([&] {
      while (true) {
        logger::get_instance().write("message 0\n");
        std::this_thread::sleep_for(100ms);
      }
    });
  

  std::thread t1 = std::thread([&] {
    auto id = std::this_thread::get_id();
      while (true) {
        logger::get_instance().write("message 1\n");
        std::this_thread::sleep_for(100ms);
      } 
    });

  std::thread t2 = std::thread([&] {
    auto id = std::this_thread::get_id();
    while (true) {
      logger::get_instance().write("message 2\n");
      std::this_thread::sleep_for(100ms);
    }
    });

  t1.join();
  t2.join();
  t0.join();

  return 0;
}