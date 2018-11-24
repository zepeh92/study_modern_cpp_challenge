#pragma once

#include <cstddef>
#include <utility>
#include <iterator>

template < typename Type > class circular_buffer;
template < typename Type > class circular_buffer_iterator;

template < typename Type >
class circular_buffer_iterator
{
public:

	using iterator_category = std::forward_iterator_tag;
	using value_type = Type;
	using difference_type = ptrdiff_t;
	using pointer = Type*;
	using reference = Type&;
	using source_type = circular_buffer<Type>;

	circular_buffer_iterator()
	{
	}

	circular_buffer_iterator(source_type* src, std::size_t idx, std::size_t count) :
		m_src(src), m_idx(idx), m_count(count)
	{
	}

	~circular_buffer_iterator()
	{
	}

	pointer operator->()
	{
		return (m_src->m_arr + m_idx);
	}

	value_type& operator*()
	{
		return *(m_src->m_arr + m_idx);
	}

	const value_type& operator*() const
	{
		return *(m_src->m_arr + m_idx);
	}

	circular_buffer_iterator& operator++()
	{
		m_idx = m_src->get_next(m_idx);
		--m_count;
		return *this;
	}

	circular_buffer_iterator operator++(int)
	{
		const auto temp = *this;
		++(*this);
		return temp;
	}

	bool operator==(const circular_buffer_iterator& rhs) const
	{
		return m_src == rhs.m_src && m_idx == rhs.m_idx && m_count == rhs.m_count;
	}

	bool operator!=(const circular_buffer_iterator& rhs) const
	{
		return !(*this == rhs);
	}

private:

	source_type* m_src = nullptr;
	std::size_t m_idx = 0;
	std::size_t m_count = 0;
};

template < typename Type >
class circular_buffer
{
public:

	friend class circular_buffer_iterator<Type>;

	circular_buffer(std::size_t capacity) :
		m_cap(capacity)
	{
		if (capacity == 0)
		{
			throw std::invalid_argument("capacity too small");
		}
	}

	circular_buffer(circular_buffer&& rhs)
	{
		*this = std::move(rhs);
	}

	~circular_buffer()
	{
		if (m_arr)
		{
			clear();
			::operator delete(m_arr);
		}
	}

	void clear()
	{
		while (try_remove());
	}

	bool try_remove()
	{
		if (empty())
		{
			return false;
		}

		const auto next = get_next(m_front);
		
		(m_arr + m_front)->~Type();
		
		m_front = next;

		--m_size;

		return true;
	}

	void add(const Type& val)
	{
		check_arr_init();

		const auto next = get_next(m_back);

		new (m_arr + m_back) Type{ val };

		if (!full())
		{
			++m_size;
			m_back = next;
		}
		else
		{
			m_front = m_back = next;
		}
	}

	const Type& front() const
	{
		return m_arr[m_front];
	}

	Type& front()
	{
		return m_arr[m_front];
	}

	bool empty() const
	{
		return size() == 0;
	}

	std::size_t size() const
	{
		return m_size;
	}

	std::size_t capacity() const
	{
		return m_cap;
	}

	bool full() const
	{
		return capacity() == size();
	}

	const Type* data() const
	{
		return m_arr;
	}

	Type* data()
	{
		return m_arr;
	}

	circular_buffer& operator=(circular_buffer&& rhs)
	{
		m_arr = rhs.m_arr;
		m_front = rhs.m_front;
		m_back = rhs.m_back;
		m_cap = rhs.m_cap;
		m_size = rhs.m_size;

		rhs.m_arr = nullptr;
		rhs.m_front = rhs.m_back = rhs.m_size = 0;

		return *this;
	}

	circular_buffer_iterator<Type> begin()
	{
		return {this, m_front, size()};
	}

	circular_buffer_iterator<Type> end()
	{
		return {this, m_back, 0};
	}

private:

	void check_arr_init()
	{
		if (m_arr == nullptr)
		{
			m_arr = static_cast<Type*>(::operator new(sizeof(Type) * m_cap));
		}
	}

	std::size_t get_next(std::size_t idx) const
	{
		return (idx + 1) != m_cap ? (idx + 1) : 0;
	}

	std::size_t get_prev(std::size_t idx) const
	{
		return idx != 0 ? idx - 1 : m_cap - 1;
	}

	Type* m_arr = nullptr;
	std::size_t m_cap = 0;
	std::size_t m_front = 0;
	std::size_t m_back = 0;
	std::size_t m_size = 0;
};