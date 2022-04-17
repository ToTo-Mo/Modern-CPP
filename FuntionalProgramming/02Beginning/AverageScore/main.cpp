#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <chrono>
#include <random>

double AverageScore(const std::vector<int>& scores)
{
    return std::accumulate(scores.cbegin(), scores.cend(),0.0) / (double)scores.size();
}

double AverageScore_Parallel(const std::vector<int>& scores)
{
    return std::reduce(
        std::execution::par_unseq,
        scores.cbegin(), scores.cend(),
        0.0
    ) / (double) scores.size();
}

std::vector<int> RandN(const int size,const int a,const int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(a,b);

    std::vector<int> results(size);

    for(int i=0; i<size; i++){
        results.push_back(dis(gen));
    }

    return std::move(results);
}

int main()
{
    std::vector<int> scores = RandN(1000, 0, 100);

    auto t0 = std::chrono::system_clock::now();
    std::cout<<"average : "<<AverageScore(scores)<<std::endl;
    auto t1 = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout<<"took : "<<duration<<std::endl;

    t0 = std::chrono::system_clock::now();
    std::cout<<"average : "<<AverageScore_Parallel(scores)<<std::endl;
    t1 = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout<<"took : "<<duration<<std::endl;
}   