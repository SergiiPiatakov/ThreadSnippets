// Create a simple thread.
// Different approaches.
// $ g++ -Wall -Wextra -std=c++11 002_main.cpp -lpthread -o 002_main
// $ ./002_main
#include <thread>
#include <cstdlib>
#include <functional>
#include <vector>
#include <iostream>

void Function ()
{
    std::cout << "Function: " << std::this_thread::get_id () << std::endl;
}

struct Functor
{
    std::thread::id id;

    void operator () ()
    {
        id = std::this_thread::get_id ();
        std::cout << "Functor: " << id << std::endl;
    }
};

int main (int, char **)
{
    auto lamda = []()->void {
        std::cout << "Lamda: " << std::this_thread::get_id () << std::endl;
    };

    Functor functor;

    std::vector <std::function <void()> > tasks;
    tasks.push_back (& Function);
    tasks.push_back (functor);
    tasks.push_back (lamda);

    std::vector <std::thread> workers;
    for (size_t i = 0; i < tasks.size (); ++i) {
        workers.push_back (std::thread (tasks [i]) );
    }

    for (size_t i = 0; i < workers.size (); ++i) {
        workers [i].join ();
    }

    return EXIT_SUCCESS;
}
