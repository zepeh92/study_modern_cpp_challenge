/*
46. Circular buffer
Create a data structure that represents a circular buffer of a fixed size. A circular buffer overwrites existing elements when the buffer is being filled beyond its fixed size. The class you must write should:
•	Prohibit default construction
•	Support the creation of objects with a specified size
•	Allow checking of the buffer capacity and status (empty(), full(), size(), capacity())
•	Add a new element, an operation that could potentially overwrite the oldest element in the buffer
•	Remove the oldest element from the buffer
•	Support iteration through its elements
*/

#include <iostream>

#include "circular_buffer.h"

using namespace std;

template < typename BufferType >
void print_state(const BufferType& buffer)
{

	auto data = buffer.data();

	cout << "size: " << buffer.size() << ", capacity: " << buffer.capacity() << ", front: " << buffer.front() << endl;
	cout << "elems: [";
	for (size_t i = 0; i != buffer.capacity() - 1; ++i)
	{
		cout << data[i] << ", ";
	}
	cout << data[buffer.capacity() - 1] << ']' << endl;
}

int main()
{
	circular_buffer<int> cb{ 3 };

	cout << endl << "add" << endl;

	for (int i = 0; i != cb.capacity() * 2; ++i)
	{
		cb.add(i);
		print_state(cb);
	}

	cout << endl << "iterator" << endl;

	for (auto& v : cb)
	{
		cout << v << ", ";
	}

	cout << endl << "remove" << endl << endl;

	for (int i = 0; i != cb.capacity(); ++i)
	{
		cb.try_remove();
		print_state(cb);
	}

	cout << endl << "add" << endl;

	for (int i = 0; i != (cb.capacity() / 2); ++i)
	{
		cb.add(i);
		print_state(cb);
	}

	return 0;
}