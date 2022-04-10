#include "ThreadPool.h"
#include <iostream>

void Work(int timer, int id)
{
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(timer));
    printf("%d end after %d\n", id, timer);
}

int main()
{
    ThreadPool pool(8);

    for(int i=0; i<10; i++){
        pool.EnqueueJob([i](){
            Work(i % 3 + 1, i);
        });
    }
}