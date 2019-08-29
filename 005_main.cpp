// Data sharing, synchronization.
// Using a mutech in such case is redundant. Using `join` is enough.
// $ g++ -Wall -Wextra -std=c++11 005_main.cpp -lpthread -o 005_main
// $ ./005_main
#include <thread>
#include <mutex>
#include <cstdlib>
#include <functional>
#include <vector>
#include <chrono>
#include <iostream>

int main (int, char **)
{
    using item = long long int;
    using task = std::function <void(std::vector <item> &, std::mutex &)>;

    auto adder = [](std::vector <item> & data, std::mutex & lock){
        lock.lock ();
        for (size_t i = 0; i < data.size (); ++i) {
            std::this_thread::sleep_for (std::chrono::nanoseconds (1) );
            data [i] += 1;
        }
        lock.unlock ();
    };

    auto multiplier = [](std::vector <item> & data, std::mutex & lock){
        lock.lock ();
        std::this_thread::sleep_for (std::chrono::nanoseconds (10) );
        for (size_t i = 0; i < data.size (); ++i) {
            data [i] *= 2;
        }
        lock.unlock ();
    };

    auto print = [](const std::vector <item> & data){
        for (size_t i = 0; i < data.size (); ++i) {
            std::cout << data [i] << " ";
        }
        std::cout << std::endl;
    };

    std::vector <task> tasks {
        adder
      , multiplier
    };

    constexpr size_t dataSize {32};
    std::mutex lock;
    std::vector <long long int> data;
    data.resize (dataSize);
    std::fill (data.begin (), data.end (), 1);

    print (data);

    std::vector <std::thread> workers;
    for (size_t i = 0; i < tasks.size (); ++i) {
        workers.push_back (std::thread (tasks [i], std::ref (data), std::ref (lock) ) );
    }
    for (size_t i = 0; i < workers.size (); ++i) {
        workers [i].join ();
    }

    print (data);

    return EXIT_SUCCESS;
}
