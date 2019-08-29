// RAII example.
// $ g++ -Wall -Wextra -std=c++11 006_main.cpp -o 006_main
// $ ./006_main
#include <cstdlib>
#include <iostream>

class Cleaner
{
    public:
        Cleaner (char * resource)
            : resource (resource)
        {
        }

        ~Cleaner ()
        {
            delete resource;
        }

    private:
        const char * const resource;
};

int main (int, char **)
{
    char * data = new char;
    Cleaner cleaner (data);

    return EXIT_SUCCESS;
}
