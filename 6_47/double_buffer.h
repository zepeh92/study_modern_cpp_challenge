#pragma once

#include <mutex>
#include <shared_mutex>

template < typename Type >
class double_buffer
{
public:

	double_buffer()
	{
	}

	double_buffer(const Type& val) :
		m_front(val),
		m_back(val)
	{
	}

	void read(Type& outVal)
	{
		std::shared_lock<std::shared_mutex> guard(m_fm);
		outVal = m_front;
	}

	void write(const Type& val)
	{
		{
			std::lock_guard<std::mutex> guard(m_bm);
			m_back = val;
		}

		{
			std::unique_lock<std::shared_mutex> guard(m_fm);
			m_front = std::move(m_back);
		}
	}

private:

	Type m_front;
	Type m_back;
	std::shared_mutex m_fm;
	std::mutex m_bm;
};