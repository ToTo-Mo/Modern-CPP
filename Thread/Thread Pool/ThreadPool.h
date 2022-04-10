#include <vector>
#include <thread>
#include <cstdio>
#include <mutex>
#include <queue>
#include <functional>

class ThreadPool
{
public:
    ThreadPool(size_t numThreads);
    virtual ~ThreadPool();

    void EnqueueJob(std::function<void()> job);

private:
    void WorkerThread();

private:
    size_t mNumThreads;
    std::vector<std::thread> mWorkerThreads;

    /* 할일들을 보관하는 Job 큐*/
    std::queue<std::function<void()>> mWaitingJobs;

    /* Job 큐를 위한 락과 콜백*/
    std::mutex mJobQueueMutex;
    std::condition_variable mJobQueueCV;

    /* 모든 쓰레드의 종료 여부, 기본값은 false이며 true시 모든 쓰레드가 종료됨*/
    bool bStopAll;
};

ThreadPool::ThreadPool(size_t numThreads) : mNumThreads(numThreads),
                                            bStopAll(false)
{
    mWorkerThreads.reserve(numThreads);
    for (size_t i = 0; i < mNumThreads; i++)
    {
        mWorkerThreads.emplace_back([this]()
                                    { this->WorkerThread(); });
    }
}

ThreadPool::~ThreadPool()
{
    bStopAll = true;
    mJobQueueCV.notify_all();

    for (auto &worker : mWorkerThreads)
    {
        worker.join();
    }
}

void ThreadPool::WorkerThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mJobQueueMutex);
        mJobQueueCV.wait(lock, [this]()
                         { return this->mWaitingJobs.empty() || bStopAll; });

        if (bStopAll && this->mWaitingJobs.empty())
        {
            return;
        }

        auto job = std::move(mWaitingJobs.front());
        mWaitingJobs.pop();
        lock.unlock();

        job();
    }
}

void ThreadPool::EnqueueJob(std::function<void()> job)
{
    if (bStopAll)
    {
        throw std::runtime_error("Thread Pool was exitted?");
    }

    {
        std::lock_guard<std::mutex> lock(mJobQueueMutex);
        mWaitingJobs.push(std::move(job));
    }
    mJobQueueCV.notify_one();
}
