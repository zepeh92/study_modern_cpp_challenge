// 39.함수의 실행 시간을 측정하세요

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class stopwatch
{
public:

	using Clock = chrono::system_clock;

	void restart()
	{
		start = Clock::now();
	}

	auto get_elapsed() const
	{
		return end - start;
	}

	auto get_elapsed_ms() const
	{
		return chrono::duration_cast<chrono::microseconds>(get_elapsed()).count();
	}

	auto get_elapsed_sec() const
	{
		return chrono::duration_cast<chrono::seconds>(get_elapsed()).count();
	}

	auto get_elapsed_nanosec() const
	{
		return chrono::duration_cast<chrono::nanoseconds>(get_elapsed()).count();
	}

	void stop()
	{
		end = Clock::now();
	}

private:

	Clock::time_point start;
	typename Clock::time_point end;
};

void do_something()
{
	std::this_thread::sleep_for(5s);
}

void print_execution_time(const std::function<void()>& func, std::ostream& os = std::cout)
{
	stopwatch sw;
	sw.restart();

	func();

	sw.stop();

	os << "sec: " << sw.get_elapsed_sec() << endl;
	os << "ms: " << sw.get_elapsed_ms() << endl;
	os << "nanosec: " << sw.get_elapsed_nanosec() << endl;
}

#include <sstream>

int main()
{
	print_execution_time(do_something);

	return 0;
}