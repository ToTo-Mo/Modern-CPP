#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <mutex>
#include <Windows.h>

using namespace std;

const int MAX_COUNT = 1500000;
const int THREAD_COUNT = 4;

bool IsPrimeNumber(int number)
{
	if (number == 1)
		return false;

	if (number == 2 || number == 3)
		return true;

	for (int i = 2; i <= number / 2; i++) {
		if ((number % i) == 0)
			return false;
	}

	return true;
}

void main()
{
	int num = 1;
	recursive_mutex numMutex;
	vector<int> primes;
	recursive_mutex primesMutex;

	vector<shared_ptr<thread>> threads;



	auto t0 = chrono::system_clock::now();

	for (int i = 0; i < THREAD_COUNT; i++) {
		shared_ptr<thread> newThread(new thread(
			[&]() {
				while (true)
				{
					int n;
					{
						lock_guard<recursive_mutex> numLock(numMutex);
						n = num;
						num++;
					}

					if (n >= MAX_COUNT)
						break;

					if (IsPrimeNumber(n))
					{
						lock_guard<recursive_mutex> primesLock(primesMutex);
						// 시리얼 병목 발생
						//Sleep(1);	
						primes.push_back(n);
					}
				}
			}
		));

		threads.push_back(newThread);
	}

	for (auto thread : threads)
	{
		thread->join();
	}

	auto t1 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();

	cout << "Took " << duration << " ms" << endl;
}

