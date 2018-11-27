/*
47. Double buffer
Write a class that represents a buffer that could be written and read at the same time without the two operations colliding.
A read operation must provide access to the old data while a write operation is in progress. 
Newly written data must be available for reading upon completion of the write operation.
*/

#include <thread>
#include <iostream>
#include <chrono>
#include <array>
#include <string>
#include "double_buffer.h"

using namespace std;
using namespace std::chrono;

class virtual_buffer
{
public:

	virtual_buffer(const std::string& str = "0") :
		m_str(str)
	{
	}

	virtual_buffer& operator=(const virtual_buffer& rhs)
	{
		m_str = rhs.m_str;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, virtual_buffer& buf);

private:

	std::string m_str;
};

std::ostream& operator<<(std::ostream& os, virtual_buffer& buf)
{
	os << buf.m_str;
	return os;
}

int main()
{
	double_buffer<virtual_buffer> buf;

	std::thread t0([&] {

		virtual_buffer rb;

		while (true)
		{
			buf.read(rb);
			cout << rb << endl;

			std::this_thread::sleep_for(50ms);
		}
		
	});

	std::thread t1([&] {

		int seq = 0;

		while (true)
		{
			virtual_buffer wb(std::to_string(seq++));

			buf.write(wb);

			std::this_thread::sleep_for(100ms);
		}
	});

	t0.join();
	t1.join();

	return 0;
}