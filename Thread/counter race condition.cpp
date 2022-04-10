#include <iostream>
#include <thread>
#include <vector>

void worker(int &counter)
{
    for (int i = 0; i < 10000; i++)
    {
        /* 브레이크 포인트를 지정하여, 
        실제로 counter +=1 이 기계어로 변환되어
        어떻게 동작하는지 확인 해보기.*/
        counter += 1;
    }
}

int main()
{
    int counter = 0;

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++)
    {
        // 레퍼런스로 전달하려면 ref 함수로 감싸야 한다 (지난 강좌 bind 함수 참조)
        workers.push_back(std::thread(worker, std::ref(counter)));
    }

    for (int i = 0; i < 4; i++)
    {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl;
}