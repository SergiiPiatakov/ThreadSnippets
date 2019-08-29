// Create a simple thread (dummy example).
// $ g++ -Wall -Wextra -std=c++11 001_main.cpp -lpthread -o 001_main
// $ ./001_main
#include <thread>
#include <iostream>

void routine ()
{
    // The background thread ID.
    std::cout << std::this_thread::get_id () << std::endl;
}

int main (int, char **)
{
    // The main thread ID.
    std::cout << std::this_thread::get_id () << std::endl;

    std::thread thread (routine);
    thread.join ();

    return EXIT_SUCCESS;
}
