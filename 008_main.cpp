// Conditional variables. Producer-Consumer example.
// $ g++ -Wall -Wextra -std=c++11 008_main.cpp -lpthread -o 008_main
// $ ./008_main
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <iostream>



struct WorkDescriptor
{
    using item = int;
    std::shared_ptr <std::queue <item> >    queue;
    std::shared_ptr <std::mutex>            mutex;
    std::shared_ptr <std::condition_variable>
                                            condition;
    const size_t                            task;
    std::shared_ptr <bool>                  done;
};



void Produce (const WorkDescriptor & descriptor)
{
    for (size_t i = 0; i < descriptor.task; ++i) {
        std::unique_lock <std::mutex> lock (* descriptor.mutex);
        std::cout << " > ";
        std::cout << i;
        descriptor.queue->push (i);
        if (i == descriptor.task - 1) {
            * descriptor.done = true;
        }
        lock.unlock ();
        descriptor.condition->notify_one ();
        std::this_thread::sleep_for (std::chrono::seconds (1) );
    }
}



void Consume (const WorkDescriptor & descriptor)
{
    while (true) {
        std::unique_lock <std::mutex> lock (* descriptor.mutex);
        descriptor.condition->wait (lock, [&]{return !descriptor.queue->empty ();});
        while (!descriptor.queue->empty () ) {
            std::cout << " < " << descriptor.queue->front () << std::endl;
            descriptor.queue->pop ();
        }
        if (* descriptor.done) {
            return;
        }
    }
}



int main (int, char **)
{
    WorkDescriptor descriptor {
        std::make_shared <std::queue <WorkDescriptor::item> > ()
      , std::make_shared <std::mutex> ()
      , std::make_shared <std::condition_variable> ()
      , 30
      , std::make_shared <bool> (false)
    };

    std::thread consumer (Consume, descriptor);
    std::thread producer (Produce, descriptor);

    producer.join ();
    consumer.join ();

    return EXIT_SUCCESS;
}
