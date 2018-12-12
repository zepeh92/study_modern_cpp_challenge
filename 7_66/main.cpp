/*
66. Customer service system
Write a program that simulates the way customers are served in an office.
The office has three desks where customers can be served at the same time.
Customers can enter the office at any time.
They take a ticket with a service number from a ticketing machine and wait until their number is next for service at one of the desks.
Customers are served in the order they entered the office, or more precisely, in the order given by their ticket.
Every time a service desk finishes serving a customer, the next customer in order is served.
The simulation should stop after a particular number of customers have been issued tickets and served.
*/

#include <memory>
#include <thread>
#include <map>
#include <mutex>
#include <future>

using namespace std;

class Customer {
public:
};

class TicketingMachine {
public:

  int AllocNumber() {
    return m_lastAllocNumber++;
  }

private:

  std::atomic<int> m_lastAllocNumber = 0;
};

class Office {

public:

  using Guard = lock_guard<mutex>;

  void Enter(shared_ptr<Customer>&& customer) {

    const int number = m_ticketingMachine.AllocNumber();

    Guard g{ m_mutex };

    m_watingCustomers.emplace(number, move(customer));
  }

  void Run(int deskCount = 3) {

    m_desks.reserve(deskCount);

    generate_n(back_inserter(m_desks), deskCount, [this] {
      return thread([this] { RunDesk(); });
      });

    for (auto& desk : m_desks) {
      desk.join();
    }
  }

  void RunDesk() {

    while (true) {

      const int callNumber = m_lastCallNumber++;

      if (shared_ptr<Customer> customer{ TryPopCustomer(callNumber) }; customer != nullptr) {
        ProviceService(callNumber, *customer);
      }
      else {
        break;
      }
    }
  }

  void ProviceService(int ticketNumber, Customer& c) {
  }

  shared_ptr<Customer> TryPopCustomer(int number) {

    Guard g{ m_mutex };

    auto i = m_watingCustomers.find(number);

    if (i == m_watingCustomers.end()) {
      return nullptr;
    }

    auto ret = std::move(i->second);

    m_watingCustomers.erase(i);

    return ret;
  }

private:

  vector<thread> m_desks;
  mutex m_mutex;
  map<int, shared_ptr<Customer>> m_watingCustomers;
  atomic<int> m_lastCallNumber = 0;
  TicketingMachine m_ticketingMachine;
};

int main() {

  list<thread> customerSpawners;

  Office office;

  generate_n(back_inserter(customerSpawners), 3, [&] {
    return
      thread([&] {
      for (int i = 0; i < 300; ++i) {
        office.Enter(make_shared<Customer>());
      }
        });
    });

  for (auto& spawner : customerSpawners) {
    if (spawner.joinable()) {
      spawner.join();
    }
  }

  office.Run();

  return 0;
}