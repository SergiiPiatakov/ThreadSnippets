// Data sharing, race condition.
// $ g++ -Wall -Wextra -std=c++11 004_main.cpp -lpthread -o 004_main
// $ ./004_main
// One possible output (with some modifications):
// $ uname -rvo
// 5.0.0-25-generic #26~18.04.1-Ubuntu SMP Thu Aug 1 13:51:02 UTC 2019 GNU/Linux
// $ gcc --version
// gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
// 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
// 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
#include <thread>
#include <cstdlib>
#include <functional>
#include <vector>
#include <chrono>
#include <iostream>

int main (int, char **)
{
    using item = long long int;
    using task = std::function <void(std::vector <item> &)>;

    auto adder = [](std::vector <item> & data){
        for (size_t i = 0; i < data.size (); ++i) {
            std::this_thread::sleep_for (std::chrono::nanoseconds (1) );
            data [i] += 1;
        }
    };

    auto multiplier = [](std::vector <item> & data){
        std::this_thread::sleep_for (std::chrono::nanoseconds (10) );
        for (size_t i = 0; i < data.size (); ++i) {
            data [i] *= 2;
        }
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
    std::vector <long long int> data;
    data.resize (dataSize);
    std::fill (data.begin (), data.end (), 1);

    print (data);

    std::vector <std::thread> workers;
    for (size_t i = 0; i < tasks.size (); ++i) {
        workers.push_back (std::thread (tasks [i], std::ref (data) ) );
    }
    for (size_t i = 0; i < workers.size (); ++i) {
        workers [i].join ();
    }

    print (data);

    return EXIT_SUCCESS;
}
