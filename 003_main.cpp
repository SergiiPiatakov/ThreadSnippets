// Data sharing.
// $ g++ -Wall -Wextra -std=c++11 003_main.cpp -lpthread -o 003_main
// $ ./003_main
#include <thread>
#include <cstdlib>
#include <functional>
#include <vector>
#include <iostream>

int main (int, char **)
{
    auto worker = [](std::vector <int> & data, size_t from, size_t n){
        for (size_t i = from; i < from + n; ++i) {
            data [i] = (data [i] + 1) * 2;
        }
    };

    auto print = [](const std::vector <int> & data){
        for (size_t i = 0; i < data.size (); ++i) {
            std::cout << data [i] << " ";
        }
        std::cout << std::endl;
    };

    constexpr size_t dataSize       {32};
    constexpr size_t workerNumber   {2};
    std::vector <int> data;
    data.resize (dataSize);
    std::fill (data.begin (), data.end (), 1);

    print (data);

    std::vector <std::thread> workers;
    for (size_t i = 0; i < workerNumber; ++i) {
        workers.push_back (std::thread (worker, std::ref (data), i * dataSize / workerNumber, dataSize / workerNumber) );
    }
    for (size_t i = 0; i < workers.size (); ++i) {
        workers [i].join ();
    }

    print (data);

    return EXIT_SUCCESS;
}
